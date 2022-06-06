#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Matrix.h"

const int SPECIAL_KEY_1 = 0;
const int SPECIAL_KEY_2 = 224;
const int ARROW_UP = 72;
const int ARROW_LEFT = 75;
const int ARROW_RIGHT = 77;
const int ARROW_DOWN = 80;
const int CHAR_SLASH = 47;
const int CHAR_MINUS = 45;
const int CHAR_NINE = 57;
const int CHAR_ZERO = 48;
const int KEY_ENTER = 13;
const int INVALID_KEY = -1;
const int BACKSPACE = 8;
const int CHAR_POINT = 46;

std::string trim(const std::string& value) {
	std::string result = value;
	if (value.starts_with(' ')) {
		result.erase(0, result.find_first_not_of(' '));
	}
	if (value.ends_with(' ')) {
		auto offset = result.find_first_of(' ');
		result.erase(offset, result.size() - offset);
	}
	return result;
}

std::string renderMatrix(const Matrix& matrix, uint32_t currentRow, uint32_t currentColumn) {
	if (matrix.getRow() == 0 || matrix.getColumn() == 0) return "empty matrix";
	if (currentRow > matrix.getRow() || currentColumn > matrix.getColumn()) return matrix.toString();
	MatrixHelper::matrix_t mat = matrix.getMatrix();
	int maxLen = MatrixHelper::findMaxLen(mat);
	std::string result = "";
	std::string beforeEle = "|";
	std::string afterEle = "|";
	for (int row = 0; row < mat.size(); row++) {
		for (int col = 0; col < mat.at(row).size(); col++) {
			if (row == currentRow && col == currentColumn) {
				beforeEle = "[";
				if (col == mat.at(row).size() - 1) afterEle = "]";
			}
			else if (row == currentRow && col != mat.at(row).size() && col - 1 == currentColumn) {
				beforeEle = "]";
			}
			std::string adjustedElement = beforeEle + MatrixHelper::fillSpaceLeft(
				MatrixHelper::truncateZero(std::to_string(mat.at(row).at(col))), maxLen
			);
			result.append(adjustedElement);
			beforeEle = "|";
		}
		result.append(afterEle + "\n");
		afterEle = "|";
	}
	return result;
}

int filteredInput() {
	int ch = _getch();
	if (ch == SPECIAL_KEY_1 || ch == SPECIAL_KEY_2) return _getch();
	else if (
		ch == KEY_ENTER ||
		ch == BACKSPACE ||
		ch == CHAR_MINUS ||
		(ch > CHAR_MINUS && ch != CHAR_SLASH && ch < CHAR_NINE)
		) return ch;
	else return -1;
}

void initMatrix(MatrixHelper::matrix_t& empty_matrix, int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	auto temp = std::vector<double>(column, 0.0);
	empty_matrix = MatrixHelper::matrix_t(row, temp);
}

MatrixHelper::matrix_t createMatrix(int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	auto temp = std::vector<double>(column, 0.0);
	return MatrixHelper::matrix_t(row, temp);
}

void handleUp() {}
void handleDown() {}
void handleLeft() {}
void handleRight() {}
void handleNext(const std::string& currentValue) {
	if (currentValue.ends_with('.')) return;
	if (currentValue.size() > 10) throw std::exception("Input is too big.");

}

void handleInput(std::string& currentValue) {
	currentValue = trim(currentValue);
	int input = filteredInput();
	switch (input)
	{
		// case ARROW up down left right
	case CHAR_MINUS:
		if (currentValue.size() > 10) break; // Limit max char
		if (currentValue.starts_with('-')) break;
		if (currentValue.empty()) {
			currentValue.push_back('-');
			std::cout << '-';
		}
		break;
	case CHAR_POINT:
		if (currentValue.size() > 10) break;
		if (currentValue.find('.') != std::string::npos) break;
		currentValue.push_back('.');
		std::cout << '.';
		break;
	case BACKSPACE:
		if (currentValue.empty()) break;
		std::cout << "\b \b"; // backspace
		currentValue.pop_back();
		break;
	case KEY_ENTER:
		handleNext(currentValue);
	default:
		if (currentValue.size() > 10) break;
		if (input >= CHAR_ZERO && input <= CHAR_NINE) {
			currentValue.push_back((char)input);
			std::cout << (char)input;
		}
		break;
	}
}

void print(const std::string& string) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int COLOR = 31;
	const int DEFAULT_COLOR = 15;
	for (auto& ch : string) {
		if (ch == '[' || ch == ']') SetConsoleTextAttribute(hConsole, COLOR);
		else SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
		std::cout << ch;
	}
}

int main() {
	system("pause");
}
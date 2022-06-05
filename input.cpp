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
const int KEY_ENTER = 13;

std::string MatrixToString(Matrix matrix, uint32_t currentRow, uint32_t currentColumn) {
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

int filterInput() {
	int ch = _getch();
	if (ch == SPECIAL_KEY_1 || ch == SPECIAL_KEY_2) {
		return _getch();
	}
	else if (ch == KEY_ENTER || (ch > CHAR_MINUS && ch != CHAR_SLASH && ch < CHAR_NINE)) {
		return ch;
	}
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
void handleNext(std::string currentValue) {
	// check if current value is exceed double max value
}

void handleInput() {
	int input = filterInput();
	while (input != KEY_ENTER) {

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
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (WORD i = 0; i < 255; i++) {
		SetConsoleTextAttribute(hConsole, i);
		std::cout << i << ". Yoooo!\n";
	}*/
	MatrixHelper::matrix_t a = createMatrix(15, 10);
	a[5][5] = 1000.0;
	Matrix matA = Matrix(a);
	unsigned int row = 0;
	unsigned int col = 0;
	while (true) {
		print(MatrixToString(matA, row, col));
		std::cout << row << "x" << col << std::endl;
		switch (filterInput())
		{
		case ARROW_UP:
			row--; break;
		case ARROW_DOWN:
			row++; break;
		case ARROW_LEFT:
			col--; break;
		case ARROW_RIGHT:
			col++; break;
		case KEY_ENTER:
			// handleNext()
			break;
		default:
			break;
		}
		system("cls");
	}
	system("pause");
}
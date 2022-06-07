#include <iostream>
#include <vector>
#include <string>
#include "Matrix.h"
#include "nduc/Keycode.h"
#include "MatrixHelper.h"
#include "MatrixRenderer.h"
#include <conio.h>

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

int main() {
	auto matA = MatrixHelper::createMatrix(10, 10);
	matA[5][5] = 10000.0;
	auto matA_r = MatrixRenderer(matA);
	matA_r.go_to(5, 5)->printWithIndicator();
	system("pause");
}
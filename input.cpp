#include <iostream>
#include <string>
#include <conio.h>
#include "Matrix.h"
#include "nduc/Keycode.h"
#include "MatrixHelper.h"
#include "MatrixRenderer.h"
#include "Input.h"
#include "Utils.h"

int getFilteredInput() {
	int ch = _getch();
	if (ch == SPECIAL_KEY_1 || ch == SPECIAL_KEY_2) return _getch();
	else if (
		ch == KEY_ENTER ||
		ch == BACKSPACE ||
		ch == CHAR_MINUS ||
		ch == CTRL_S ||
		(ch >= CHAR_MINUS && ch != CHAR_SLASH && ch <= CHAR_NINE)
		) return ch;
	else return -1;
}

void handleUp(std::string& currentValue, MatrixRenderer& matrixRenderer) {
	currentValue.clear();
	matrixRenderer.up();
}
void handleDown(std::string& currentValue, MatrixRenderer& matrixRenderer) {
	currentValue.clear();
	matrixRenderer.down();
}
void handleLeft(std::string& currentValue, MatrixRenderer& matrixRenderer) {
	currentValue.clear();
	matrixRenderer.left();
}
void handleRight(std::string& currentValue, MatrixRenderer& matrixRenderer) {
	currentValue.clear();
	matrixRenderer.right();
}
void handleNext(std::string& currentValue, MatrixRenderer& matrixRenderer) {
	if (currentValue.ends_with('.')) return;
	if (currentValue.ends_with('-')) return;
	if (currentValue.size() > VALUE_CHAR_LIMIT) throw std::exception("Input is too big.");

	if (currentValue.empty()) {
		matrixRenderer.next();
		return;
	}

	double stoded = std::stod(trim(currentValue));
	// Zero check to avoid displaying "minus zero (-0)" in matrix
	if (stoded == 0) stoded = 0.0;

	matrixRenderer.setCurrentElement(stoded);
	currentValue.clear();
	matrixRenderer.next();
}

Matrix handleInput(std::string& currentValue, MatrixRenderer& matrixRenderer, std::string matrixName) {
	currentValue = trim(currentValue);
	while (true) {
		system("cls");
		std::cout << "Enter value for matrix " << matrixName << std::endl;
		matrixRenderer.printWithIndicator();
		std::cout << "Enter value for element at row "
			<< matrixRenderer.getCurrentRow() + 1
			<< " and column "
			<< matrixRenderer.getCurrentColumn() + 1
			<< " or press ctrl+s to save the matrix: "
			<< currentValue;
		int input = getFilteredInput();
		switch (input)
		{
		case ARROW_UP:
			handleUp(currentValue, matrixRenderer); break;
		case ARROW_DOWN:
			handleDown(currentValue, matrixRenderer); break;
		case ARROW_LEFT:
			handleLeft(currentValue, matrixRenderer); break;
		case ARROW_RIGHT:
			handleRight(currentValue, matrixRenderer); break;
		case CHAR_MINUS:
			if (currentValue.size() >= VALUE_CHAR_LIMIT) break; // Limit max char
			if (currentValue.starts_with('-')) break;
			if (currentValue.empty()) {
				currentValue.push_back('-');
			}
			break;
		case CHAR_POINT:
			if (currentValue.size() >= VALUE_CHAR_LIMIT) break;
			if (currentValue.find('.') != std::string::npos) break;
			currentValue.push_back('.');
			break;
		case BACKSPACE:
			if (currentValue.empty()) break;
			currentValue.pop_back();
			break;
		case KEY_ENTER:
			handleNext(currentValue, matrixRenderer);
			break;
		case CTRL_S:
			return matrixRenderer;
		default:
			if (currentValue.size() >= VALUE_CHAR_LIMIT) break;
			if (input >= CHAR_ZERO && input <= CHAR_NINE) {
				currentValue.push_back((char)input);
			}
			break;
		}
	}
}

unsigned int getRowColInput() {
	int first_char, second_char;
	std::string currentValue;
	while (true)
	{
		first_char = _getch();
		if (first_char == CHAR_ONE) {
			currentValue.push_back((char)first_char);
			_putch(first_char);
			break;
		}
		else if (first_char >= CHAR_TWO && first_char <= CHAR_NINE) {
			currentValue.push_back((char)first_char);
			_putch(first_char);
			return std::stod(currentValue);
		}
	}
	while (true) {
		second_char = _getch();
		if (second_char == CHAR_ZERO) {
			currentValue.push_back((char)second_char);
			_putch(second_char);
			return std::stod(currentValue);
		}
		else if (second_char == KEY_ENTER) {
			return std::stod(currentValue);
		}
	}
}

Matrix::matrix_t initMatrixFromInput(std::string matrixName) {
	unsigned int row, col;
	std::cout << "Creating matrix " << trim(matrixName) << std::endl;
	std::cout << "How many rows do you want? (Max is 10) ";
	row = getRowColInput();
	std::cout << std::endl;
	std::cout << "How many columns do you want? (Max is 10) ";
	col = getRowColInput();
	std::cout << std::endl;
	return MatrixHelper::createMatrix(row, col);
}

void start() {
	std::cout << "Matrix calculator (beta)\n-------------------------------------\n";
	Matrix::matrix_t matA = initMatrixFromInput("A"), matB = initMatrixFromInput("B");
	MatrixRenderer matrixA = MatrixRenderer(matA), matrixB = MatrixRenderer(matB);
	std::string currentValue;
	Matrix a = handleInput(currentValue, matrixA, "A");
	Matrix b = handleInput(currentValue, matrixB, "B");
	unsigned int option;
	std::cout << "\nOptions:\n1. A+B\n2. A-B\n3. B-A\n4. AxB\n5. BxA\n";
	do {
		option = _getch();
	} while (!(option >= CHAR_ONE && option <= CHAR_FIVE));
	system("cls");
	switch (option)
	{
	case CHAR_ONE:
		std::cout << "A+B is:\n" << Matrix::plus(a, b).toString() << std::endl;
		break;
	case CHAR_TWO:
		std::cout << "A-B is:\n" << Matrix::subtract(a, b).toString() << std::endl;
		break;
	case CHAR_THREE:
		std::cout << "B-A is:\n" << Matrix::subtract(b, a).toString() << std::endl;
		break;
	case CHAR_FOUR:
		std::cout << "AxB is:\n" << Matrix::multiply(a, b).toString() << std::endl;
		break;
	case CHAR_FIVE:
		std::cout << "BxA is:\n" << Matrix::multiply(b, a).toString() << std::endl;
		break;
	default:
		std::cout << "Invalid input. Program closes.";
		break;
	}
}
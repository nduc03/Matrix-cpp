#include <iostream>
#include <string>
#include <conio.h>

#include "nduc/Keycode.h"
#include "Matrix.h"
#include "MatrixHelper.h"
#include "MatrixRenderer.h"
#include "MatrixError.h"
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

void backspace() {
	std::cout << "\b \b";
}

unsigned int getRowColInput() {
	std::string currentValue;
	while (true) {
		int input = _getch();
		if (currentValue.empty()) {
			if (input == CHAR_ONE) {
				currentValue.push_back((char)input);
				_putch(input);
			}
			else if (input >= CHAR_TWO && input <= CHAR_NINE) {
				currentValue.push_back((char)input);
				_putch(input);
			}
		}
		else if (currentValue.size() == 1) {
			if (input == CHAR_ZERO && currentValue.back() == CHAR_ONE) {
				currentValue.push_back((char)input);
				_putch(input);
			}
			else if (input == BACKSPACE) {
				backspace();
				currentValue.pop_back();
			}
			else if (input == KEY_ENTER) {
				return std::stod(currentValue);
			}
		}
		else if (currentValue.size() == 2) {
			if (currentValue.front() == CHAR_ONE && currentValue.at(1) == CHAR_ZERO && input == KEY_ENTER) {
				return std::stod(currentValue);
			}
			else if (currentValue.front() != CHAR_ONE && currentValue.at(1) != CHAR_ZERO) {
				throw std::exception("Somethings wrong with getRowColInput()");
			}
			else if (input == BACKSPACE) {
				currentValue.pop_back();
				backspace();
			}
		}
		else throw std::exception("Somethings really wrong with getRowColInput()");
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
	std::cout << "Matrix calculator (beta)\n-------------------------------------------\n";
	Matrix::matrix_t matA = initMatrixFromInput("A"), matB = initMatrixFromInput("B");
	MatrixRenderer matrixA = MatrixRenderer(matA), matrixB = MatrixRenderer(matB);
	std::string currentValue;
	Matrix a = handleInput(currentValue, matrixA, "A");
	Matrix b = handleInput(currentValue, matrixB, "B");
	system("cls");
	unsigned int option;
	std::cout << "Options:\n1. A+B\n2. A-B\n3. B-A\n4. AxB\n5. BxA\n";
	do {
		option = _getch();
	} while (!(option >= CHAR_ONE && option <= CHAR_FIVE));
	system("cls");
	try {
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
	catch (MatrixError err) {
		system("cls");
		std::cout << "!!! Program had a problem !!!\nProgram error message: " << err.reason() << std::endl;
		return;
	}
}

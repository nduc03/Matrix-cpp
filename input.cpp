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
		(ch > CHAR_MINUS && ch != CHAR_SLASH && ch < CHAR_NINE)
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
	if (currentValue.size() > 10) throw std::exception("Input is too big.");

	if (!currentValue.empty()) matrixRenderer.setCurrentElement(std::stod(trim(currentValue)));
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
			<< matrixRenderer.getCurrentRow()
			<< " and column "
			<< matrixRenderer.getCurrentColumn()
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
			if (currentValue.size() > 10) break; // Limit max char
			if (currentValue.starts_with('-')) break;
			if (currentValue.empty()) {
				currentValue.push_back('-');
			}
			break;
		case CHAR_POINT:
			if (currentValue.size() > 10) break;
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
			if (currentValue.size() > 10) break;
			if (input >= CHAR_ZERO && input <= CHAR_NINE) {
				currentValue.push_back((char)input);
			}
			break;
		}
	}
}

Matrix::matrix_t initMatrixFromInput(std::string matrixName) {
	using namespace std;
	unsigned int row, col;
	cout << "Creating matrix " << trim(matrixName) << endl;
	cout << "How many rows do you want? (Max is 20) ";
	cin >> row;
	if (row > 20) throw exception("Row is to big.");
	cout << "How many columns do you want? (Max is 20) ";
	cin >> col;
	if (col > 20) throw exception("Column is to big.");
	return MatrixHelper::createMatrix(row, col);
}

void start() {
	std::cout << "This program still in development and it will definitely crash if user pass illegitimate input.\n";
	std::cout << "Matrix calculator (very beta)\n-------------------------------------\n";
	Matrix::matrix_t matA = initMatrixFromInput("A"), matB = initMatrixFromInput("B");
	MatrixRenderer matrixA = MatrixRenderer(matA), matrixB = MatrixRenderer(matB);
	std::string currentValue;
	Matrix a = handleInput(currentValue, matrixA, "A");
	Matrix b = handleInput(currentValue, matrixB, "B");
	unsigned int option;
	std::cout << "\nOptions:\n1. A+B\n2. A-B\n3. B-A\n4. AxB\n5. BxA\n";
	std::cin >> option;
	system("cls");
	switch (option)
	{
	case 1:
		std::cout << "A+B is:\n" << Matrix::plus(a, b).toString() << std::endl;
		break;
	case 2:
		std::cout << "A-B is:\n" << Matrix::subtract(a, b).toString() << std::endl;
		break;
	case 3:
		std::cout << "B-A is:\n" << Matrix::subtract(b, a).toString() << std::endl;
		break;
	case 4:
		std::cout << "AxB is:\n" << Matrix::multiply(a, b).toString() << std::endl;
		break;
	case 5:
		std::cout << "BxA is:\n" << Matrix::multiply(b, a).toString() << std::endl;
		break;
	default:
		std::cout << "Invalid input. Program closes.";
		break;
	}
}
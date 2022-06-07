#include <Windows.h>
#include <conio.h>
#include "MatrixRenderer.h"
#include "MatrixHelper.h"

int MatrixRenderer::getCurrentRow() const
{
	return this->currentRow;
}

int MatrixRenderer::getCurrentColumn() const
{
	return this->currentColumn;
}

MatrixRenderer::MatrixRenderer(matrix_t matrix) : Matrix(matrix)
{
	this->currentRow = 0; this->currentColumn = 0;
}

MatrixRenderer::MatrixRenderer(Matrix matrix) : Matrix(matrix.getMatrix())
{
	this->currentRow = 0; this->currentColumn = 0;
}

MatrixRenderer* MatrixRenderer::up()
{
	if (this->currentRow > 0) currentRow--;
	return this;
}

MatrixRenderer* MatrixRenderer::down()
{
	if (this->currentRow > 0) currentRow++;
	return this;
}

MatrixRenderer* MatrixRenderer::left()
{
	if (this->currentColumn > 0) currentColumn--;
	return this;
}

MatrixRenderer* MatrixRenderer::right()
{
	if (this->currentColumn > 0) currentColumn++;

	return this;
}

MatrixRenderer* MatrixRenderer::next()
{
	if (this->currentColumn >= this->getColumn()) {
		return this->down()->go_to(currentRow, 0);
	}
	return this->left();
}

MatrixRenderer* MatrixRenderer::go_to(uint32_t row, uint32_t column)
{
	if (row <= this->getRow() && column <= this->getColumn()) {
		this->currentColumn = column;
		this->currentRow = row;
	}
	return this;
}

std::string MatrixRenderer::toStringWithIndicator()
{
	if (this->getRow() == 0 || this->getColumn() == 0) return "Empty matrix.\n";
	if (currentRow > this->getRow() || currentColumn > this->getColumn()) return this->toString();
	MatrixHelper::matrix_t matrix = this->getMatrix();
	int maxLen = MatrixHelper::findMaxLen(matrix);
	std::string result = "";
	std::string beforeEle = "|";
	std::string afterEle = "|";
	for (int row = 0; row < matrix.size(); row++) {
		for (int col = 0; col < matrix.at(row).size(); col++) {
			if (row == currentRow && col == currentColumn) {
				beforeEle = "[";
				if (col == matrix.at(row).size() - 1) afterEle = "]";
			}
			else if (row == currentRow && col != matrix.at(row).size() && col - 1 == currentColumn) {
				beforeEle = "]";
			}
			std::string adjustedElement = beforeEle + MatrixHelper::fillSpaceLeft(
				MatrixHelper::truncateZero(std::to_string(matrix.at(row).at(col))), maxLen
			);
			result.append(adjustedElement);
			beforeEle = "|";
		}
		result.append(afterEle + "\n");
		afterEle = "|";
	}
	return result;
}

void MatrixRenderer::printWithIndicator()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int COLOR = 31;
	const int DEFAULT_COLOR = 15;
	std::string string = this->toStringWithIndicator();
	for (auto& ch : string) {
		if (ch == '[' || ch == ']') SetConsoleTextAttribute(hConsole, COLOR);
		else SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
		_putch(ch);
	}
}
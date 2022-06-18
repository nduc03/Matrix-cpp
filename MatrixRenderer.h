#pragma once
#include "Matrix.h"
class MatrixRenderer : public Matrix
{
public:
	uint32_t getCurrentRow() const;
	uint32_t getCurrentColumn() const;
	MatrixRenderer(matrix_t matrix);
	MatrixRenderer(Matrix matrix);
	MatrixRenderer* up();
	MatrixRenderer* down();
	MatrixRenderer* left();
	MatrixRenderer* right();
	MatrixRenderer* next();
	MatrixRenderer* go_to(uint32_t row, uint32_t column);
	void setCurrentElement(double value);
	std::string toStringWithIndicator() const;
	void printWithIndicator() const;
private:
	uint32_t currentRow, currentColumn, maxLen;
};


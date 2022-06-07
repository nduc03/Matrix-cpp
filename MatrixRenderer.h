#pragma once
#include "Matrix.h"
class MatrixRenderer : public Matrix
{
public:
	int getCurrentRow() const;
	int getCurrentColumn() const;
	MatrixRenderer(matrix_t matrix);
	MatrixRenderer(Matrix matrix);
	MatrixRenderer* up();
	MatrixRenderer* down();
	MatrixRenderer* left();
	MatrixRenderer* right();
	MatrixRenderer* next();
	MatrixRenderer* go_to(uint32_t row, uint32_t column);
	std::string toStringWithIndicator();
	void printWithIndicator();
private:
	int currentRow, currentColumn;
};


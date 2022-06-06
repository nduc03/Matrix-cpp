#pragma once
#include "Matrix.h"
class MatrixRenderer : public Matrix
{
public:
	int getCurrentRow() const;
	int getCurrentColumn() const;
	MatrixRenderer(matrix_t matrix);
	MatrixRenderer* up();
	MatrixRenderer* down();
	MatrixRenderer* left();
	MatrixRenderer* right();
	MatrixRenderer* go_to(uint32_t row, uint32_t column);
private:
	int currentRow = 0, currentColumn = 0;
	void print(const std::string& string);
	std::string toString(uint32_t currentRow, uint32_t currentColumn);
};


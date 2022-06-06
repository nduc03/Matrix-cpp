#include "MatrixRenderer.h"

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
}

MatrixRenderer* MatrixRenderer::up()
{
	return this;
}

MatrixRenderer* MatrixRenderer::down()
{
	return this;
}

MatrixRenderer* MatrixRenderer::left()
{
	return this;
}

MatrixRenderer* MatrixRenderer::right()
{
	return this;
}

MatrixRenderer* MatrixRenderer::go_to(uint32_t row, uint32_t column)
{
	return this;
}

void MatrixRenderer::print(const std::string& string)
{
}

std::string MatrixRenderer::toString(uint32_t currentRow, uint32_t currentColumn)
{
	return std::string();
}

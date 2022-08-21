#pragma once
#include <string>
#include <vector>

class Matrix {
public:
	typedef std::vector<std::vector<double>> matrix_t;

	Matrix(matrix_t matrix);

	uint32_t    getRow() const;
	uint32_t getColumn() const;
	matrix_t getMatrix() const;
	bool isSquare() const;
	std::string getElement(uint32_t row, uint32_t column) const;
	void setElement(double value, uint32_t row, uint32_t column);

	Matrix multiplyWith(const Matrix& matrix);
	Matrix     plusWith(const Matrix& matrix);
	Matrix subtractWith(const Matrix& matrix);

	static Matrix multiply(const Matrix& matrixA, const Matrix& matrixB);
	static Matrix     plus(const Matrix& matrixA, const Matrix& matrixB);
	static Matrix subtract(const Matrix& matrixA, const Matrix& matrixB);

	std::string toString() const;
private:
	uint32_t m_row, m_column;
	matrix_t m_matrix;

	static matrix_t   mul(const matrix_t& matrixA, const matrix_t& matrixB);
	static matrix_t   add(const matrix_t& matrixA, const matrix_t& matrixB);
	static matrix_t minus(const matrix_t& matrixA, const matrix_t& matrixB);
};

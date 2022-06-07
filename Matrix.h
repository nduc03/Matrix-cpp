#pragma once
#include <string>
#include <vector>

class Matrix {
protected:
	typedef std::vector<std::vector<double>> matrix_t;
private:
	int m_row, m_column;
	matrix_t m_matrix;

	static matrix_t mul(const matrix_t& matrixA, const matrix_t& matrixB);
	static matrix_t _plus(const matrix_t& matrixA, const matrix_t& matrixB);
	static matrix_t minus(const matrix_t& matrixA, const matrix_t& matrixB);
public:
	Matrix(matrix_t matrix);

	int getRow() const;
	int getColumn() const;
	bool isSquare() const;
	std::string getElement(int row, int column) const;
	matrix_t getMatrix() const;

	Matrix multiplyWith(const Matrix& matrix);
	Matrix plusWith(const Matrix& matrix);
	Matrix subtractWith(const Matrix& matrix);

	static Matrix multiply(const Matrix& matrixA, const Matrix& matrixB);
	static Matrix plus(const Matrix& matrixA, const Matrix& matrixB);
	static Matrix subtract(const Matrix& matrixA, const Matrix& matrixB);

	std::string toString() const;
};

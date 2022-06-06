#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class MatrixError : std::exception {
	std::string msg;
public:
	MatrixError(std::string msg);
	std::string reason();
};

class MatrixMultiplyError : public MatrixError {
public:
	MatrixMultiplyError(std::string msg);
};

class MatrixPlusMinusError : public MatrixError {
public:
	MatrixPlusMinusError(std::string msg);
};

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

class MatrixHelper {
public:
	typedef std::vector<std::vector<double>> matrix_t;

	MatrixHelper() = delete;
	static int findMaxLen(matrix_t matrix);
	static std::string fillSpaceLeft(const std::string& value, int requiredLength);
	static std::string truncateZero(const std::string& value);
};
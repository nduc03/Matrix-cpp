#include "Matrix.h"
#include "MatrixHelper.h"
#include "MatrixError.h"

Matrix::matrix_t Matrix::mul(const matrix_t& matrixA, const matrix_t& matrixB) {
	if (matrixA[0].size() != matrixB.size()) throw MatrixMultiplyError("Invalid dimension, can't multiply");
	matrix_t result;
	int row = matrixA.size();
	int col = matrixB[0].size();
	int row_col_common = matrixB.size();
	for (int i = 0; i < row; i++) {
		result.push_back({});
		for (int j = 0; j < col; j++) {
			result[i].push_back(0.0);
			for (int x = 0; x < row_col_common; x++) {
				result[i][j] += matrixA[i][x] * matrixB[x][j];
			}
		}
	}
	return result;
}

Matrix::matrix_t Matrix::_plus(const matrix_t& matrixA, const matrix_t& matrixB) {
	if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size())
		throw MatrixPlusMinusError("Invalid dimension, can't plus");
	matrix_t result;
	int row = matrixA.size();
	int col = matrixB[0].size();
	for (int i = 0; i < row; i++) {
		result.push_back({});
		for (int j = 0; j < col; j++) {
			result[i].push_back(matrixA[i][j] + matrixB[i][j]);
		}
	}
	return result;
}

Matrix::matrix_t Matrix::minus(const matrix_t& matrixA, const matrix_t& matrixB) {
	if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size())
		throw MatrixPlusMinusError("Invalid dimension, can't subtract");
	matrix_t result;
	int row = matrixA.size();
	int col = matrixB[0].size();
	for (int i = 0; i < row; i++) {
		result.push_back({});
		for (int j = 0; j < col; j++) {
			result[i].push_back(matrixA[i][j] - matrixB[i][j]);
		}
	}
	return result;
}

int Matrix::getRow() const { return m_row; }

int Matrix::getColumn() const { return m_column; }

bool Matrix::isSquare() const { return m_row == m_column && m_row > 0; }

std::string Matrix::getElement(int row, int column) const {
	if (row < 1 || column < 1) throw std::out_of_range("Invalid position.");
	return MatrixHelper::truncateZero(std::to_string(m_matrix.at(row).at(column)));
}

Matrix::matrix_t Matrix::getMatrix() const { return m_matrix; }

Matrix::Matrix(matrix_t matrix) {
	this->m_matrix = matrix;
	this->m_row = matrix.size();
	this->m_column = matrix[0].size();
	if (m_row < 1 || m_column < 1) throw MatrixError("Invalid matrix");
	if (m_row > 20 || m_column > 20) throw MatrixError("Matrix size is too big.");
	for (int row = 1; row < m_row; row++) {
		if (matrix[row].size() != m_column) throw MatrixError("Invalid matrix. Size of columns not the same.");
	}
}

Matrix Matrix::multiplyWith(const Matrix& matrix) {
	if (this->m_column != matrix.getRow()) throw MatrixMultiplyError("Invalid dimension. Cannot multiply.");
	matrix_t result = mul(this->m_matrix, matrix.getMatrix());
	return Matrix(result);
}

Matrix Matrix::multiply(const Matrix& matrixA, const Matrix& matrixB) {
	if (matrixA.getColumn() != matrixB.getRow()) throw MatrixMultiplyError("Invalid dimension. Cannot multiply.");
	matrix_t result = mul(matrixA.getMatrix(), matrixB.getMatrix());
	return Matrix(result);
}

Matrix Matrix::plusWith(const Matrix& matrix) {
	if (this->m_column != matrix.getColumn() || this->m_row != matrix.getRow())
		throw MatrixMultiplyError("Invalid dimension. Cannot plus.");
	matrix_t result = _plus(this->m_matrix, matrix.getMatrix());
	return Matrix(result);
}

Matrix Matrix::plus(const Matrix& matrixA, const Matrix& matrixB) {
	if (matrixA.getColumn() != matrixB.getColumn() || matrixA.getRow() != matrixB.getRow())
		throw MatrixMultiplyError("Invalid dimension. Cannot plus.");
	matrix_t result = _plus(matrixA.getMatrix(), matrixB.getMatrix());
	return Matrix(result);
}

Matrix Matrix::subtractWith(const Matrix& matrix) {
	if (this->m_column != matrix.getColumn() || this->m_row != matrix.getRow())
		throw MatrixMultiplyError("Invalid dimension. Cannot subtract.");
	matrix_t result = minus(this->m_matrix, matrix.getMatrix());
	return Matrix(result);
}

Matrix Matrix::subtract(const Matrix& matrixA, const Matrix& matrixB) {
	if (matrixA.getColumn() != matrixB.getColumn() || matrixA.getRow() != matrixB.getRow())
		throw MatrixMultiplyError("Invalid dimension. Cannot subtract.");
	matrix_t result = minus(matrixA.getMatrix(), matrixB.getMatrix());
	return Matrix(result);
}

std::string Matrix::toString() const {
	if (m_row == 0 || m_column == 0) return "empty matrix";
	int maxLen = MatrixHelper::findMaxLen(m_matrix);
	std::string result = "";
	for (auto& row : m_matrix) {
		for (auto& element : row) {
			std::string adjustedElement = "|" + MatrixHelper::fillSpaceLeft(
				MatrixHelper::truncateZero(std::to_string(element)), maxLen
			);
			result.append(adjustedElement);
		}
		result.append("|\n");
	}
	return result;
}
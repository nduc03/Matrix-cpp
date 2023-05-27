#include "MatrixHelper.h"
#include "Matrix.h"
#include "MatrixError.h"
#include "Utils.h"

int MatrixHelper::findMaxLen(matrix_t matrix) {
	int max = 1;
	for (auto& row : matrix) {
		for (auto& ele : row) {
			int len = truncateZero(std::to_string(ele)).size();
			if (len > max) max = len;
		}
	}
	return max;
}

void MatrixHelper::initMatrix(matrix_t& empty_matrix, int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	if (row > 20 || column > 20) throw MatrixError("Matrix size is too big.");
	empty_matrix = MatrixHelper::matrix_t(row, std::vector<double>(column, 0.0));
}

MatrixHelper::matrix_t MatrixHelper::createMatrix(int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	if (row > 20 || column > 20) throw MatrixError("Matrix size is too big.");
	return MatrixHelper::matrix_t(row, std::vector<double>(column, 0.0));
}
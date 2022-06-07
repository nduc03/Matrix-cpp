#include "MatrixHelper.h"
#include "Matrix.h"
#include "MatrixError.h"

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

std::string MatrixHelper::fillSpaceLeft(const std::string& value, int requiredLength) {
	std::string result = "";
	int requiredSpace = requiredLength - value.size();
	for (int i = 0; i < requiredSpace; i++) {
		result += " ";
	}
	return result + value;
}

std::string MatrixHelper::truncateZero(const std::string& value) {
	std::string result = value;
	while ((result.back() == '0' && result.find('.') != std::string::npos) || result.back() == '.') {
		result.pop_back();
	}
	return result;
}

void MatrixHelper::initMatrix(matrix_t& empty_matrix, int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	if (row > 20 || column > 20) throw MatrixError("Matrix size is too big.");
	auto temp = std::vector<double>(column, 0.0);
	empty_matrix = MatrixHelper::matrix_t(row, temp);
}

MatrixHelper::matrix_t MatrixHelper::createMatrix(int row, int column) {
	if (row < 1 || column < 1) throw MatrixError("Invalid row or column.");
	if (row > 20 || column > 20) throw MatrixError("Matrix size is too big.");
	auto temp = std::vector<double>(column, 0.0);
	return MatrixHelper::matrix_t(row, temp);
}
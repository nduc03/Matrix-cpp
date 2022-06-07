#pragma once
#include <vector>
#include <string>

class MatrixHelper {
public:
	typedef std::vector<std::vector<double>> matrix_t;

	MatrixHelper() = delete;
	static int findMaxLen(matrix_t matrix);
	static std::string fillSpaceLeft(const std::string& value, int requiredLength);
	static std::string truncateZero(const std::string& value);
	static void initMatrix(matrix_t& empty_matrix, int row, int column);
	static matrix_t createMatrix(int row, int column);
};
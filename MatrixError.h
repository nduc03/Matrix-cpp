#pragma once
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
#include "MatrixError.h"

MatrixError::MatrixError(std::string msg) {
	this->msg = msg;
}

std::string MatrixError::reason() {
	return this->msg;
}

MatrixMultiplyError::MatrixMultiplyError(std::string msg) : MatrixError(msg) {}

MatrixPlusMinusError::MatrixPlusMinusError(std::string msg) : MatrixError(msg) {}
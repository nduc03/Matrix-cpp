#pragma once
#include <string>
#include "MatrixRenderer.h"

const int VALUE_CHAR_LIMIT = 7;

int getFilteredInput();
void handleUp   (std::string& currentValue, MatrixRenderer& matrixRenderer);
void handleDown (std::string& currentValue, MatrixRenderer& matrixRenderer);
void handleLeft (std::string& currentValue, MatrixRenderer& matrixRenderer);
void handleRight(std::string& currentValue, MatrixRenderer& matrixRenderer);
void handleNext (std::string& currentValue, MatrixRenderer& matrixRenderer);
Matrix handleInput(std::string& currentValue, MatrixRenderer& matrixRenderer, std::string matrixName = "");
Matrix::matrix_t initMatrixFromInput(std::string matrixName = "");
void start();
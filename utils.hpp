#ifndef UTILS_H
#define UTILS_H

#include "Matrix.hpp"
#include <vector>

std::vector<float> matrix_vec_mult(const Matrix& mat, const std::vector<float>& vec);

void vec_sub(std::vector<float>& vec1, const std::vector<float>& vec2);

void vec_sigmoid(std::vector<float>& vec);

#endif

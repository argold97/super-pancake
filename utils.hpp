#ifndef UTILS_H
#define UTILS_H

#include "Matrix.hpp"
#include <vector>
#include <string>
#include <random>

std::vector<float> matrix_vec_mult(const Matrix& mat, const std::vector<float>& vec);

void matrix_add(Matrix& a, const Matrix& b);

void vec_add(std::vector<float>& vec1, const std::vector<float>&vec2);

void vec_sub(std::vector<float>& vec1, const std::vector<float>& vec2);

void vec_sigmoid(std::vector<float>& vec);

std::string matrix_to_string(const Matrix& mat);

std::mt19937& gen();

float binormal(float in);

#endif

#include "utils.hpp"
#include <cmath>

using namespace std;

void vec_add(vector<float>& vec1, const vector<float>& vec2)
{
	for(size_t i = 0; i < vec1.size(); i++)
		vec1[i] = vec1[i] + vec2[i];
}

void vec_sub(vector<float>& vec1, const vector<float>& vec2)
{
	for(size_t i = 0; i < vec1.size(); i++)
		vec1[i] = vec1[i] - vec2[i];
}

void matrix_add(Matrix& a, const Matrix& b)
{
	for(size_t i = 0; i < a.rows(); i++)
		for(size_t j = 0; j < a.cols(); j++)
			*a.at(i, j) += b.get(i, j);
}

inline float sigmoid(float x)
{
	return 1.0F / (1 + exp(x * -1.0F));
}

void vec_sigmoid(vector<float>& vec)
{
	for(size_t i = 0; i < vec.size(); i++)
		vec[i] = sigmoid(vec[i]);
}

vector<float> matrix_vec_mult(const Matrix& mat, const vector<float>& vec)
{
	vector<float> result;

	for(size_t i = 0; i < mat.rows(); i++)
	{
		float sum = 0.0F;
		for(size_t j = 0; j < vec.size(); j++)
			sum += vec[j] * mat.get(i, j);
		result.push_back(sum);
	}
	return result;
}


string matrix_to_string(const Matrix& mat)
{
	string str;
	for(size_t i = 0; i < mat.rows(); i++)
	{
		str += "[ ";
		for(size_t j = 0; j < mat.rows(); j++)
			str += to_string(mat.get(i, j)) + " ";
		str += "]\n";
	}
	return str;
}

mt19937& gen()
{
	static thread_local mt19937 generator(random_device{}());
	return generator;
}

float binormal(float in)
{
	return (gen()() % 2) ? in : -1.0F * in;
}

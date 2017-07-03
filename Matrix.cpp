#include "Matrix.hpp"
#include <cstring>

Matrix::Matrix() : m_data(nullptr), m_rows(0), m_cols(0)
{ }

Matrix::Matrix(unsigned int rows, unsigned int cols) : m_rows(rows), m_cols(cols)
{
	m_data = new float[m_rows * m_cols];
}

Matrix::Matrix(const Matrix& other) : Matrix(other.rows(), other.cols())
{
	load(other.data());
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if(other.rows() * other.cols() != m_rows * m_cols)
	{
		m_rows = other.rows();
		m_cols = other.cols();
		delete m_data;
		m_data = new float[m_rows * m_cols];
	}
	load(other.data());
	return *this;
}

Matrix::~Matrix()
{
	delete[] m_data;
}

float* Matrix::at(unsigned int r, unsigned int c)
{
	return &m_data[r * m_rows + c];
}

float Matrix::get(unsigned int r, unsigned int c) const
{
	return m_data[r * m_rows + c];
}

const float* Matrix::data() const
{
	return (const float*)m_data;
}

void Matrix::load(const float* data)
{
	memcpy((void*)m_data, (const void*)data, sizeof(float) * m_rows * m_cols);
}

unsigned int Matrix::rows() const
{
	return m_rows;
}

unsigned int Matrix::cols() const
{
	return m_cols;
}

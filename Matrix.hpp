#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
	public:
	Matrix();
	Matrix(unsigned int rows, unsigned int cols);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();
	float* at(unsigned int r, unsigned int c);
	float get(unsigned int r, unsigned int c) const;
	const float* data() const;
	void load(const float* data);
	unsigned int rows() const;
	unsigned int cols() const;

	private:
	float* m_data;
	unsigned int m_rows;
	unsigned int m_cols;
};

#endif

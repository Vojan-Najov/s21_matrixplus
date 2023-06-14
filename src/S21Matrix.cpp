#include <cstring.h>
#include <cmath.h>
#include <utility>

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(void)
	: _rows(S21_MATRIX_DEFAULT_ROWS), _cols(S21_MATRIX_DEFAULT_COLS)
{
	_allocateArray(S21_MATRIX_DEFAULT_ROWS, S21_MATRIX_DEFAULT_COLS);
	_resetArray();
}

S21Matrix::S21Matrix(int rows, int cols)
	: _rows(rows), _cols(cols)
{
	if (rows < 1) {
		throw std::invalid_argument("The number of rows is less than 1.");
	}
	if (cols < 1) {
		throw std::invalid_argument("The number of columns is less than 1.");
	}

	_allocateArray(rows, cols);
	memset(_matrix[0], 0, rows * cols * sizeof(double));
}

S21Matrix::S21Matrix(const S21Matrix& other)
	: _rows(other._rows), _cols(other._cols)
{
	_allocateMatrix(_rows, _cols);
	_copyMatrix(other);
}

S21Matrix(S21Matrix&& other)
	: _rows(other._rows), _cols(other._cols), _matrix(other._matrix)
{
	other._rows = 0;
	other._cols = 0;
	other._matrix = nullptr;
}

S21Matrix::~S21Matrix(void)
{
	if (_matrix != nullptr) {
		_clearMatrix();
	}
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept
{
	bool result = true;

	if (_rows != other._rows || _cols != other._cols) {
		result = false;
	} else {
		for (int i = 0; result == true && i < _rows; ++i) {
			for (int j = 0; result == true && j < _cols; ++j) {
				if (fabs(_matrix[i][j] - other._matrix[i][j]) > S21_MATRIX_EPS) {
					result = false;
				}
			}
		}
	}

	return (result);
}

void S21Matrix::SumMatrix(const S21Matrix& other)
{
	if (_rows != other._rows || _cols != other._cols) {
		throw std::invalid_argument("Different matrix dimensions.");
	}

	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			_matrix[i][j] += other._matrix[i][j];
		}
	}
}

void S21Matrix::SubMatrix(const S21Matrix& other)
{
	if (_rows != other._rows || _cols != other._cols) {
		throw std::invalid_argument("Different matrix dimensions.");
	}

	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			_matrix[i][j] -= other._matrix[i][j];
		}
	}
}

void S21Matrix::MulMatrix(double num)
{
	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			_matrix[i][j] *= num;
		}
	}
}

void S21Matrix::MulMatrix(const S21Matrix& other)
{
	S21Matrix tmp(_rows, other._cols);

	if (_cols != other._rows) {
		throw std::invalid_argument("The matrices are incompatible.");
	}

	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			for (int k = 0; k < _cols; ++k) {
				tmp[i][j] += _matrix[i][k] * other._matrix[k][j];
			}
		}
	}
	_swapMatrix(tmp);
}

S21Matrix S21Matrix::Transpose(void) const
{
	S21Matrix tmp(_cols, _rows);

	for (int i = 0; i < _rows; ++i) {
		for (int j = 0; j < _cols; ++j) {
			tmp[j][i] = _matrix[i][j];
		}
	}

	return (tmp);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	SumMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	SubMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	MulMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator*(double num) const
{
	S21Matrix tmp(*this);

	MulMatrix(num);

	return (tmp);
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept
{
	return (EqMatrix(other));
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other)
{
	if (this != &other) {
		if (_rows != other._rows || _cols != other._cols) {
			S21Matrix(other)._swapMatrix(*this);
		} else {
			_copyMatrix(other);
		}
	}

	return (*this);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other)
{
	SumMatrix(other);

	return (*this);
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other)
{
	SubMatrix(other);

	return (*this);
}

S21Matrix& S21Matrix::operator*=(double num) noexcept
{
	MulMatrix(num);

	return (*this);
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other)
{
	MulMatrix(other);

	return (*this);
}

const double& S21Matrix::operator()(int i, int j) const
{
	if (i < 1 || i > _rows) {
		throw std::out_of_range("Index outside the range of rows.");
	}
	if (j < 1 || j > _cols) {
		throw std::out_of_range("Index outside the range of columns.");
	}

	return (_matrix[i][j]);
}

double& S21Matrix::operator()(int i, int j)
{
	if (i < 1 || i > _rows) {
		throw std::out_of_range("Index outside the range of rows.");
	}
	if (j < 1 || j > _cols) {
		throw std::out_of_range("Index outside the range of columns.");
	}

	return (_matrix[i][j]);
}

void S21Matrix::_allocateMatrix(int rows, int cols)
{
	_matrix = new double*[rows];
	_matrix[0] = new double[rows * cols];
	for (int i = 1; i < rows; ++i) {
		_matrix[i] = _matrix[0] + i * _cols;
	}
}

void S21Matrix::_clearMatrix(void)
{
	delete [] _matrix[0];
	delete [] _matrix;
}

void S21Matrix::_resetMatrix(void) noexcept
{
	memset(_matrix[0], 0, rows * cols * sizeof(double));
}

void S21Matrix::_copyMatrix(const S21Matrix& other) noexcept
{
	memcpy(_matrix[0], other._matrix[0], _rows * _cols * sizeof(double));
}

void S21Matrix::_swapMatrix(const S21Matrix& other) noexcept
{
	std::swap(_rows, other._rows);
	std::swap(_cols, other._cols);
	std::swap(_matrix, other._matrix);
}


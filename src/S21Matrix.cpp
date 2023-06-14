#include <cstring.h>

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(void)
	: _rows(S21_MATRIX_DEFAULT_ROWS),
      _cols(S21_MATRIX_DEFAULT_COLS)
{
	_allocate(S21_MATRIX_DEFAULT_ROWS, S21_MATRIX_DEFAULT_COLS);
	memset(_matrix[0], 0, rows * cols);
}

S21Matrix::S21Matrix(int rows, int cols)
	: _rows(rows), _cols(cols)
{
	assert(_rows > 0);
	assert(_cols > 0);

	_allocate(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix& other)
	: _rows(other._rows), _cols(other._cols)
{
	_allocate(_rows, _cols);
	memcpy(_matrix[0], other._matrix[0], _rows * _cols);
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
		delete [] _matrix[0];
		delete [] _matrix;
	}
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const
{
	return (*this == other);
}

bool S21Matrix::operator==(const S21Matrix& other) const
{
	bool result = true;

	if (_rows != other._rows || _cols != other._cols) {
		result = false;
	} else {
		for (int i = 0; result == true && i < _rows; ++i) {
			for (int j = 0; result == true && j < _cols; ++j) {
				if (_matrix[i][j] != other._matrix[i][j]) {
					result = false;
				}
			}
		}
	}

	return (result);
}

void S21Matrix::_allocate(int rows, int cols)
{
	_matrix = new double*[rows];
	if (_matrix != nullptr) {
		_matrix[0] = new double[rows * cols];
		if (_matrix[0] != nullptr) {
			for (int i = 1; i < rows; ++i) {
				_matrix[i] = matrix + i * cols;
			}
		}
	}
}


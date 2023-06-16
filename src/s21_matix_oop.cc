#include "s21_matrix_oop.h"

#include <cstring>
#include <cmath>
#include <utility>
#include <stdexcept>

const int S21Matrix::kDefaultRows = 1;
const int S21Matrix::kDefaultCols = 1;
const double S21Matrix::kEps = 1.0e-6;

// Constructors and Destructor.

S21Matrix::S21Matrix(void)
	: rows_(kDefaultRows), cols_(kDefaultCols)
{
	_allocateMatrix(kDefaultRows, kDefaultCols);
	_resetMatrix();
}

S21Matrix::S21Matrix(int rows, int cols)
	: rows_(rows), cols_(cols)
{
	if (rows < 1) {
		throw std::invalid_argument("The number of rows is less than 1.");
	}
	if (cols < 1) {
		throw std::invalid_argument("The number of columns is less than 1.");
	}

	_allocateMatrix(rows, cols);
	_resetMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
	: rows_(other.rows_), cols_(other.cols_)
{
	_allocateMatrix(rows_, cols_);
	_copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other)
	: rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_)
{
	other.rows_ = 0;
	other.cols_ = 0;
	other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix(void)
{
	if (matrix_ != nullptr) {
		delete [] matrix_[0];
		delete [] matrix_;
	}
}

// Accessors and Mutators.

int S21Matrix::GetRows(void) const noexcept { return (rows_); }

int S21Matrix::GetCols(void) const noexcept { return (cols_); }

void S21Matrix::SetRows(int rows)
{
	if (rows < 1) {
		throw std::invalid_argument("The number of rows is less than one.");
	}

	if (rows != rows_) {
		S21Matrix tmp(rows, cols_);
		tmp._copyMatrix(*this);
		_swapMatrix(tmp);
	}
}

void S21Matrix::SetCols(int cols)
{
	if (cols < 1) {
		throw std::invalid_argument("The number of rows is less than one.");
	}

	if (cols != cols_) {
		S21Matrix tmp(rows_, cols);
		tmp._copyMatrix(*this);
		_swapMatrix(tmp);
	}
}

// Member Functions.

bool S21Matrix::EqMatrix(const S21Matrix& other) const noexcept
{
	bool result = true;

	if (rows_ != other.rows_ || cols_ != other.cols_) {
		result = false;
	} else {
		for (int i = 0; result == true && i < rows_; ++i) {
			for (int j = 0; result == true && j < cols_; ++j) {
				if (fabs(matrix_[i][j] - other.matrix_[i][j]) > kEps) {
					result = false;
				}
			}
		}
	}

	return (result);
}

void S21Matrix::SumMatrix(const S21Matrix& other)
{
	if (rows_ != other.rows_ || cols_ != other.cols_) {
		throw std::invalid_argument("Different matrix dimensions.");
	}

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] += other.matrix_[i][j];
		}
	}
}

void S21Matrix::SubMatrix(const S21Matrix& other)
{
	if (rows_ != other.rows_ || cols_ != other.cols_) {
		throw std::invalid_argument("Different matrix dimensions.");
	}

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] -= other.matrix_[i][j];
		}
	}
}

void S21Matrix::MulMatrix(double num) noexcept
{
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			matrix_[i][j] *= num;
		}
	}
}

void S21Matrix::MulMatrix(const S21Matrix& other)
{
	S21Matrix tmp(rows_, other.cols_);

	if (cols_ != other.rows_) {
		throw std::invalid_argument("The matrices are incompatible.");
	}

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < other.cols_; ++j) {
			for (int k = 0; k < cols_; ++k) {
				tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
			}
		}
	}
	_swapMatrix(tmp);
}

S21Matrix S21Matrix::Transpose(void) const
{
	S21Matrix tmp(cols_, rows_);

	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			tmp.matrix_[j][i] = matrix_[i][j];
		}
	}

	return (tmp);
}

// Operator Overloading

S21Matrix S21Matrix::operator+(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	tmp.SumMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	tmp.SubMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const
{
	S21Matrix tmp(*this);

	tmp.MulMatrix(other);

	return (tmp);
}

S21Matrix S21Matrix::operator*(double num) const
{
	S21Matrix tmp(*this);

	tmp.MulMatrix(num);

	return (tmp);
}

bool S21Matrix::operator==(const S21Matrix& other) const noexcept
{
	return (EqMatrix(other));
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other)
{
	if (this != &other) {
		if (rows_ != other.rows_ || cols_ != other.cols_) {
			S21Matrix(other)._swapMatrix(*this);
		} else {
			_copyMatrix(other);
		}
	}

	return (*this);
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) noexcept {
	_swapMatrix(other);
	return(*this);
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
	if (i < 0 || i >= rows_) {
		throw std::out_of_range("Index outside the range of rows.");
	}
	if (j < 0 || j >= cols_) {
		throw std::out_of_range("Index outside the range of columns.");
	}

	return (matrix_[i][j]);
}

double& S21Matrix::operator()(int i, int j)
{
	if (i < 0 || i >= rows_) {
		throw std::out_of_range("Index outside the range of rows.");
	}
	if (j < 0 || j >= cols_) {
		throw std::out_of_range("Index outside the range of columns.");
	}

	return (matrix_[i][j]);
}

// Auxiliary private member functions.

void S21Matrix::_allocateMatrix(int rows, int cols)
{
	matrix_ = new double*[rows];
	matrix_[0] = new double[rows * cols];
	for (int i = 1; i < rows; ++i) {
		matrix_[i] = matrix_[0] + i * cols_;
	}
}

void S21Matrix::_resetMatrix(void) noexcept
{
	memset(matrix_[0], 0, rows_ * cols_ * sizeof(matrix_[0][0]));
}

void S21Matrix::_copyMatrix(const S21Matrix& other) noexcept
{
	int min_rows = rows_ <= other.rows_ ? rows_ : other.rows_;
	int min_cols = cols_ <= other.cols_ ? cols_ : other.cols_;

	if (cols_ == other.cols_) {
		memcpy(matrix_[0], other.matrix_[0],
               min_rows * min_cols * sizeof(matrix_[0][0]));
	} else {
		for (int i = 0; i < min_rows; ++i) {
			for (int j = 0; j < min_cols; ++j) {
				matrix_[i][j] = other.matrix_[i][j];
			}
		}
	}
}

void S21Matrix::_swapMatrix(S21Matrix& other) noexcept
{
	std::swap(rows_, other.rows_);
	std::swap(cols_, other.cols_);
	std::swap(matrix_, other.matrix_);
}


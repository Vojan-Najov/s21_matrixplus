#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <cstring>
#include <cmath>
#include <utility>
#include <stdexcept>

class S21Matrix {
  public:
	static const int kDefaultRows;
	static const int kDefaultCols;
	static const double kEps; // = 1.0e-6;

	S21Matrix(void);
	explicit S21Matrix(int rows, int cols);
	S21Matrix(const S21Matrix& other);
	S21Matrix(S21Matrix&& other);
	~S21Matrix(void);

	bool EqMatrix(const S21Matrix& other) const noexcept;
	void SumMatrix(const S21Matrix& other);
	void SubMatrix(const S21Matrix& other);
	void MulMatrix(double num) noexcept;
	void MulMatrix(const S21Matrix& other);
	S21Matrix Transpose(void) const;
	S21Matrix CalcComplements(void) const;
	double Determinant(void) const;
	S21Matrix InverseMatrix(void) const;

	S21Matrix operator+(const S21Matrix& other) const;
	S21Matrix operator-(const S21Matrix& other) const;
	S21Matrix operator*(const S21Matrix& other) const;
	S21Matrix operator*(double num) const;
	bool operator==(const S21Matrix& other) const noexcept;
	S21Matrix& operator=(const S21Matrix& other);
	S21Matrix& operator+=(const S21Matrix& other);
	S21Matrix& operator-=(const S21Matrix& other);
	S21Matrix& operator*=(const S21Matrix& other);
	S21Matrix& operator*=(double num) noexcept;
	const double& operator()(int i, int j) const;
	double& operator()(int i, int j);

	int GetRows(void) const noexcept;
	int GetCols(void) const noexcept;
	void SetRows(int rows);
	void SetCols(int cols);
	
  private:
	int rows_;
	int cols_;
	double **matrix_;

	void _allocateMatrix(int rows, int cols);
	void _clearMatrix(void);
	void _resetMatrix(void) noexcept;
	void _copyMatrix(const S21Matrix& other) noexcept;
	void _swapMatrix(S21Matrix& other) noexcept;
};

#endif  // S21_MATRIX_OOP_H_


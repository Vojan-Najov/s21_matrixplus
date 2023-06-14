#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

#ifndef S21_DEFAULT_ROWS
#define S21_DEFAULT_ROWS 3
#endif

#ifndef S21_MATRIX_DEFAULT_COLS
#define S21_MATRIX_DEFAULT_COLS 3
#endif

#ifndef S21_MATRIX_EPS
#define S21_MATRIX_EPS 1.0e-6
#endif

class S21Matrix {
  public:
	S21Matrix(void);
	S21Matrix(int rows, int cols);
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
	S21Matrix operator*(double num) const noexcept;
	bool operator==(const S21Matrix& other) const noexcept;
	S21Matrix& operator=(const S21Matrix& other);
	S21Matrix& operator+=(const S21Matrix& other);
	S21Matrix& operator-=(const S21Matrix& other);
	S21Matrix& operator*=(const S21Matrix& other);
	S21Matrix& operator*=(double num) noexcept;
	const double& operator()(int i, int j) const;
	double& operator()(int i, int j);
	
  private:
	int _rows;
	int _cols;
	double **_matrix;

	void _allocateMatrix(int rows, int cols);
	void _clearMatrix(void);
	void _resetMatrix(void) noexcept;
	void _copyMatrix(const S21Matrix& other) noexcept;
	void _swapMatrix(const S21Matrix& other) noexcept;
};

#endif


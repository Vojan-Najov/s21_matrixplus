#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

class S21Matrix {
  public:
	S21Matrix(void);
	S21Matrix(int rows, int cols);
	S21Matrix(const S21Matrix& other);
	S21Matrix(S21Matrix&& other);
	~S21Matrix(void);

	bool EqMatrix(const S21Matrix& other) const;
	void SumMatrix(const S21Matrix& other);
	void SubMatrix(const S21Matrix& other);
	void MulMatrix(const double num);
	void MulMatrix(const S21Matrix& other);
	S21Matrix Transpose(void) const;
	S21Matrix CalcComplements(void) const;
	double Determinant(void) const;
	S21Matrix InverseMatrix(void) const;

	S21Matrix operator+(const S21Matrix& other) const;
	S21Matrix operator-(const S21Matrix& other) const;
	S21Matrix operator*(const S21Matrix& other) const;
	S21Matrix operator*(double num) const;
	bool operator==(const S21Matrix& other) const;
	S21Matrix& operator=(const S21Matrix& other);
	S21Matrix& operator+=(const S21Matrix& other);
	S21Matrix& operator-=(const S21Matrix& other);
	S21Matrix& operator*=(const S21Matrix& other);
	S21Matrix& operator*=(double num);
	const double& operator()(int i, int j) const;
	double& operator()(int i, int j);
	
  private:
	int _rows;
	int _cols;
	double **_matrix;
};

#endif


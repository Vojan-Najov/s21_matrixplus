#ifndef __S21_MATRIX_OOP_H__
#define __S21_MATRIX_OOP_H__

class S21Matrix {
  public:
	S21Matrix(void);
	S21Matrix(int rows, int cols);
	S21Matrix(const S21Matrix& other);
	S21Matrix(S21Matrix&& other);
	~S21Matrix(void);

	bool EqMatrix(const S21Matrix& other);
	void SumMatrix(const S21Matrix& other);
	void SubMatrix(const S21Matrix& other);
	void MulMatrix(const double num);
	void MulMatrix(const S21Matrix& other);
	S21Matrix Transpose(void);
	S21Matrix CalcComplements(void);
	double Determinant(void);
	S21Matrix InverseMatrix(void);

	
	
  private:
	int rows_;
	int cols_;
	double **matrix;
};

#endif


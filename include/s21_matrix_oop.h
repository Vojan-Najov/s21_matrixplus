#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

class S21Matrix {
 public:
  static const double kEps;
  static const int kDefaultRows;
  static const int kDefaultCols;

  S21Matrix(void);
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;

  ~S21Matrix(void);

  int rows(void) const noexcept;
  int cols(void) const noexcept;
  void set_rows(int rows);
  void set_cols(int cols);
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
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(double num) noexcept;
  const double& operator()(int i, int j) const;
  double& operator()(int i, int j);

 private:
  int rows_;
  int cols_;
  double** matrix_;

  void AllocateMatrix(int rows, int cols);
  void ResetMatrix(void) noexcept;
  void CopyMatrix(const S21Matrix& other) noexcept;
  void SwapMatrix(S21Matrix& other) noexcept;
  S21Matrix Minor(int row, int col) const;
};

#endif  // S21_MATRIX_OOP_H_

#include <gtest/gtest.h>

#include <utility>

#include "s21_matrix_oop.h"

// Tests for constructors and destructor

TEST(MatrixConstructorDestructor, DefaultConstructor) {
  S21Matrix m;

  EXPECT_EQ(m.GetRows(), S21Matrix::kDefaultRows);
  EXPECT_EQ(m.GetCols(), S21Matrix::kDefaultCols);
  for (int i = 0; i < S21Matrix::kDefaultRows; ++i) {
    for (int j = 0; j < S21Matrix::kDefaultCols; ++j) {
      EXPECT_EQ(m(i, j), 0.0);
    }
  }
}

TEST(MatrixConstructorDestructor, ConvertingConstructor) {
  int rows = 100;
  int cols = 87;
  S21Matrix m(rows, cols);

  EXPECT_EQ(m.GetRows(), rows);
  EXPECT_EQ(m.GetCols(), cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m(i, j), 0.0);
    }
  }
}

TEST(MatrixConstructorDestructor, ConvertingConstructorBadRows) {
  int rows = -2;
  int cols = 87;

  EXPECT_THROW(S21Matrix(rows, cols), std::invalid_argument);

  rows = 0;
  EXPECT_THROW(S21Matrix(rows, cols), std::invalid_argument);
}

TEST(MatrixConstructorDestructor, ConvertingConstructorBadCols) {
  int rows = 123;
  int cols = -87;

  EXPECT_THROW(S21Matrix(rows, cols), std::invalid_argument);

  cols = 0;
  EXPECT_THROW(S21Matrix(rows, cols), std::invalid_argument);
}

TEST(MatrixConstructorDestructor, CopyConstructor) {
  int rows = 123;
  int cols = 112;

  S21Matrix m(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m(i, j) = i * 1.12 + j * 2.12;
    }
  }

  S21Matrix copy(m);
  EXPECT_EQ(m.GetRows(), copy.GetRows());
  EXPECT_EQ(m.GetCols(), copy.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m(i, j), copy(i, j));
    }
  }
}

TEST(MatrixConstructorDestructor, MoveConstructor) {
  int rows = 123;
  int cols = 112;

  S21Matrix m(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m(i, j) = i * 1.12 + j * 2.12;
    }
  }

  S21Matrix copy(m);
  S21Matrix move = S21Matrix(std::move(copy));
  EXPECT_EQ(m.GetRows(), move.GetRows());
  EXPECT_EQ(m.GetCols(), move.GetCols());
  EXPECT_EQ(copy.GetRows(), 0);
  EXPECT_EQ(copy.GetCols(), 0);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m(i, j), move(i, j));
    }
  }
}

// Tests for accessors and mutators

TEST(MatrixAccessorMutator, RowsColsAccessor) {
  int rows = 1111;
  int cols = 249;

  S21Matrix m(rows, cols);
  EXPECT_EQ(m.GetRows(), rows);
  EXPECT_EQ(m.GetCols(), cols);
}

TEST(MatrixAccessorMutator, GreaterRowsMutator) {
  int rows = 91;
  int new_rows = 106;
  int cols = 14;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetRows(new_rows);
  EXPECT_EQ(m2.GetRows(), new_rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
  for (int i = rows; i < new_rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), 0.0);
    }
  }
}

TEST(MatrixAccessorMutator, LessRowsMutator) {
  int rows = 91;
  int new_rows = 80;
  int cols = 14;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetRows(new_rows);
  EXPECT_EQ(m2.GetRows(), new_rows);
  for (int i = 0; i < new_rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
}

TEST(MatrixAccessorMutator, EqualRowsMutator) {
  int rows = 91;
  int cols = 14;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetRows(rows);
  EXPECT_EQ(m2.GetRows(), rows);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
}

TEST(MatrixAccessorMutator, BadRowsMutator) {
  int rows = 91;
  int cols = 14;

  int new_rows = 0;
  S21Matrix m(rows, cols);
  EXPECT_THROW(m.SetRows(new_rows), std::invalid_argument);
  new_rows = -16;
  EXPECT_THROW(m.SetRows(new_rows), std::invalid_argument);
}

TEST(MatrixAccessorMutator, GreaterColsMutator) {
  int rows = 91;
  int cols = 14;
  int new_cols = 106;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetCols(new_cols);
  EXPECT_EQ(m2.GetCols(), new_cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
  for (int i = 0; i < rows; ++i) {
    for (int j = cols; j < new_cols; ++j) {
      EXPECT_EQ(m2(i, j), 0.0);
    }
  }
}

TEST(MatrixAccessorMutator, LessColsMutator) {
  int rows = 91;
  int cols = 80;
  int new_cols = 14;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetCols(new_cols);
  EXPECT_EQ(m2.GetCols(), new_cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < new_cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
}

TEST(MatrixAccessorMutator, EqualColsMutator) {
  int rows = 91;
  int cols = 14;

  S21Matrix m1(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = i * 1.12 + j * 2.27 + 0.99;
    }
  }

  S21Matrix m2(m1);
  m2.SetCols(cols);
  EXPECT_EQ(m2.GetCols(), cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m2(i, j), m1(i, j)) << "i = " << i << "  j = " << j;
    }
  }
}

TEST(MatrixAccessorMutator, BadColsMutator) {
  int rows = 91;
  int cols = 14;

  int new_cols = 0;
  S21Matrix m(rows, cols);
  EXPECT_THROW(m.SetCols(new_cols), std::invalid_argument);
  new_cols = -16;
  EXPECT_THROW(m.SetCols(new_cols), std::invalid_argument);
}

// Tests for EqMatrix

TEST(MatrixEq, OtherCols) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 11);

  EXPECT_EQ(m1.EqMatrix(m2), false);
  EXPECT_EQ(m2.EqMatrix(m1), false);
}

TEST(MatrixEq, OtherRows) {
  S21Matrix m1(11, 14);
  S21Matrix m2(12, 14);

  EXPECT_EQ(m1.EqMatrix(m2), false);
  EXPECT_EQ(m2.EqMatrix(m1), false);
}

TEST(MatrixEq, OtherRowsCols) {
  S21Matrix m1(12, 14);
  S21Matrix m2(11, 11);

  EXPECT_EQ(m1.EqMatrix(m2), false);
  EXPECT_EQ(m2.EqMatrix(m1), false);
}

TEST(MatrixEq, Equal) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  EXPECT_EQ(m1.EqMatrix(m2), true);
  EXPECT_EQ(m2.EqMatrix(m1), true);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  EXPECT_EQ(m1.EqMatrix(m2), true);
  EXPECT_EQ(m2.EqMatrix(m1), true);
}

TEST(MatrixEq, NotEqual) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }

  m1(2, 5) += 0.00143;
  EXPECT_EQ(m1.EqMatrix(m2), false);
  EXPECT_EQ(m2.EqMatrix(m1), false);
  m1(2, 5) = m2(2, 5);
  m1(m1.GetRows() - 1, m1.GetCols() - 1) -= 0.0001;
  EXPECT_EQ(m1.EqMatrix(m2), false);
  EXPECT_EQ(m2.EqMatrix(m1), false);
}

// Tests for SumMatrix

TEST(MatrixSum, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixSum, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixSum, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixSum, SumMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a + b;
    }
  }

  m1.SumMatrix(m2);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(i, j));
    }
  }
}

// Tests for SubMatrix

TEST(MatrixSub, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixSub, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixSub, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixSub, SubMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a - b;
    }
  }

  m1.SubMatrix(m2);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(i, j));
    }
  }
}

// Tests for MulMatrix on num

TEST(MatrixMulNum, MulMatrix) {
  int rows = 9;
  int cols = 10;
  double ratio = -17.123;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = m2(i, j) = 1.23 + i * 16.123 + j * 4.123;
      m2(i, j) *= ratio;
    }
  }

  m1.MulMatrix(ratio);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m2(i, j));
    }
  }
}

// Tests for MulMatrix on matrix

TEST(MatrixMulMatrix, IncompatibleMatrices) {
  S21Matrix m1(19, 16);
  S21Matrix m2(18, 17);

  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);

  S21Matrix a1(14, 15);
  S21Matrix a2(14, 15);
  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

TEST(MatrixMulMatrix, SquareMatrices) {
  double a[3][3] = {{-1.0, 2.0, 5.0}, {3.0, 4.0, 6.0}, {-8.0, 2.0, 12.0}};
  double b[3][3] = {{-2.0, 2.0, 19.1}, {5.0, 7.0, 17.7}, {-1.0, 4.0, -13.56}};
  double c[3][3] = {
      {7.0, 32.0, -51.5}, {8.0, 58.0, 46.74}, {14.0, 46.0, -280.12}};

  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  S21Matrix m3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1(i, j) = a[i][j];
      m2(i, j) = b[i][j];
      m3(i, j) = c[i][j];
    }
  }

  m1.MulMatrix(m2);
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(m1(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

TEST(MatrixMulMatrix, RectangleMatrices) {
  double a[3][4] = {
      {-1.0, 2.0, 5.0, 78.45}, {3.0, 4.0, 6.0, 19.01}, {-8.0, 2.0, 12.0, 0.43}};
  double b[4][5] = {{-2.0, 2.0, 19.1, 0.5, 0.001},
                    {5.0, 7.0, 17.7, -0.9, -18.78},
                    {-1.0, 4.0, -13.56, 189.1, 19.43},
                    {18.1, 0.3, -17.1, 1983.14, 0.93}};
  double c[3][5] = {{1426.945, 55.535, -1392.995, 156520.533, 132.5475},
                    {352.081, 63.703, -278.331, 38831.9914, 59.1423},
                    {21.783, 46.129, -287.473, 3116.1502, 195.9919}};

  S21Matrix m1(3, 4);
  S21Matrix m2(4, 5);
  S21Matrix m3(3, 5);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      m1(i, j) = a[i][j];
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      m2(i, j) = b[i][j];
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      m3(i, j) = c[i][j];
    }
  }

  m1.MulMatrix(m2);
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < m3.GetRows(); ++i) {
    for (int j = 0; j < m3.GetCols(); ++j) {
      EXPECT_NEAR(m1(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

// Tests for Transpose

TEST(MatrixTranspose, SquareMatrix) {
  int rows = 97;
  int cols = 97;
  S21Matrix m1(rows, cols);
  S21Matrix m2(cols, rows);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = m2(j, i) = 192.123 + i * 17.123 - j * 9.87;
    }
  }
  S21Matrix m3(m1.Transpose());
  EXPECT_EQ(m1.GetRows(), m3.GetCols());
  EXPECT_EQ(m1.GetCols(), m3.GetRows());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(j, i));
    }
  }
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      EXPECT_EQ(m2(i, j), m3(i, j));
    }
  }
}

TEST(MatrixTranspose, RectangleMatrix) {
  int rows = 97;
  int cols = 197;
  S21Matrix m1(rows, cols);
  S21Matrix m2(cols, rows);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = m2(j, i) = 192.123 + i * 17.123 - j * 9.87;
    }
  }
  S21Matrix m3(m1.Transpose());
  EXPECT_EQ(m1.GetRows(), m3.GetCols());
  EXPECT_EQ(m1.GetCols(), m3.GetRows());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(j, i));
    }
  }
  for (int i = 0; i < cols; ++i) {
    for (int j = 0; j < rows; ++j) {
      EXPECT_EQ(m2(i, j), m3(i, j));
    }
  }
}

// Tests for CalcComplemnts

TEST(MatrixCalcComplements, Matrix1x1) {
  S21Matrix m1(1, 1);
  S21Matrix m2(1, 1);

  m1(0, 0) = 0.0;
  EXPECT_THROW(m1.CalcComplements(), std::invalid_argument);

  m2(0, 0) = 100.0;
  S21Matrix comp = m2.CalcComplements();
  EXPECT_EQ(comp.GetRows(), 1);
  EXPECT_EQ(comp.GetCols(), 1);
  EXPECT_EQ(comp(0, 0), 1.0);
}

TEST(MatrixCalcComplements, Matrix2x2) {
  double a[2][2] = {{15.87, 78.98}, {47.25, -45.478}};
  double b[2][2] = {{-45.478, -47.25}, {-78.98, 15.87}};

  S21Matrix ma(2, 2);
  S21Matrix mb(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix comp = ma.CalcComplements();
  EXPECT_TRUE(comp == mb);
}

TEST(MatrixCalcComplements, Matrix3x3) {
  double a[3][3] = {{1., 2., 3.}, {0., 4., 2.}, {5., 2., 1.}};
  double b[3][3] = {{0., 10., -20.}, {4., -14., 8.}, {-8., -2., 4.}};

  S21Matrix ma(3, 3);
  S21Matrix mb(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix comp = ma.CalcComplements();
  EXPECT_TRUE(comp == mb);
}

TEST(MatrixCalcComplements, Matrix4x4) {
  double a[4][4] = {
      {4., 5., 9., 8.}, {4., 1., 2., 3.}, {8., 7., 15., 4.}, {7., 6., 4., 9}};
  double b[4][4] = {{-145., -169., 109., 177.},
                    {252., -504., 72., 108.},
                    {47., 95., 25., -111.},
                    {24., 276., -132., -36.}};

  S21Matrix ma(4, 4);
  S21Matrix mb(4, 4);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix comp = ma.CalcComplements();
  EXPECT_TRUE(comp == mb);
}

TEST(MatrixCalcComplements, Matrix5x5) {
  double a[5][5] = {{78., 951., 147., 47., 52.},
                    {76., 98., 78., 753., -89.},
                    {87., 457., 253., 984., -71.},
                    {47., 453., 786., 123., 357.},
                    {765., -896., 783., 478., 456}};
  double b[5][5] = {
      {892211883., -9088259207., 44376427597., -13166556043., -81751647719.},
      {97617917421., -13672761316., 251606522691., -104032036661.,
       -513616435766.},
      {-71997449493., 10510919457., -193843105045., 72992451018.,
       397773228858.},
      {25486500814., -1504267981., 29580687324., -14989913303., -80792756249.},
      {-12212500158., 1182045334., -9293332343., 4297527901., 19088191207}};

  S21Matrix ma(5, 5);
  S21Matrix mb(5, 5);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix comp = ma.CalcComplements();
  EXPECT_TRUE(comp == mb);
}

TEST(MatrixCalcComplements, RectangleMatrix) {
  S21Matrix m1(19, 18);
  S21Matrix m2(21, 43);

  EXPECT_THROW(m1.CalcComplements(), std::invalid_argument);
  EXPECT_THROW(m2.CalcComplements(), std::invalid_argument);
}

// Tests for Determinant

TEST(MatrixDeterminant, Matrix1x1) {
  double dt = 1183.2019381738;
  S21Matrix m(1, 1);

  m(0, 0) = dt;
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, Matrix2x2) {
  double a[2][2] = {{179.38, 18.91}, {2.18821, 472.9428}};
  double dt = 84795.1004129;
  S21Matrix m(2, 2);

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      m(i, j) = a[i][j];
    }
  }
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, Matrix3x3) {
  double a[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {5.0, 7.0, 9.0}};
  double dt = 0.0;
  S21Matrix m(3, 3);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m(i, j) = a[i][j];
    }
  }
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, Matrix5x5) {
  double a[5][5] = {{3.0, 2.0, -6.0, 2.0, -6.0},
                    {-4.0, 17.0, 7.0, 17.0, 7.0},
                    {1.0, 2.0, 9.0, -3.0, 4.0},
                    {12.0, 3.0, 3.0, 2.0, 9.0},
                    {-1.0, -2.0, 4.0, 8.0, -1.0}};
  double dt = -158255.0;

  S21Matrix m(5, 5);
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      m(i, j) = a[i][j];
    }
  }
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, Matrix6x6) {
  double a[6][6] = {{1.1, 1.2, 1.3, 1.4, 1.5, 1.6},
                    {2.8, -2.9, -2.3, -2.4, 2.5, 2.7},
                    {3.33, 3.2, -3.87, 3.99, 3.47, -3.02},
                    {4.85, 4.23, 4.32, -4.18, 4.89, 4.23},
                    {5.12, 5.32, 5.28, 5.67, -5.73, 5.91},
                    {6.15, -6.53, 6.44, 6.32, 6.78, 6.98}};
  double dt = -77591.0 - (269266237810933.0 / 3733527061589101.0);

  S21Matrix m(6, 6);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      m(i, j) = a[i][j];
    }
  }
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, Matrix6x6_2) {
  double a[6][6] = {{0.0, 1.2, 1.3, 1.4, 1.5, 1.6},
                    {0.0, -2.9, -2.3, -2.4, 2.5, 2.7},
                    {0.0, 3.2, -3.87, 3.99, 3.47, -3.02},
                    {0.0, 4.23, 4.32, -4.18, 4.89, 4.23},
                    {0.0, 5.32, 5.28, 5.67, -5.73, 5.91},
                    {0.0, -6.53, 6.44, 6.32, 6.78, 6.98}};
  double dt = 0.0;

  S21Matrix m(6, 6);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      m(i, j) = a[i][j];
    }
  }
  EXPECT_NEAR(dt, m.Determinant(), S21Matrix::kEps);
}

TEST(MatrixDeterminant, RectangleMatrix) {
  S21Matrix m1(1, 2);
  S21Matrix m2(115, 23);

  EXPECT_THROW(m1.Determinant(), std::invalid_argument);
  EXPECT_THROW(m2.Determinant(), std::invalid_argument);
}

// Tests for InverseMatrix

TEST(MatrixInverse, Matrix1x1) {
  double a = 125480.4;
  double b = 5.0 / 627402.0;

  S21Matrix m(1, 1);
  m(0, 0) = a;
  S21Matrix inverse = m.InverseMatrix();
  EXPECT_EQ(inverse.GetRows(), m.GetRows());
  EXPECT_EQ(inverse.GetCols(), m.GetCols());
  EXPECT_NEAR(inverse(0, 0), b, S21Matrix::kEps);
}

TEST(MatrixInverse, Matrix3x3) {
  double a[3][3] = {{2., 5., 7.}, {6., 3., 4.}, {5., -2., -3.}};
  double b[3][3] = {{1., -1., 1.}, {-38., 41., -34.}, {27., -29., 24.}};

  S21Matrix ma(3, 3);
  S21Matrix mb(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix inverse = ma.InverseMatrix();
  EXPECT_TRUE(inverse == mb);
}

TEST(MatrixInverse, Matrix6x6) {
  double a[6][6] = {
      {12., 47., 58., 47., 42., 14.},   {47., 59., 63., 54., 89., 12.},
      {15., 56., -65., -97., 32., 16.}, {58., 75., -24., 45., -16., 8.},
      {78., 93., 17., 13., -11., 7.},   {84., 65., 19., -35., 54., 18.}};
  double b[6][6] = {{-0.01, -0.001, -0.009, 0.006, -0.005, 0.016},
                    {0.0, 0.008, 0.01, -0.007, 0.018, -0.018},
                    {0.009, -0.005, -0.004, -0.014, 0.011, 0.002},
                    {0.001, 0.003, -0.004, 0.012, -0.009, -0.001},
                    {-0.011, 0.017, 0.005, -0.001, -0.004, -0.005},
                    {0.075, -0.067, -0.012, 0.04, -0.061, 0.058}};

  S21Matrix ma(6, 6);
  S21Matrix mb(6, 6);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      ma(i, j) = a[i][j];
      mb(i, j) = b[i][j];
    }
  }

  S21Matrix inverse = ma.InverseMatrix();
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      EXPECT_NEAR(inverse(i, j), b[i][j], 1.0e-3);
    }
  }
}

TEST(MatrixInverse, NoExist) {
  double a[3][3] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {5.0, 7.0, 9.0}};

  S21Matrix m(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m(i, j) = a[i][j];
    }
  }

  EXPECT_THROW(m.InverseMatrix(), std::invalid_argument);
}

TEST(MatrixInverse, NoExist2) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 0.0;
  EXPECT_THROW(m1.InverseMatrix(), std::invalid_argument);

  S21Matrix m2(13, 10);
  EXPECT_THROW(m2.InverseMatrix(), std::invalid_argument);

  S21Matrix m3(9, 10);
  EXPECT_THROW(m3.InverseMatrix(), std::invalid_argument);
}

// Tests for operator+

TEST(MatrixOperatorPlus, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 + m2, std::invalid_argument);
  EXPECT_THROW(m2 + m1, std::invalid_argument);
}

TEST(MatrixOperatorPlus, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 + m2, std::invalid_argument);
  EXPECT_THROW(m2 + m1, std::invalid_argument);
}

TEST(MatrixOperatorPlus, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1 + m2, std::invalid_argument);
  EXPECT_THROW(m2 + m1, std::invalid_argument);
}

TEST(MatrixOperatorPlus, SumMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a + b;
    }
  }

  S21Matrix sum(m1 + m2);
  EXPECT_EQ(sum.GetRows(), m3.GetRows());
  EXPECT_EQ(sum.GetCols(), m3.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(sum(i, j), m3(i, j));
      EXPECT_EQ(sum(i, j), m1(i, j) + m2(i, j));
    }
  }
}

// Tests for operator-

TEST(MatrixOperatorMinus, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 - m2, std::invalid_argument);
  EXPECT_THROW(m2 - m1, std::invalid_argument);
}

TEST(MatrixOperatorMinus, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 - m2, std::invalid_argument);
  EXPECT_THROW(m2 - m1, std::invalid_argument);
}

TEST(MatrixOperatorMinus, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1 - m2, std::invalid_argument);
  EXPECT_THROW(m2 - m1, std::invalid_argument);
}

TEST(MatrixOperatorMinus, SubMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a - b;
    }
  }

  S21Matrix sub(m1 - m2);
  EXPECT_EQ(sub.GetRows(), m3.GetRows());
  EXPECT_EQ(sub.GetCols(), m3.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(sub(i, j), m3(i, j));
      EXPECT_EQ(sub(i, j), m1(i, j) - m2(i, j));
    }
  }
}

// Tests for operator* num

TEST(MatrixOperatorMulNum, MulMatrixNum) {
  int rows = 9;
  int cols = 10;
  double ratio = -17.123;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = m2(i, j) = 1.23 + i * 16.123 + j * 4.123;
      m2(i, j) *= ratio;
    }
  }

  S21Matrix mul(m1 * ratio);
  EXPECT_EQ(mul.GetRows(), m2.GetRows());
  EXPECT_EQ(mul.GetCols(), m2.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(mul(i, j), m2(i, j));
      EXPECT_EQ(mul(i, j), m1(i, j) * ratio);
    }
  }
}

// Tests for operator* matrix

TEST(MatrixOperatorMulMatrix, IncompatibleMatrices) {
  S21Matrix m1(19, 16);
  S21Matrix m2(18, 17);

  EXPECT_THROW(m1 * m2, std::invalid_argument);

  S21Matrix a1(14, 15);
  S21Matrix a2(14, 15);
  EXPECT_THROW(m1 * m2, std::invalid_argument);
}

TEST(MatrixOperatorMulMatrix, SquareMatrices) {
  double a[3][3] = {{-1.0, 2.0, 5.0}, {3.0, 4.0, 6.0}, {-8.0, 2.0, 12.0}};
  double b[3][3] = {{-2.0, 2.0, 19.1}, {5.0, 7.0, 17.7}, {-1.0, 4.0, -13.56}};
  double c[3][3] = {
      {7.0, 32.0, -51.5}, {8.0, 58.0, 46.74}, {14.0, 46.0, -280.12}};

  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  S21Matrix m3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1(i, j) = a[i][j];
      m2(i, j) = b[i][j];
      m3(i, j) = c[i][j];
    }
  }

  S21Matrix mul(m1 * m2);
  EXPECT_EQ(mul.GetRows(), m3.GetRows());
  EXPECT_EQ(mul.GetCols(), m3.GetCols());
  for (int i = 0; i < m3.GetRows(); ++i) {
    for (int j = 0; j < m3.GetCols(); ++j) {
      EXPECT_NEAR(mul(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

TEST(MatrixOperatorMulMatrix, RectangleMatrices) {
  double a[3][4] = {
      {-1.0, 2.0, 5.0, 78.45}, {3.0, 4.0, 6.0, 19.01}, {-8.0, 2.0, 12.0, 0.43}};
  double b[4][5] = {{-2.0, 2.0, 19.1, 0.5, 0.001},
                    {5.0, 7.0, 17.7, -0.9, -18.78},
                    {-1.0, 4.0, -13.56, 189.1, 19.43},
                    {18.1, 0.3, -17.1, 1983.14, 0.93}};
  double c[3][5] = {{1426.945, 55.535, -1392.995, 156520.533, 132.5475},
                    {352.081, 63.703, -278.331, 38831.9914, 59.1423},
                    {21.783, 46.129, -287.473, 3116.1502, 195.9919}};

  S21Matrix m1(3, 4);
  S21Matrix m2(4, 5);
  S21Matrix m3(3, 5);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      m1(i, j) = a[i][j];
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      m2(i, j) = b[i][j];
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      m3(i, j) = c[i][j];
    }
  }

  S21Matrix mul(m1 * m2);
  EXPECT_EQ(mul.GetRows(), m3.GetRows());
  EXPECT_EQ(mul.GetCols(), m3.GetCols());
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_NEAR(mul(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

// Tests for operator==

TEST(MatrixOperatorEqual, OtherCols) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 11);

  EXPECT_EQ(m1 == m2, false);
  EXPECT_EQ(m2 == m1, false);
}

TEST(MatrixOperatorEqual, OtherRows) {
  S21Matrix m1(11, 14);
  S21Matrix m2(12, 14);

  EXPECT_EQ(m1 == m2, false);
  EXPECT_EQ(m2 == m1, false);
}

TEST(MatrixOperatorEqual, OtherRowsCols) {
  S21Matrix m1(12, 14);
  S21Matrix m2(11, 11);

  EXPECT_EQ(m1 == m2, false);
  EXPECT_EQ(m2 == m1, false);
}

TEST(MatrixOperatorEqual, Equal) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  EXPECT_EQ(m1.EqMatrix(m2), true);
  EXPECT_EQ(m2.EqMatrix(m1), true);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  EXPECT_EQ(m1 == m2, true);
  EXPECT_EQ(m2 == m1, true);
}

TEST(MatrixOperatorEqual, NotEqual) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }

  m1(2, 5) += 0.00143;
  EXPECT_EQ(m1 == m2, false);
  EXPECT_EQ(m2 == m1, false);
  m1(2, 5) = m2(2, 5);
  m1(m1.GetRows() - 1, m1.GetCols() - 1) -= 0.0001;
  EXPECT_EQ(m1 == m2, false);
  EXPECT_EQ(m2 == m1, false);
}

// Tests for operator=

TEST(MatrixOperatorAssign, SameDimension) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
    }
  }

  m2 = m1;
  EXPECT_EQ(m2.GetRows(), m1.GetRows());
  EXPECT_EQ(m2.GetCols(), m1.GetCols());
  EXPECT_TRUE(m2 == m1);
}

TEST(MatrixOperatorAssign, DifferentDimensionLess) {
  S21Matrix m1(12, 14);
  S21Matrix m2(20, 21);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  for (int i = 0; i < m2.GetRows(); ++i) {
    for (int j = 0; j < m2.GetCols(); ++j) {
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
    }
  }

  m2 = m1;
  EXPECT_EQ(m2.GetRows(), m1.GetRows());
  EXPECT_EQ(m2.GetCols(), m1.GetCols());
  EXPECT_TRUE(m2 == m1);
}

TEST(MatrixOperatorAssign, DifferentDimensionGreater) {
  S21Matrix m1(20, 21);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  for (int i = 0; i < m2.GetRows(); ++i) {
    for (int j = 0; j < m2.GetCols(); ++j) {
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
    }
  }

  m2 = m1;
  EXPECT_EQ(m2.GetRows(), m1.GetRows());
  EXPECT_EQ(m2.GetCols(), m1.GetCols());
  EXPECT_TRUE(m2 == m1);
}

TEST(MatrixOperatorAssign, SelfAssign) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }

  m2 = m2;
  EXPECT_EQ(m2.GetRows(), m1.GetRows());
  EXPECT_EQ(m2.GetCols(), m1.GetCols());
  EXPECT_TRUE(m2 == m1);
}

// Tests for move operator=

TEST(MatrixMoveOperatorAssign, SameDimension) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);
  S21Matrix m3(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
      m3(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }

  m2 = std::move(m1);
  EXPECT_EQ(m2.GetRows(), m3.GetRows());
  EXPECT_EQ(m2.GetCols(), m3.GetCols());
  EXPECT_TRUE(m2 == m3);
}

TEST(MatrixMoveOperatorAssign, DifferentDimensionLess) {
  S21Matrix m1(12, 14);
  S21Matrix m2(20, 21);
  S21Matrix m3(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m3(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  for (int i = 0; i < m2.GetRows(); ++i) {
    for (int j = 0; j < m2.GetCols(); ++j) {
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
    }
  }

  m2 = std::move(m1);
  EXPECT_EQ(m2.GetRows(), m3.GetRows());
  EXPECT_EQ(m2.GetCols(), m3.GetCols());
  EXPECT_TRUE(m2 == m3);
}

TEST(MatrixMoveOperatorAssign, DifferentDimensionGreater) {
  S21Matrix m1(20, 21);
  S21Matrix m2(12, 14);
  S21Matrix m3(20, 21);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m3(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }
  for (int i = 0; i < m2.GetRows(); ++i) {
    for (int j = 0; j < m2.GetCols(); ++j) {
      m2(i, j) = 0.12345 - i * 19.141 + j * 8.3;
    }
  }

  m2 = std::move(m1);
  EXPECT_EQ(m2.GetRows(), m3.GetRows());
  EXPECT_EQ(m2.GetCols(), m3.GetCols());
  EXPECT_TRUE(m2 == m3);
}

/*
TEST(MatrixMoveOperatorAssign, SelfAssign) {
  S21Matrix m1(12, 14);
  S21Matrix m2(12, 14);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = 0.12345 + i * 19.141 + j * 8.3;
      m2(i, j) = 0.12345 + i * 19.141 + j * 8.3;
    }
  }

  m2 = std::move(m2);
  EXPECT_EQ(m2.GetRows(), m1.GetRows());
  EXPECT_EQ(m2.GetCols(), m1.GetCols());
  EXPECT_TRUE(m2 == m1);
}
*/

// Tests for operator+=

TEST(MatrixOperatorPlusAssign, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 += m2, std::invalid_argument);
  EXPECT_THROW(m2 += m1, std::invalid_argument);
}

TEST(MatrixOperatorPlusAssign, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 += m2, std::invalid_argument);
  EXPECT_THROW(m2 += m1, std::invalid_argument);
}

TEST(MatrixOperatorPlusAssign, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1 += m2, std::invalid_argument);
  EXPECT_THROW(m2 += m1, std::invalid_argument);
}

TEST(MatrixOperatorPlusAssign, SumMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a + b;
    }
  }

  m1 += m2;
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(i, j));
    }
  }
}

// Tests for operator-=

TEST(MatrixOperatorMinusAssign, OtherRows) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 -= m2, std::invalid_argument);
  EXPECT_THROW(m2 -= m1, std::invalid_argument);
}

TEST(MatrixOperatorMinusAssign, OtherCols) {
  S21Matrix m1(10, 11);
  S21Matrix m2(10, 12);

  EXPECT_THROW(m1 -= m2, std::invalid_argument);
  EXPECT_THROW(m2 -= m1, std::invalid_argument);
}

TEST(MatrixOperatorMinusAssign, OtherRowsCols) {
  S21Matrix m1(11, 12);
  S21Matrix m2(10, 1);

  EXPECT_THROW(m1 -= m2, std::invalid_argument);
  EXPECT_THROW(m2 -= m1, std::invalid_argument);
}

TEST(MatrixOperatorMinusAssign, SumMatrix) {
  int rows = 9;
  int cols = 10;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);
  S21Matrix m3(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      double a = 1.23 + i * 16.123 + j * 4.123;
      double b = 2.1 + i * 19.123 + j * 14.123;
      m1(i, j) = a;
      m2(i, j) = b;
      m3(i, j) = a - b;
    }
  }

  m1 -= m2;
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m3(i, j));
    }
  }
}

// Tests for operator*= num

TEST(MatrixOperatorMulAssignNum, MulMatrixNum) {
  int rows = 9;
  int cols = 10;
  double ratio = -17.123;
  S21Matrix m1(rows, cols);
  S21Matrix m2(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      m1(i, j) = m2(i, j) = 1.23 + i * 16.123 + j * 4.123;
      m2(i, j) *= ratio;
    }
  }

  m1 *= ratio;
  EXPECT_EQ(m1.GetRows(), m2.GetRows());
  EXPECT_EQ(m1.GetCols(), m2.GetCols());
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      EXPECT_EQ(m1(i, j), m2(i, j));
    }
  }
}

// Tests for operator*= matrix

TEST(MatrixOperatorMulAssignMatrix, IncompatibleMatrices) {
  S21Matrix m1(19, 16);
  S21Matrix m2(18, 17);

  EXPECT_THROW(m1 *= m2, std::invalid_argument);

  S21Matrix a1(14, 15);
  S21Matrix a2(14, 15);
  EXPECT_THROW(m1 *= m2, std::invalid_argument);
}

TEST(MatrixOperatorMulAssignMatrix, SquareMatrices) {
  double a[3][3] = {{-1.0, 2.0, 5.0}, {3.0, 4.0, 6.0}, {-8.0, 2.0, 12.0}};
  double b[3][3] = {{-2.0, 2.0, 19.1}, {5.0, 7.0, 17.7}, {-1.0, 4.0, -13.56}};
  double c[3][3] = {
      {7.0, 32.0, -51.5}, {8.0, 58.0, 46.74}, {14.0, 46.0, -280.12}};

  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  S21Matrix m3(3, 3);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      m1(i, j) = a[i][j];
      m2(i, j) = b[i][j];
      m3(i, j) = c[i][j];
    }
  }

  m1 *= m2;
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < m3.GetRows(); ++i) {
    for (int j = 0; j < m3.GetCols(); ++j) {
      EXPECT_NEAR(m1(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

TEST(MatrixOperatorMulAssignMatrix, RectangleMatrices) {
  double a[3][4] = {
      {-1.0, 2.0, 5.0, 78.45}, {3.0, 4.0, 6.0, 19.01}, {-8.0, 2.0, 12.0, 0.43}};
  double b[4][5] = {{-2.0, 2.0, 19.1, 0.5, 0.001},
                    {5.0, 7.0, 17.7, -0.9, -18.78},
                    {-1.0, 4.0, -13.56, 189.1, 19.43},
                    {18.1, 0.3, -17.1, 1983.14, 0.93}};
  double c[3][5] = {{1426.945, 55.535, -1392.995, 156520.533, 132.5475},
                    {352.081, 63.703, -278.331, 38831.9914, 59.1423},
                    {21.783, 46.129, -287.473, 3116.1502, 195.9919}};

  S21Matrix m1(3, 4);
  S21Matrix m2(4, 5);
  S21Matrix m3(3, 5);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 4; ++j) {
      m1(i, j) = a[i][j];
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 5; ++j) {
      m2(i, j) = b[i][j];
    }
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 5; ++j) {
      m3(i, j) = c[i][j];
    }
  }

  m1 *= m2;
  EXPECT_EQ(m1.GetRows(), m3.GetRows());
  EXPECT_EQ(m1.GetCols(), m3.GetCols());
  for (int i = 0; i < m3.GetRows(); ++i) {
    for (int j = 0; j < m3.GetCols(); ++j) {
      EXPECT_NEAR(m1(i, j), m3(i, j), S21Matrix::kEps);
    }
  }
}

// Tests for operator()
TEST(MatrixOperatorParentheses, LessThanZero) {
  S21Matrix m1(100, 77);
  const S21Matrix m2(100, 77);

  EXPECT_THROW(m1(-1, 14), std::out_of_range);
  EXPECT_THROW(m1(1, -14), std::out_of_range);
  EXPECT_THROW(m1(-11, -14), std::out_of_range);

  EXPECT_THROW(m2(-1, 14), std::out_of_range);
  EXPECT_THROW(m2(1, -14), std::out_of_range);
  EXPECT_THROW(m2(-11, -14), std::out_of_range);
}

TEST(MatrixOperatorParentheses, GreaterThanZero) {
  S21Matrix m1(100, 77);
  const S21Matrix m2(100, 77);

  EXPECT_THROW(m1(100, 14), std::out_of_range);
  EXPECT_THROW(m1(1, 77), std::out_of_range);
  EXPECT_THROW(m1(110, 66), std::out_of_range);
  EXPECT_THROW(m1(11, 99), std::out_of_range);
  EXPECT_THROW(m1(111, 949), std::out_of_range);

  EXPECT_THROW(m2(100, 14), std::out_of_range);
  EXPECT_THROW(m2(1, 77), std::out_of_range);
  EXPECT_THROW(m2(110, 66), std::out_of_range);
  EXPECT_THROW(m2(11, 99), std::out_of_range);
  EXPECT_THROW(m2(111, 949), std::out_of_range);
}

TEST(MatrixOperatorParentheses, NormalIndex) {
  S21Matrix m1(100, 77);
  const S21Matrix m2(100, 77);

  for (int i = 0; i < m1.GetRows(); ++i) {
    for (int j = 0; j < m1.GetCols(); ++j) {
      m1(i, j) = static_cast<double>(i) + static_cast<double>(j);
    }
  }

  EXPECT_EQ(m1(14, 63), 14.0 + 63.0);
  EXPECT_EQ(m2(17, 54), 0.0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return (RUN_ALL_TESTS());
}

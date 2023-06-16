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
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixSum, OtherCols) {
	S21Matrix m1(10, 11);
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1.SumMatrix(m2), std::invalid_argument);
}

TEST(MatrixSum, OtherRowsCols) {
	S21Matrix m1(11, 12);
	S21Matrix m2 (10, 1);

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
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixSub, OtherCols) {
	S21Matrix m1(10, 11);
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1.SubMatrix(m2), std::invalid_argument);
}

TEST(MatrixSub, OtherRowsCols) {
	S21Matrix m1(11, 12);
	S21Matrix m2 (10, 1);

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
	S21Matrix m2 (18, 17);

	EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);

	S21Matrix a1(14, 15);
	S21Matrix a2(14, 15);
	EXPECT_THROW(m1.MulMatrix(m1), std::invalid_argument);
}

TEST(MatrixMulMatrix, SquareMatrices) {
	double a[3][3] = {
		{-1.0, 2.0, 5.0},
        {3.0, 4.0, 6.0},
        {-8.0, 2.0, 12.0}
	};
	double b[3][3] = {
		{-2.0, 2.0, 19.1},
		{5.0, 7.0, 17.7},
		{-1.0, 4.0, -13.56}
	};
	double c[3][3] = {
		{7.0, 32.0, -51.5},
		{8.0, 58.0, 46.74},
		{14.0, 46.0, -280.12}
	};

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
			EXPECT_NEAR(m1(i,j), m3(i, j), S21Matrix::kEps);
		}
	}
}

TEST(MatrixMulMatrix, RectangleMatrices) {
	double a[3][4] = {
		{-1.0, 2.0, 5.0, 78.45},
		{3.0, 4.0, 6.0, 19.01},
		{-8.0, 2.0, 12.0, 0.43}
	};
	double b[4][5] = {
		{-2.0, 2.0, 19.1, 0.5, 0.001},
		{5.0, 7.0, 17.7, -0.9, -18.78},
		{-1.0, 4.0, -13.56, 189.1, 19.43},
		{18.1, 0.3, -17.1, 1983.14, 0.93}
	};
	double c[3][5] = {
		{1426.945, 55.535, -1392.995, 156520.533, 132.5475},
		{352.081, 63.703, -278.331, 38831.9914, 59.1423},
		{21.783, 46.129, -287.473, 3116.1502, 195.9919}
	};

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
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			EXPECT_NEAR(m1(i,j), m3(i, j), S21Matrix::kEps);
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

// Tests for Determinant

// Tests for InverseMatrix

// Tests for operator+

TEST(MatrixOperatorPlus, OtherRows) {
	S21Matrix m1(11, 12);
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1 + m2, std::invalid_argument);
	EXPECT_THROW(m2 + m1, std::invalid_argument);
}

TEST(MatrixOperatorPlus, OtherCols) {
	S21Matrix m1(10, 11);
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1 + m2, std::invalid_argument);
	EXPECT_THROW(m2 + m1, std::invalid_argument);
}

TEST(MatrixOperatorPlus, OtherRowsCols) {
	S21Matrix m1(11, 12);
	S21Matrix m2 (10, 1);

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
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1 - m2, std::invalid_argument);
	EXPECT_THROW(m2 - m1, std::invalid_argument);
}

TEST(MatrixOperatorMinus, OtherCols) {
	S21Matrix m1(10, 11);
	S21Matrix m2 (10, 12);

	EXPECT_THROW(m1 - m2, std::invalid_argument);
	EXPECT_THROW(m2 - m1, std::invalid_argument);
}

TEST(MatrixOperatorMinus, OtherRowsCols) {
	S21Matrix m1(11, 12);
	S21Matrix m2 (10, 1);

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
// Tests for operator==
// Tests for operator=
// Tests for operator+=
// Tests for operator-=
// Tests for operator*= num
// Tests for operator*= matrix
// Tests for operator() const
// Tests for operator()



int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return (RUN_ALL_TESTS());
}


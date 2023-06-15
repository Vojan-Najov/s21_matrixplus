#include <gtest/gtest.h>
#include <utility>

#include "s21_matrix_oop.h"

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


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return (RUN_ALL_TESTS());
}


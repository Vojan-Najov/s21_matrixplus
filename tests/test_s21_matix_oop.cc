#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(MatrixConstructor, DefaultConstructor) {
	S21Matrix m;

	EXPECT_EQ(m.getRows(), S21Matrix::kDefaultRows);
	EXPECT_EQ(m.getCols(), S21Matrix::kDefaultCols);
	for (int i = 0; i < S21Matrix::kDefaultRows; ++i) {
		for (int j = 0; j < S21Matrix::kDefaultCols; ++j) {
			EXPECT_EQ(m(i, j), 0.0);
		}
	}
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);

	return (RUN_ALL_TESTS());
}


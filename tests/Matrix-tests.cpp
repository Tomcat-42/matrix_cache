#include <gtest/gtest.h>
#include <matrix_cache/matrix.h>

class MatrixSmallTest : public ::testing::Test {
 protected:
  void SetUp() override {
    matrix_square_1_ = Matrix(
        new double *[2] {
          new double[2]{1., 2.}, new double[2] { 3., 4. }
        },
        2, 2);

    matrix_square_2_ = Matrix(
        new double *[2] {
          new double[2]{5., 6.}, new double[2] { 7., 8. }
        },
        2, 2);

    matrix_non_square_1_ = Matrix(
        new double *[2] {
          new double[3]{1., 2., 3.}, new double[3] { 4., 5., 6. }
        },
        2, 3);

    matrix_non_square_2_ = Matrix(
        new double *[3] {
          new double[2]{1., 2.}, new double[2]{4., 5.}, new double[2] { 7., 8. }
        },
        2, 3);

    matrix_multiply_ms1_ms2_ = Matrix(
        new double *[2] {
          new double[2]{19., 22.}, new double[2] { 43., 50. }
        },
        2, 2);

    matrix_multiply_ns1_ns2_ = Matrix(
        new double *[2] {
          new double[2]{30., 36.}, new double[2] { 66., 81. }
        },
        2, 3);

    // void TearDown() override {}
  }
  Matrix matrix_square_1_;
  Matrix matrix_square_2_;
  Matrix matrix_multiply_ms1_ms2_;
  Matrix matrix_non_square_1_;
  Matrix matrix_non_square_2_;
  Matrix matrix_multiply_ns1_ns2_;
};

TEST_F(MatrixSmallTest, testSquareMultiplicationEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_square_1_ * matrix_square_2_;

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_multiply_ms1_ms2_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixSmallTest, testSquareMultiplicationNotEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_square_1_ * matrix_square_2_;

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_multiply_ms1_ms2_, true)
      << "Matrix multiplication not equal failed";
}
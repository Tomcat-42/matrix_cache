#include <gtest/gtest.h>
#include <matrix_cache/matrix.h>

#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::string;

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
        3, 2);

    matrix_multiply_ms1_ms2_ = Matrix(
        new double *[2] {
          new double[2]{19., 22.}, new double[2] { 43., 50. }
        },
        2, 2);

    matrix_multiply_ns1_ns2_ = Matrix(
        new double *[2] {
          new double[2]{30., 36.}, new double[2] { 66., 81. }
        },
        2, 2);

    // void TearDown() override {}
  }
  Matrix matrix_square_1_;
  Matrix matrix_square_2_;
  Matrix matrix_multiply_ms1_ms2_;
  Matrix matrix_non_square_1_;
  Matrix matrix_non_square_2_;
  Matrix matrix_multiply_ns1_ns2_;
};

class MatrixBigTest : public ::testing::Test {
 protected:
  void SetUp() override {
    int l1, c1, l2, c2, lp, cp;

    matrix_1_file_path_ = "../../files/matrix_1";
    matrix_2_file_path_ = "../../files/matrix_2";
    matrix_1_2_prod_file_path_ = "../../files/matrix_1_2_prod";
    dimensions_file_path_ = "../../files/dimensions";

    ifstream matrix_1_file(matrix_1_file_path_);
    ifstream matrix_2_file(matrix_2_file_path_);
    ifstream matrix_1_2_prod_file(matrix_1_2_prod_file_path_);
    ifstream dimensions_file(dimensions_file_path_);

    dimensions_file >> l1 >> c1 >> l2 >> c2 >> lp >> cp;

    matrix_1_ = Matrix(l1, c1);
    matrix_2_ = Matrix(l2, c2);
    matrix_1_2_prod_ = Matrix(lp, cp);

    matrix_1_file >> matrix_1_;
    matrix_2_file >> matrix_2_;
    matrix_1_2_prod_file >> matrix_1_2_prod_;

    matrix_1_file.close();
    matrix_2_file.close();
    matrix_1_2_prod_file.close();
  }

  // void TearDown() override {}
  string matrix_1_file_path_;
  string matrix_2_file_path_;
  string matrix_1_2_prod_file_path_;
  string dimensions_file_path_;
  Matrix matrix_1_;
  Matrix matrix_2_;
  Matrix matrix_1_2_prod_;
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

TEST_F(MatrixSmallTest, testNonSquareMultiplicationEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_non_square_1_ * matrix_non_square_2_;

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_multiply_ns1_ns2_, true)
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

TEST_F(MatrixSmallTest, testNonSquareMultiplicationNotEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_non_square_1_ * matrix_non_square_2_;

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_multiply_ns1_ns2_, true)
      << "Matrix multiplication not equal failed";
}

TEST_F(MatrixSmallTest, testSquareMultiplicationTransposedEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result =
      matrix_square_1_ ^ matrix_square_2_.transpose();

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_multiply_ms1_ms2_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixSmallTest, testNonSquareMultiplicationTransposedEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result =
      matrix_non_square_1_ ^ matrix_non_square_2_.transpose();

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_multiply_ns1_ns2_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixSmallTest, testSquareMultiplicationTransposedNotEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result =
      matrix_square_1_ ^ matrix_square_2_.transpose();

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_multiply_ms1_ms2_, true)
      << "Matrix multiplication not equal failed";
}

TEST_F(MatrixSmallTest, testNonSquareMultiplicationTransposedNotEqual) {
  // arrange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result =
      matrix_non_square_1_ ^ matrix_non_square_2_.transpose();

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_multiply_ns1_ns2_, true)
      << "Matrix multiplication not equal failed";
}

TEST_F(MatrixBigTest, testMultiplicationEqual) {
  // arange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_1_ * matrix_2_;

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_1_2_prod_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixBigTest, testMultiplicationNotEqual) {
  // arange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_1_ * matrix_2_;

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_1_2_prod_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixBigTest, testMultiplicationTransposedEqual) {
  // arange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_1_ ^ matrix_2_.transpose();

  // expect
  EXPECT_EQ(matrix_multiplication_result == matrix_1_2_prod_, true)
      << "Matrix multiplication equal failed";
}

TEST_F(MatrixBigTest, testMultiplicationTransposedposedNotEqual) {
  // arange
  Matrix matrix_multiplication_result;
  // act
  matrix_multiplication_result = matrix_1_ ^ matrix_2_.transpose();

  // expect
  EXPECT_NE(matrix_multiplication_result != matrix_1_2_prod_, true)
      << "Matrix multiplication equal failed";
}
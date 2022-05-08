#pragma once
#include <iostream>

#define MAX_RANDOM_SIZE 1000000
#define MIN_RANDOM_SIZE 0

class Matrix {
 private:
  double **matrix;
  int _rows, _cols;
  void alloc_mem();

 public:
  // constructors
  Matrix(int, int);
  Matrix(double **, int, int);
  Matrix(const Matrix &);
  Matrix();
  ~Matrix();

  // simple operations and operators
  inline double &operator()(int x, int y) { return matrix[x][y]; }
  Matrix &operator=(const Matrix &);
  Matrix &operator/=(double);
  Matrix &operator+(const Matrix &);
  Matrix &operator+=(const Matrix &);
  Matrix &operator-=(const Matrix &);
  Matrix &operator-(const Matrix &);
  Matrix &operator*=(const Matrix &);
  Matrix &operator*(const Matrix &);
  Matrix &operator^=(const Matrix &);
  Matrix &operator^(const Matrix &);
  Matrix &operator*=(double);
  bool operator==(const Matrix &);
  bool operator!=(const Matrix &);

  // transposition
  void swap_rows(int, int);
  Matrix transpose();

  // randomization
  Matrix &randomize(double, double);

  // matrix io
  friend std::ostream &operator<<(std::ostream &, const Matrix &);
  friend std::istream &operator>>(std::istream &, Matrix &);
};

// Matrix operator+(const Matrix &, const Matrix &);
// Matrix operator-(const Matrix &, const Matrix &);
// Matrix operator*(const Matrix &, const Matrix &);
// Matrix operator*(const Matrix &, double);
// Matrix operator*(double, const Matrix &);
// Matrix operator/(const Matrix &, double);
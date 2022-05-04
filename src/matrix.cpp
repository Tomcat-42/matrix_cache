#include <matrix_cache/matrix.h>
#include <matrix_cache/utils.h>

#include <stdexcept>

using std::domain_error;
using std::endl;
using std::istream;
using std::ostream;
using utils::get_random_value;

// private methods
void Matrix::alloc_mem() {
  matrix = new double *[_rows];
  for (int i = 0; i < _rows; i++) {
    matrix[i] = new double[_cols];
  }
}

/* Constructors and desructors overloadings */
Matrix::Matrix(int rows, int cols, bool random = false)
    : _rows(rows), _cols(cols) {
  alloc_mem();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] =
          random ? get_random_value(MIN_RANDOM_SIZE, MAX_RANDOM_SIZE) : 0;
    }
  }
}

Matrix::Matrix(double **matrix, int rows, int cols) : _rows(rows), _cols(cols) {
  alloc_mem();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      this->matrix[i][j] = matrix[i][j];
    }
  }
}

Matrix::Matrix(const Matrix &other) : _rows(other._rows), _cols(other._cols) {
  alloc_mem();
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] = other.matrix[i][j];
    }
  }
}

Matrix::Matrix() : _rows(1), _cols(1) { alloc_mem(); }

Matrix::~Matrix() {
  for (int i = 0; i < _rows; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

/* Operations and operators overloadings */
Matrix &Matrix::operator=(const Matrix &other) {
  if (this == &other) {
    return *this;
  }
  _rows = other._rows;
  _cols = other._cols;
  alloc_mem();
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] = other.matrix[i][j];
    }
  }
  return *this;
}

Matrix &Matrix::operator/=(double divisor) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] /= divisor;
    }
  }
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw domain_error("Matrices must have the same dimensions");
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] += other.matrix[i][j];
    }
  }

  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  if (_rows != other._rows || _cols != other._cols) {
    throw domain_error("Matrices must have the same dimensions");
  }

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] -= other.matrix[i][j];
    }
  }

  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  if (_cols != other._rows) {
    throw domain_error("Matrices must have the same dimensions");
  }

  Matrix temp_matrix(_rows, other._cols);

  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < other._cols; j++) {
      for (int k = 0; k < _cols; k++) {
        temp_matrix.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
      }
    }
  }

  return (*this = temp_matrix);
}

Matrix &Matrix::operator*=(double factor) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      matrix[i][j] *= factor;
    }
  }
  return *this;
}

void Matrix::swap_rows(int row1, int row2) {
  double *temp = matrix[row1];
  matrix[row1] = matrix[row2];
  matrix[row2] = temp;
}

Matrix Matrix::transpose() {
  Matrix temp_matrix(_cols, _rows);
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      temp_matrix.matrix[j][i] = matrix[i][j];
    }
  }
  return temp_matrix;
}

// matrix io
ostream &operator<<(ostream &os, const Matrix &matrix) {
  for (int i = 0; i < matrix._rows; i++) {
    for (int j = 0; j < matrix._cols; j++) {
      os << matrix.matrix[i][j] << " ";
    }
    os << endl;
  }
  return os;
}

istream &operator>>(istream &is, Matrix &matrix) {
  for (int i = 0; i < matrix._rows; i++) {
    for (int j = 0; j < matrix._cols; j++) {
      is >> matrix.matrix[i][j];
    }
  }
  return is;
}

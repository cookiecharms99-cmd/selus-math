#include "matrix.hpp"
#include "vector.hpp"
#include <initializer_list>
#include <stdexcept>

// Construction
// Operators-----------------------------------------------------------------
//
Matrix::Matrix() : elements{}, n_rows{}, n_cols{} {}
Matrix::Matrix(std::size_t rows, std::size_t cols)
    : elements(rows * cols, 0.0), n_cols{cols}, n_rows{rows} {}

Matrix::Matrix(std::vector<std::vector<double>> mat) {
  if (mat.empty()) {
    n_rows = 0;
    n_cols = 0;
    return;
  }

  n_rows = mat.size();
  n_cols = mat[0].size();
  elements.resize(n_rows * n_cols);
  for (std::size_t i{0}; i < mat.size(); ++i) {
    if (mat[i].size() != n_cols) {
      throw std::invalid_argument("all rows must be equally sized pls :)");
    }

    for (std::size_t j{0}; j < mat[0].size(); ++j) {
      elements[flat_idx(i, j)] = mat[i][j];
    }
  }
}

Matrix::Matrix(std::size_t rows, std::size_t cols, std::vector<double> flat)
    : n_rows{rows}, n_cols{cols}, elements(std::move(flat)) {
  if (elements.size() != rows * cols) {
    throw std::invalid_argument("must match pls!");
  }
}

Matrix::Matrix(std::initializer_list<std::vector<double>> list)
    : Matrix(std::vector<std::vector<double>>(list)) {}

// ---------------------------------------------------------------------------------------------
// Access operators
// operators---------------------------------------------------------

double &Matrix::operator()(std::size_t row, std::size_t col) {
  return elements[flat_idx(row, col)];
}

const double &Matrix::operator()(std::size_t row, std::size_t col) const {
  return elements[flat_idx(row, col)];
}

std::span<double> Matrix::operator[](std::size_t row) {
  return std::span<double>(elements.data() + row * n_cols, n_cols);
}

std::span<const double> Matrix::operator[](std::size_t row) const {
  return std::span<const double>(elements.data() + row * n_cols, n_cols);
}
//
//

bool Matrix::operator==(const Matrix &other) const {
  return ((this->n_rows == other.n_rows) && (this->n_cols == other.n_cols) &&
          (this->elements == other.elements));
}

// Math operations :)-----------------------------------------------------------
// w other matrix

Matrix &Matrix::operator+=(const Matrix &other) {
  if ((this->n_rows != other.n_rows) || (this->n_cols != other.n_cols)) {
    throw std::invalid_argument("eep dimension mismatch!");
  }
  for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
    this->elements[idx] += other.elements[idx];
  }
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  if ((this->n_rows != other.n_rows) || (this->n_cols != other.n_cols)) {
    throw std::invalid_argument("eep dimension mismatch!");
  }
  for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
    this->elements[idx] -= other.elements[idx];
  }
  return *this;
}

// now... matrix product... eep!!

Matrix &Matrix::operator*=(const Matrix &other) {
  if ((this->n_cols) != other.n_rows) {
    throw std::invalid_argument("eep dimension mistmach for matrix product!");
  }
  Matrix result(this->n_rows, other.n_cols);
  // Formula recall! (AB)_ij = Sum_{k} A_ik B_kj
  for (std::size_t i{0}; i < this->n_rows; ++i) {
    for (std::size_t k{0}; k < this->n_cols; ++k) {
      for (std::size_t j{0}; j < other.n_cols; ++j) {
        result[i][j] += (*this)[i][k] * other[k][j];
      }
    }
  }
  return *this = std::move(result);
}

// now element wise product
Matrix &Matrix::elem_mul(const Matrix &other) {
  if ((this->n_rows != other.n_rows) || (this->n_cols != other.n_cols)) {
    throw std::invalid_argument("eep dimension mismatch!");
  }
  for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
    this->elements[idx] *= other.elements[idx];
  }
  return *this;
}

// w scalar
Matrix &Matrix::operator*=(double scalar) {
  for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
    elements[idx] *= scalar;
  }
  return *this;
}
Matrix &Matrix::operator/=(double scalar) {
  for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
    elements[idx] /= scalar;
  }
  return *this;
}

// Corresponding math!! :D-------
// matrix matrix
Matrix operator+(Matrix m1, const Matrix &m2) {
  m1 += m2;
  return m1;
}

Matrix operator-(Matrix m1, const Matrix &m2) {
  m1 -= m2;
  return m1;
}
Matrix operator*(Matrix m1, const Matrix &m2) {
  m1 *= m2;
  return m1;
}

Matrix elem_mul(Matrix m1, const Matrix &m2) {
  m1.elem_mul(m2);
  return m1;
}

// scalar
Matrix operator*(Matrix m, double scalar) {
  m *= scalar;
  return m;
}
Matrix operator/(Matrix m, double scalar) {
  m /= scalar;
  return m;
}

//------------------
// math!! :D
//
Matrix Matrix::transpose() const {
  Matrix result(n_cols, n_rows);
  for (std::size_t r{0}; r < n_rows; ++r) {
    for (std::size_t c{0}; c < n_cols; ++c) {
      // local reads better than local writes
      // todo: make it even better :3
      result[c][r] = (*this)[r][c];
    }
  }
  return result;
}

// --------------------------------------------------------------------

// Auxillary
//
// important helper!
//
std::size_t Matrix::flat_idx(std::size_t row, std::size_t col) const {
  return n_cols * row + col;
}

std::size_t Matrix::rows() const { return n_rows; }
std::size_t Matrix::cols() const { return n_cols; }
std::vector<double> Matrix::data() const { return elements; }
void Matrix::print_matrix() {

  for (std::size_t i{}; i < n_rows; ++i) {
    std::cout << "|";
    for (std::size_t j{}; j < n_cols; j++) {
      std::cout << (*this)[i][j];
      if (j != n_cols - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "|\n";
  };
}

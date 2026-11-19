#pragma once

#include "vector.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
namespace selus {

template <typename T = double> class Matrix {
  std::size_t n_rows{0};
  std::size_t n_cols{0};
  std::vector<T> elements{};

public:
  // Constructors -------------------------------------------------------------
  Matrix() = default;

  Matrix(std::size_t rows, std::size_t cols)
      : n_rows{rows}, n_cols{cols}, elements(rows * cols, T{}) {}

  Matrix(std::vector<std::vector<T>> mat) {
    if (mat.empty()) {
      n_rows = 0;
      n_cols = 0;
      return;
    }

    n_rows = mat.size();
    n_cols = mat[0].size();
    elements.resize(n_rows * n_cols);

    for (std::size_t i{0}; i < n_rows; ++i) {
      if (mat[i].size() != n_cols) {
        throw std::invalid_argument("all rows must be equally sized pls :)");
      }
      for (std::size_t j{0}; j < n_cols; ++j) {
        elements[flat_idx(i, j)] = std::move(mat[i][j]);
      }
    }
  }

  Matrix(std::size_t rows, std::size_t cols, std::vector<T> flat)
      : n_rows{rows}, n_cols{cols}, elements(std::move(flat)) {
    if (elements.size() != rows * cols) {
      throw std::invalid_argument("must match pls!");
    }
  }

  Matrix(std::initializer_list<std::vector<T>> list)
      : Matrix(std::vector<std::vector<T>>(list)) {}

  // Access operations --------------------------------------------------------
  T &operator()(std::size_t row, std::size_t col) {
    return elements[flat_idx(row, col)];
  }

  const T &operator()(std::size_t row, std::size_t col) const {
    return elements[flat_idx(row, col)];
  }

  std::span<T> operator[](std::size_t row) {
    return std::span<T>(elements.data() + row * n_cols, n_cols);
  }

  std::span<const T> operator[](std::size_t row) const {
    return std::span<const T>(elements.data() + row * n_cols, n_cols);
  }

  // Equivalence --------------------------------------------------------------
  bool operator==(const Matrix<T> &other) const {
    return (n_rows == other.n_rows) && (n_cols == other.n_cols) &&
           (elements == other.elements);
  }

  // Compound matrix operations -----------------------------------------------
  Matrix<T> &operator+=(const Matrix<T> &other) {
    if ((n_rows != other.n_rows) || (n_cols != other.n_cols)) {
      throw std::invalid_argument("eep dimension mismatch!");
    }
    for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
      elements[idx] += other.elements[idx];
    }
    return *this;
  }

  Matrix<T> &operator-=(const Matrix<T> &other) {
    if ((n_rows != other.n_rows) || (n_cols != other.n_cols)) {
      throw std::invalid_argument("eep dimension mismatch!");
    }
    for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
      elements[idx] -= other.elements[idx];
    }
    return *this;
  }

  Matrix<T> &operator*=(const Matrix<T> &other) {
    if (n_cols != other.n_rows) {
      throw std::invalid_argument("eep dimension mismatch for matrix product!");
    }
    Matrix<T> result(n_rows, other.n_cols);
    //
    // i-k-j loop order streams row k of `other` and row i of `result`
    // sequentially
    // Recall formula (AB)_ij = Sum{k} Aik * Bkj
    for (std::size_t i{0}; i < n_rows; ++i) {
      for (std::size_t k{0}; k < n_cols; ++k) {
        for (std::size_t j{0}; j < other.n_cols; ++j) {
          result[i][j] += (*this)[i][k] * other[k][j];
        }
      }
    }
    return *this = std::move(result);
  }

  Matrix<T> &elem_mul(const Matrix<T> &other) {
    if ((n_rows != other.n_rows) || (n_cols != other.n_cols)) {
      throw std::invalid_argument("eep dimension mismatch!");
    }
    for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
      elements[idx] *= other.elements[idx];
    }
    return *this;
  }

  // Compound scalar operations -----------------------------------------------
  Matrix<T> &operator*=(const T &scalar) {
    for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
      elements[idx] *= scalar;
    }
    return *this;
  }

  Matrix<T> &operator/=(const T &scalar) {
    for (std::size_t idx{0}; idx < n_rows * n_cols; ++idx) {
      elements[idx] /= scalar;
    }
    return *this;
  }

  // Transformations & metadata -----------------------------------------------
  Matrix<T> transpose() const {
    // todo: figure out how to get local reads and local writes
    // the current code has distant writes but close reads because it's better
    // than the reverse! :)
    Matrix<T> result(n_cols, n_rows);
    for (std::size_t r{0}; r < n_rows; ++r) {
      for (std::size_t c{0}; c < n_cols; ++c) {
        result[c][r] = (*this)[r][c];
      }
    }
    return result;
  }

  std::size_t rows() const { return n_rows; }
  std::size_t cols() const { return n_cols; }
  const std::vector<T> &data() const { return elements; }

  std::size_t flat_idx(std::size_t row, std::size_t col) const {
    return n_cols * row + col;
  }

  void print_matrix() const {
    for (std::size_t i{0}; i < n_rows; ++i) {
      std::cout << "|";
      for (std::size_t j{0}; j < n_cols; ++j) {
        std::cout << (*this)[i][j];
        if (j != n_cols - 1) {
          std::cout << ", ";
        }
      }
      std::cout << "|\n";
    }
  }

  // TODO: determinant(), trace(), frobenius_norm(), eigenvalues/vectors
}; // namespace selus

// Free binary operators ------------------------------------------------------
template <typename T> Matrix<T> operator+(Matrix<T> m1, const Matrix<T> &m2) {
  m1 += m2;
  return m1;
}

template <typename T> Matrix<T> operator-(Matrix<T> m1, const Matrix<T> &m2) {
  m1 -= m2;
  return m1;
}

template <typename T> Matrix<T> operator*(Matrix<T> m1, const Matrix<T> &m2) {
  m1 *= m2;
  return m1;
}

template <typename T> Matrix<T> elem_mul(Matrix<T> m1, const Matrix<T> &m2) {
  m1.elem_mul(m2);
  return m1;
}

template <typename T>
Matrix<T> operator*(Matrix<T> m, const std::type_identity_t<T> &scalar) {
  m *= scalar;
  return m;
}

template <typename T>
Matrix<T> operator*(const std::type_identity_t<T> &scalar, Matrix<T> m) {
  m *= scalar;
  return m;
}

template <typename T>
Matrix<T> operator/(Matrix<T> m, const std::type_identity_t<T> &scalar) {
  m /= scalar;
  return m;
}

template <typename T>
Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v) {
  if (m.cols() != v.size()) {
    throw std::invalid_argument("eep dimensions much match better pls!\n");
  }
  Vector<T> result(v.size());
  for (std::size_t i{0}; i < m.rows(); ++i) {
    for (std::size_t j{0}; j < m.cols(); ++j) {
      result[i] += m[i][j] * v[j];
    }
  }
  return result;
}
} // namespace selus

#include "vector.hpp"
#include <span>

class Matrix {
  std::size_t n_rows{0};
  std::size_t n_cols{0}; // in principle only need to cache one of these?
  // flat vector underneath
  std::vector<double> elements{};

public:
  // Constructors -------------
  Matrix();                                     // empty matrix
  Matrix(std::size_t rows, std::size_t cols);   // empty rows,cols matrix
  Matrix(std::vector<std::vector<double>> mat); // Matrix = Matrix({{1,2}{3,4}})
  Matrix(std::size_t rows, std::size_t cols,
         std::vector<double> flat); // Matrix = Matrix(1,2, {1,2})
  Matrix(
      std::initializer_list<std::vector<double>> list); // Matrix {{1,2},{3,4}}

  // Access operations-----------------------------------------------------
  // Q: should single index access return a Vector or std::vector?

  // q: how to get [i][j]?
  double &operator()(std::size_t row, std::size_t col);
  const double &operator()(std::size_t row, std::size_t col) const;

  std::span<double> operator[](std::size_t row);
  std::span<const double> operator[](std::size_t row) const;
  // Read a row or column

  //
  //
  // Equivalence operator
  bool operator==(const Matrix &other) const;
  // Math Operations! -------------------------------------
  // with other matrices
  Matrix &operator+=(const Matrix &other);
  Matrix &operator*=(const Matrix &other); // matrix product or element wise?
  Matrix &operator-=(const Matrix &other);
  Matrix &elem_mul(const Matrix &other);

  // with scalars
  Matrix &operator*=(double scalar);
  Matrix &operator/=(double scalar);

  // --------
  // Auxillary functions ----------
  //
  void print_matrix();
  Vector &ReadRow(std::size_t row) const;
  Vector &ReadCol(std::size_t col) const;

  //
  // math
  Matrix transpose() const;
  double determinant() const;
  double trace() const;
  double frobenius_norm() const;
  Vector get_eigenvalues() const;
  Matrix get_eigenmatrix() const;
  std::size_t rows() const;
  std::size_t cols() const;
  std::vector<double> data() const;
  std::size_t flat_idx(std::size_t row, std::size_t col) const;

  //--------------------
};

// External operations
// math
//
Matrix operator+(Matrix m1, const Matrix &m2);
Matrix operator-(Matrix m1, const Matrix &m2);
Matrix operator*(Matrix m1, const Matrix &m2);
Matrix elem_mul(Matrix m1, const Matrix &m2);
Vector operator*(Matrix m, const Vector &v);

// with scalars
Matrix operator*(Matrix m, double scalar);
Matrix operator/(Matrix m, double scalar);

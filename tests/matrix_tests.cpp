#include <cassert>
#include <complex>
#include <iostream>
#include <selus/matrix.hpp>
#include <selus/vector.hpp>
#include <stdexcept>
int main() {
  using selus::Matrix;
  // test construction
  Matrix A;
  assert((A.rows() == 0) && (A.cols() == 0) && (A.data().empty()));

  Matrix B{{1, 2, 3}, {4, 5, 6}};
  B.print_matrix();
  assert((B[0][0] == 1) && (B[1][0] == 4) && (B.rows() == 2) &&
         (B.cols() == 3));

  Matrix C = Matrix(2, 2, {4, 3, 2, 1});
  assert((C.rows() == 2) && (C.cols() == 2) && (C[0][1] == 3));

  Matrix D = {{1, 2, 3, 4}};
  D *= 2.0;

  assert((D[0][0] == 2));
  D = D.transpose();
  D.print_matrix();

  assert((D.rows() == 4) && (D.cols() == 1));
  Matrix E = D * 2.0;
  assert(E[0][0] == 4);

  Matrix pauli_x{{0, 1}, {1, 0}};
  Matrix I2 = Matrix({{1, 0}, {0, 1}});
  Matrix pauli_x2 = pauli_x * pauli_x;
  assert(I2 == pauli_x2);

  bool mul_error_works;
  try {
    B *= I2;
    mul_error_works = false;
  }

  catch (std::invalid_argument) {
    mul_error_works = true;
  }
  assert(mul_error_works);
  Matrix B_copy = I2 * B;
  assert(B_copy == B);

  using namespace std::complex_literals;
  Matrix<std::complex<double>> pauli_y{{0, -1.0i}, {1.0i, 0}};
  Matrix<std::complex<double>> I_2_c{{1, 0}, {0, 1}};
  assert(pauli_y * pauli_y == I_2_c);
}

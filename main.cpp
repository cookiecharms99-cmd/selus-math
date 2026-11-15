#include "matrix.hpp"
#include "vector.hpp"
#include <iostream>

int main() {
  Matrix A{{1, 2}, {3, 4}};
  Matrix B(10, 10);
  Matrix C;
  Matrix D = Matrix(2, 3, {1, 2, 3, 4, 5, 6});
  D *= 2;
  D.print_matrix();
}

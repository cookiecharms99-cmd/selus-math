#include "vector.hpp"
#include <iostream>

int main() {
  Vector v1{1, 2, 3};
  Vector v2({4, 5, 6});
  Vector v3{0, 0, 1};
  (v1 += v2) += v3;
  v1.print_vector();

  Vector v4 = v1 * 2.0;
  v4.print_vector();

  Vector v5 = 3.5 * v1;
  v5.print_vector();

  Vector v6 = v5 / 2.0;
  v6.print_vector();
}

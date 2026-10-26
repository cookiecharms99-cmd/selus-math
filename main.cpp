#include "vector.hpp"
#include <iostream>

int main() {
  Vector v1{{
      1,
      2,
      3,
  }};
  Vector v2{{4, 5, 6}};
  v1.print_vector();
  std::cout << "v1 . v1 = " << dot(v1, v1) << "\n";
}

#include "vector.hpp"
#include <iostream>

int main() {
  Vector v1(3);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  std::cout << "||v1||^2 = " << v1.squared_norm() << "!\n";
  return 0;
}

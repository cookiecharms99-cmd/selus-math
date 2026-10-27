#include "../vector.hpp" // must be a better way to do this lol
#include <cassert>
#include <iostream>
#include <stdexcept>
int main() {

  // Test vector size!
  std::cout << "Size Test!\n";
  Vector v1(3);
  assert(v1.size() == 3);
  std::cout << "PASSED! <3 ✅\n";

  // Test vector operations (use integers :o)
  v1 = {1, 2, 3};
  Vector v2{4, 5, 6};
  Vector v3{3, 6, 9};

  double scalar{2};
  double scalar2{3};
  Vector expected_add{5, 7, 9};
  Vector expected_scaled_v1{2, 4, 6};
  Vector expected_divscale_v3{1, 2, 3};

  std::cout << "Test vector addition!\n";
  assert(v1 + v2 == expected_add);
  std::cout << "PASSED! <3 ✅\n";

  std::cout << "Test scalar multiplication!\n";
  assert(v1 * scalar == expected_scaled_v1);
  std::cout << "PASSED! <3 ✅\n";

  std::cout << "Test scalar division!\n";
  assert(v3 / scalar2 == expected_divscale_v3);
  std::cout << "PASSED! <3 ✅\n";

  // Test inplace modification (just do adding :3)
  (v1 += v1) += v1;
  Vector expected_inplaceadd_v1{4, 8, 12};
  std::cout << "Test in place modification (vector add)!\n";
  assert(v1 == expected_inplaceadd_v1);
  std::cout << "PASSED! <3 ✅\n";

  // Inplace scalar mul
  //
  Vector v6{1, 0, 2};
  v6 *= 8;
  Vector expected_scal_mul{8, 0, 16};
  std::cout << "Test in place modification (scalar mul)!\n";
  assert(v6 == expected_scal_mul);
  std::cout << "PASSED! <3 ✅\n";

  // Test dot products!
  double v2_dot_v3 = dot(v2, v3);
  double expected_dot_prod{96};

  std::cout << "Test dot product!\n";

  assert(v2_dot_v3 == expected_dot_prod);
  std::cout << "PASSED! <3 ✅\n";

  // Test norm!
  Vector v5{1, 2, 3, 0};
  double v5_sq_norm = v5.squared_norm();
  double v5_dot_v5 = dot(v5, v5);
  double expected_sq_norm = 14;

  std::cout << "Test norm and norm equivalence to dot product!\n";
  assert((v5_dot_v5 == v5_sq_norm) && (expected_sq_norm == v5_sq_norm));
  std::cout << "PASSED! <3 ✅\n";

  // Test that ops check dim properly! (just add for now :3)
  Vector v7{1}, v8{1, 2};
  std::cout << "Test that incompatible vectors won't add!\n";
  bool caught_error;
  try {
    Vector result = v7 + v8;

    caught_error = false;

  } catch (std::invalid_argument) {
    caught_error = true;
  }
  assert(caught_error);
  std::cout << "PASSED! <3 ✅\n";
  // Addition shouldn't mutate its inputs
  Vector a{1, 2, 3};
  Vector b{4, 5, 6};

  Vector c = a + b;

  assert((a == Vector{1, 2, 3}));
  assert((b == Vector{4, 5, 6}));
}

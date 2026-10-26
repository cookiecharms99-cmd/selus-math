#include <iostream>
#include <stdexcept>
#include <vector>
class Vector {

  std::vector<double> elements{};

public:
  std::size_t size() const;
  double squared_norm() const;
  double &operator[](std::size_t idx);

  void print_vector();

  // Operators
  const double &operator[](std::size_t idx) const;

  // Constructors
  Vector();
  Vector(std::size_t len);
  Vector(std::vector<double> input_elements);
};

// External vector operations.
/*
 *
 * So far v1 + v2
 *  v1 . v2
 */
Vector operator+(const Vector &v1, const Vector &v2);
double dot(const Vector &v1, const Vector &v2);

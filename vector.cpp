#include "vector.hpp"
// Operators--------------------------------------------------------------------
//
//
// inplace Vector operators ---------------

double &Vector::operator[](std::size_t idx) { return elements[idx]; }
const double &Vector::operator[](std::size_t idx) const {
  return elements[idx];
}
bool Vector::operator==(const Vector &other) {
  return elements == other.elements;
}
// With vectors -------------
Vector &Vector::operator+=(const Vector &other) {

  std::size_t my_size = std::size(elements), other_size = other.size();
  if (my_size != other_size) {
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah");
  }
  for (std::size_t i{}; i < my_size; ++i) {

    elements[i] += other[i];
  }
  return *this;
}

Vector &Vector::operator-=(const Vector &other) {

  std::size_t my_size = std::size(elements), other_size = other.size();
  if (my_size != other_size) {
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah");
  }
  for (std::size_t i{}; i < my_size; ++i) {

    elements[i] -= other[i];
  }
  return *this;
}
// -------------------------------

// With scalars -----------------
Vector &Vector::operator*=(double scalar) {
  for (std::size_t i{}; i < size(); ++i) {

    elements[i] *= scalar;
  }
  return *this;
}

Vector &Vector::operator/=(double scalar) {
  for (std::size_t i{}; i < size(); ++i) {

    elements[i] /= scalar;
  }
  return *this;
}

//----------------------------
//-----------------------------------------------------
// not in place operations-------------------------
// With scalars ------------
//
Vector operator*(Vector v, double scalar) {
  v *= scalar;
  return v;
}
Vector operator*(double scalar, Vector v) {
  v *= scalar;
  return v;
}

// personal arbitrary choice but perhaps 1 / v is potentially dubious, but idk
// lol :3
Vector operator/(Vector v, double scalar) {
  v /= scalar;
  return v;
}

// Vector operator/(const double scalar, Vector v) {
// v /= scalar;
// return v;
// }

//-----------------------

// With vectors-----------
Vector operator-(Vector v1, const Vector &v2) {
  v1 += v2;
  return v1;
}
Vector operator+(Vector v1, const Vector &v2) {
  v1 += v2;
  return v1;
}

//---------------------
//
// --------------------------------------------------------------------------------

std::size_t Vector::size() const { return std::size(elements); }
// Constructors
Vector::Vector() { elements = std::vector<double>{}; }
Vector::Vector(std::size_t len)

    : elements(len) {};

Vector::Vector(std::vector<double> input_elements) {
  elements = input_elements;
}

Vector::Vector(std::initializer_list<double> values) : elements(values) {}

void Vector::print_vector() {

  std::cout << "[";
  if (size() != 0) {
    for (std::size_t i{}; i < size() - 1; ++i) {
      std::cout << elements[i] << ", ";
    }
    std::cout << elements[size() - 1];
  }
  std::cout << "]\n";
}

// Function Operations
double dot(const Vector &v1, const Vector &v2) {
  std::size_t size1 = v1.size(), size2 = v2.size();
  // Perhaps there's a way to create custom exceptions idk
  if (size1 != size2) {
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah\n");
  }
  double prod{0};
  for (std::size_t i{}; i < size1; i++) {
    prod += v1[i] * v2[i];
  }
  return prod;
}

double Vector::squared_norm() const { return dot(*this, *this); }

#include "vector.hpp"

std::size_t Vector::size() const { return std::size(elements); }

Vector::Vector() { elements = std::vector<double>{}; }
Vector::Vector(std::size_t len)

    : elements(len) {};

Vector::Vector(std::vector<double> input_elements) {
  elements = input_elements;
}

void Vector::print_vector() {

  std::cout << "[";
  if (size() != 0) {
    for (std::size_t i{}; i < size() - 1; i++) {
      std::cout << elements[i] << ", ";
    }
    std::cout << elements[size() - 1];
  }
  std::cout << "]\n";
}

// Operators

double &Vector::operator[](std::size_t idx) { return elements[idx]; }
const double &Vector::operator[](std::size_t idx) const {
  return elements[idx];
}

Vector operator+(const Vector &v1, const Vector &v2) {
  std::size_t size1 = v1.size(), size2 = v2.size();
  if (size1 != size2) {
    std::cerr << "wrong sizes!";
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah\n");
  }
  Vector out(size1);
  for (std::size_t i{}; i < size1; i++) {
    out[i] = v1[i] + v2[i];
  }
  return out;
}

// Function Operations
double dot(const Vector &v1, const Vector &v2) {
  std::size_t size1 = v1.size(), size2 = v2.size();
  // Perhaps there's a way to create custom exceptions idk
  if (size1 != size2) {

    std::cerr << "wrong sizes!";
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah\n");
  }
  double prod{0};
  for (std::size_t i{}; i < size1; i++) {
    prod += v1[i] * v2[i];
  }
  return prod;
}

double Vector::squared_norm() const { return dot(*this, *this); }

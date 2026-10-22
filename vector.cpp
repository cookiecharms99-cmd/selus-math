#include "vector.hpp"

double &Vector::operator[](std::size_t idx) { return elements[idx]; }

std::size_t Vector::size() const { return std::size(elements); }

double Vector::squared_norm() const {
  double norm = 0;
  for (std::size_t i{}; i < this->size(); i++) {
    norm += elements[i] * elements[i];
  }
  return norm;
}

Vector::Vector() { elements = std::vector<double>{}; }
Vector::Vector(std::size_t len)

    : elements(len) {}

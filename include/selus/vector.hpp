#ifndef vector_hpp
#define vector_hpp
#include <initializer_list>
#include <iostream>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <vector>
namespace selus {

template <typename T = double> class Vector {

  std::vector<T> elements{};

public:
  // Assign vector Operators------------------------------------
  T &operator[](std::size_t idx);
  const T &operator[](std::size_t idx) const;
  // Equivalence operator
  bool operator==(const Vector &other) const;

  Vector<T> &operator+=(const Vector<T> &other);
  Vector<T> &operator-=(const Vector<T> &other);
  // Element wise!
  // Vector<T> &operator*=(const Vector<T> &other);
  // Vector<T> &operator/=(const Vector<T> &other);

  // assign Scalar operators-------------------
  Vector<T> &operator*=(T scalar);
  Vector<T> &operator/=(T scalar);
  //--------------------------------------------

  //-------------------------------------------------------------
  // Constructors----------------------------------------------
  Vector();
  Vector(std::size_t len);
  Vector(std::vector<T> input_elements);
  Vector(std::initializer_list<T> list);
  //--------------------------------------------------------------
  //
  //
  // Auxillary functions!-------
  std::span<T> span() { return elements; }
  void print_vector();
  std::size_t size() const;

  //-----------------------------
  //
  //
  // Math functions! -----------------
  T squared_norm() const; // hmmm... cookie is confused :O | complex should have
                          // a separate implementation for this to work
};

// External vector operations.
/*
 *
 * So far v1 + v2
 *  v1 . v2
 */
// Operators!--------------------------------------------------------

// Vector operations---------
template <typename T> Vector<T> operator+(Vector<T> v1, const Vector<T> &v2);

template <typename T> Vector<T> operator-(Vector<T> v1, const Vector<T> &v2);

// Define these ones element wise
//
// template <typename T> Vector<T> operator*(Vector<T> v1, const Vector<T> &v2);

// template <typename T> Vector<T> operator/(Vector<T> v1, const Vector<T> &v2);

//---------------------------

// Scalar operations! --------
//
template <typename T>
Vector<T> operator*(Vector<T> v, std::type_identity_t<T> scalar);
template <typename T>
Vector<T> operator*(std::type_identity_t<T> scalar, Vector<T> v);

template <typename T>
Vector<T> operator/(Vector<T> v, std::type_identity_t<T> scalar);
//-----------------------------

// ------------------------------------------------------------------
template <typename T> T dot(const Vector<T> &v1, const Vector<T> &v2);

// ------------ Implementations ------------------------
//
//
//
template <typename T> T &Vector<T>::operator[](std::size_t idx) {
  return elements[idx];
}
template <typename T> const T &Vector<T>::operator[](std::size_t idx) const {
  return elements[idx];
}
template <typename T> bool Vector<T>::operator==(const Vector &other) const {
  return elements == other.elements;
}
// With vectors -------------
template <typename T> Vector<T> &Vector<T>::operator+=(const Vector<T> &other) {

  std::size_t my_size = std::size(elements), other_size = other.size();
  if (my_size != other_size) {
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah");
  }
  for (std::size_t i{}; i < my_size; ++i) {

    elements[i] += other[i];
  }
  return *this;
}

template <typename T> Vector<T> &Vector<T>::operator-=(const Vector<T> &other) {

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
template <typename T> Vector<T> &Vector<T>::operator*=(T scalar) {
  for (std::size_t i{}; i < size(); ++i) {

    elements[i] *= scalar;
  }
  return *this;
}

template <typename T> Vector<T> &Vector<T>::operator/=(T scalar) {
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
template <typename T> Vector<T> operator*(Vector<T> v, T scalar) {
  v *= scalar;
  return v;
}
template <typename T> Vector<T> operator*(T scalar, Vector<T> v) {
  v *= scalar;
  return v;
}

// personal arbitrary choice but perhaps 1 / v is potentially dubious, but idk
// lol :3
template <typename T> Vector<T> operator/(Vector<T> v, T scalar) {
  v /= scalar;
  return v;
}

// Vector operator/(const double scalar, Vector v) {
// v /= scalar;
// return v;
// }

//-----------------------

// With vectors-----------
template <typename T> Vector<T> operator-(Vector<T> v1, const Vector<T> &v2) {
  v1 -= v2;
  return v1;
}
template <typename T> Vector<T> operator+(Vector<T> v1, const Vector<T> &v2) {
  v1 += v2;
  return v1;
}

//---------------------
//
// --------------------------------------------------------------------------------

template <typename T> std::size_t Vector<T>::size() const {
  return std::size(elements);
}
// Constructors
template <typename T> Vector<T>::Vector() { elements = std::vector<T>{}; }
template <typename T>
Vector<T>::Vector(std::size_t len)

    : elements(len) {};

template <typename T> Vector<T>::Vector(std::vector<T> input_elements) {
  elements = input_elements;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> values) : elements(values) {}

template <typename T> void Vector<T>::print_vector() {

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
template <typename T> T dot(const Vector<T> &v1, const Vector<T> &v2) {
  std::size_t size1 = v1.size(), size2 = v2.size();
  // Perhaps there's a way to create custom exceptions idk
  if (size1 != size2) {
    throw std::invalid_argument("Eep the dimensions need to agree! aaaaah\n");
  }
  T prod{0};
  for (std::size_t i{}; i < size1; i++) {
    prod += v1[i] * v2[i];
  }
  return prod;
}

template <typename T> T Vector<T>::squared_norm() const {
  return dot(*this, *this);
}

} // namespace selus
#endif

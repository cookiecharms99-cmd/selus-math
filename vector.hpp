#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <vector>
class Vector {

  std::vector<double> elements{};

public:
  // Assign vector Operators------------------------------------
  double &operator[](std::size_t idx);
  const double &operator[](std::size_t idx) const;
  // Equivalence operator
  bool operator==(const Vector &other);

  Vector &operator+=(const Vector &other);
  Vector &operator-=(const Vector &other);
  // Element wise!
  Vector &operator*=(const Vector &other);
  Vector &operator/=(const Vector &other);

  // assign Scalar operators-------------------
  Vector &operator*=(double scalar);
  Vector &operator/=(double scalar);
  //--------------------------------------------

  //-------------------------------------------------------------
  // Constructors----------------------------------------------
  Vector();
  Vector(std::size_t len);
  Vector(std::vector<double> input_elements);
  Vector(std::initializer_list<double> list);
  //--------------------------------------------------------------
  //
  //
  // Auxillary functions!-------
  void print_vector();
  std::size_t size() const;

  //-----------------------------
  //
  //
  // Math functions! -----------------
  double squared_norm() const;
};

// External vector operations.
/*
 *
 * So far v1 + v2
 *  v1 . v2
 */
// Operators!--------------------------------------------------------

// Vector operations---------
Vector operator+(Vector v1, const Vector &v2);
Vector operator-(Vector v1, const Vector &v2);

// Define these ones element wise
Vector operator*(Vector v1, const Vector &v2);
Vector operator/(Vector v1, const Vector &v2);

//---------------------------

// Scalar operations! --------
Vector operator*(Vector v, double scalar);
Vector operator*(double scalar, Vector v);

Vector operator/(Vector v, double scalar);
//-----------------------------

// ------------------------------------------------------------------
double dot(const Vector &v1, const Vector &v2);

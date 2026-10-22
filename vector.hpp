
#include <vector>

class Vector {

  std::vector<double> elements{};

public:
  std::size_t size() const;
  double squared_norm() const;
  double &operator[](std::size_t idx);
  Vector();
  Vector(std::size_t len);
};

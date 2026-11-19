#include <iostream>

#include <bit>
#include <selus/fft.hpp>
#include <selus/matrix.hpp>
#include <selus/vector.hpp>
using namespace selus;
int main() {
  Vector<std::complex<double>> V{1, 2, 3, 4, 5, 6, 7, 8};

  Vector<std::complex<double>> U = fft(V);
  U.print_vector();
  V = ifft(U);
  V.print_vector();

  return 0;
}

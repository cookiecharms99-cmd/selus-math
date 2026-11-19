#include <cassert>
#include <iostream>

#include <selus/fft.hpp>
#include <selus/matrix.hpp>
#include <selus/vector.hpp>

int main()

{
  Vector<std::complex<double>> x = {1, 2, 3, 4};
  Vector<std::complex<double>> check_x = idft(dft(x));
  check_x.print_vector();
}

#include "matrix.hpp"
#include "vector.hpp"
#include <bit>
#include <complex>
#include <numbers>
using namespace selus;
Vector<std::complex<double>> dft(Vector<std::complex<double>> x) {

  std::size_t N = x.size();

  // make the exponential kernel!
  //
  //
  Matrix<std::complex<double>> kernel(N, N);
  for (std::size_t n{}; n < N; ++n) {
    for (std::size_t k{}; k < N; ++k) {
      double angle = -2.0 * k * n * std::numbers::pi / N;
      kernel[k][n] = std::exp(std::complex<double>(0.0, angle));
    }
  }
  return kernel * x;
}

Vector<std::complex<double>> idft(Vector<std::complex<double>> x) {

  std::size_t N = x.size();

  // make the exponential kernel!
  //
  //
  Matrix<std::complex<double>> kernel(N, N);
  for (std::size_t n{}; n < N; ++n) {
    for (std::size_t k{}; k < N; ++k) {
      double angle = 2.0 * k * n * std::numbers::pi / N;
      kernel[k][n] = std::exp(std::complex<double>(0.0, angle)) * 1.0 /
                     (static_cast<double>(N));
    }
  }
  return kernel * x;
}

std::size_t bit_reversed(std::size_t idx, std::size_t bits) {
  std::size_t rev{0};
  for (std::size_t i{0}; i < bits; ++i) {
    rev <<= 1;
    rev = (rev | (idx & 1));
    idx >>= 1;
  }
  return rev;
}

void fft(std::span<std::complex<double>> data, bool inverse = false) {

  std::size_t n = data.size();
  if (!std::has_single_bit(n)) {
    throw std::invalid_argument("FFT size must be a power of 2 :D");
  }
  if (n == 1)
    return;

  std::size_t bits = std::countr_zero(n);
  // Swap all of x to construct the tree :3

  for (std::size_t i{0}; i < n; ++i) {
    std::size_t rev = bit_reversed(i, bits);
    if (i < rev)
      std::swap(data[i], data[rev]);
  }
  // With the tree now constructed, go in various stages for each length, then
  // traverse each block, then conduct the fft trick step inside :)
  for (std::size_t length{2}; length <= n; length <<= 1) {
    std::size_t half = length >> 1;

    double angle = -2.0 * std::numbers::pi / length;
    if (inverse) {
      angle *= -1;
    }
    std::complex<double> w_step = std::polar(1.0, angle);

    for (std::size_t i{0}; i < n; i += length) {
      std::complex<double> w = 1.0;
      for (std::size_t j{0}; j < half; ++j) {
        auto u = data[i + j];
        auto v = w * data[i + j + half];
        data[i + j] = u + v;
        data[i + j + half] = u - v;
        w *= w_step;
      }
    }
  }
}

void ifft(std::span<std::complex<double>> data) {
  fft(data, true);
  std::size_t n = data.size();
  for (std::size_t i{0}; i < n; ++i) {
    data[i] /= n;
  }
}

// Create new fft'd vector

Vector<std::complex<double>> fft(Vector<std::complex<double>> v) {
  fft(v.span()); // calls your existing span version on the copy!
  return v;      // hands back the transformed Vector
}

Vector<std::complex<double>> ifft(Vector<std::complex<double>> v) {
  ifft(v.span()); // calls your existing span version on the copy!
  return v;       // hands back the transformed Vector
}

#include <chrono>
#include <complex>
#include <iostream>
#include <random>
#include <selus/fft.hpp>
#include <selus/matrix.hpp>
#include <selus/vector.hpp>

double test_dft(std::size_t N) {
  Vector<std::complex<double>> v(N), u(N);

  // Random values are usually better for benchmarking so the CPU
  // doesn't benefit from trivial zero-multiplications or predictable branches.
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for (std::size_t i{0}; i < N; ++i) {
    v[i] = {dist(gen), dist(gen)};
  }

  auto t_0 = std::chrono::steady_clock::now();
  u = dft(v); // Capture result so the compiler doesn't optimize it away
  auto t_1 = std::chrono::steady_clock::now();

  std::chrono::duration<double> dft_time = t_1 - t_0;
  std::cout << "dft time: " << dft_time.count() << " s\n";

  auto t_2 = std::chrono::steady_clock::now();
  v = idft(u);
  auto t_3 = std::chrono::steady_clock::now();
  std::chrono::duration<double> idft_time = t_3 - t_2;
  std::cout << "inv dft time: " << idft_time.count() << " s\n";

  // Touch the output so the compiler must actually compute both transforms
  std::cout << "sample check: " << u[0] << "\n";

  return (idft_time + dft_time).count();
}

double test_fft(std::size_t N) {

  std::vector<std::complex<double>> vec(N);

  // Random values are usually better for benchmarking so the CPU
  // doesn't benefit from trivial zero-multiplications or predictable branches.
  std::mt19937 gen(42);
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for (std::size_t i{0}; i < N; ++i) {
    vec[i] = {dist(gen), dist(gen)};
  }
  std::span<std::complex<double>> v{vec};

  auto t_0 = std::chrono::steady_clock::now();
  fft(v); // Capture result so the compiler doesn't optimize it away
  auto t_1 = std::chrono::steady_clock::now();

  std::chrono::duration<double> fft_time = t_1 - t_0;
  std::cout << "fft time: " << fft_time.count() << " s\n";

  auto t_2 = std::chrono::steady_clock::now();
  ifft(v);
  auto t_3 = std::chrono::steady_clock::now();
  std::chrono::duration<double> ifft_time = t_3 - t_2;
  std::cout << "inv fft time: " << ifft_time.count() << " s\n";

  // touch output so compiler doesn't ignore the output
  std::cout << v[0] << "\n";

  return (ifft_time + fft_time).count();
}

int main() {

  std::size_t sample_sizes[4] = {64, 256, 1024, 2048};
  for (std::size_t i{0}; i < 4; ++i) {
    double t = test_dft(sample_sizes[i]);
    double t_fft = test_fft(sample_sizes[i]);
    std::cout << "Sample Size " << sample_sizes[i] << "| time taken: " << t
              << "| time fft: " << t_fft << "\n";
  }
}

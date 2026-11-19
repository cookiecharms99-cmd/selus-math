# ⚔️ Selus Math Quest — 11/17

**Goal:** Prepare `selus-math` for complex-valued quantum wavefunctions ($\psi \in \mathbb{C}$) and multi-project reuse so our upcoming **Bose-Einstein Condensate (BEC) Split-Step Fourier solver** can include and call it cleanly from a separate repo.

---

## 🗺️ Order of Operations

1. **Template `Matrix<T>` (and `Vector<T>`) inside `selus-math`**
   - Unlock `Matrix<std::complex<double>>` without duplicating code.
2. **Package `selus-math` for external directories**
   - Expose clean headers so a sibling `bec-sim` project can `#include <selus/matrix.hpp>` out of the box.
3. **1D $\rightarrow$ 2D Cooley-Tukey FFT (`fft.hpp`)**
   - Implement in-place radix-2 `fft` / `ifft` over `std::span<std::complex<double>>`, then extend to 2D `fft2` / `ifft2` on `Matrix<std::complex<double>>`.

---

## ✅ Quest Checklist

### Phase 1: Header-Only Template Refactor (`selus-math`)

- [x] **Move `Matrix` definitions into `matrix.hpp`** (or `include/selus/matrix.hpp`) since C++ templates must be visible to the compiler at instantiation time.
- [x] **Parameterize `template <typename T = double> class Matrix`:**
  - [ ] Replace hardcoded `double` storage (`std::vector<T> elements`) and element accessors (`T& operator()`, `std::span<T> operator[]`).
  - [ ] Update constructors (`Matrix(rows, cols)` default-initializing `T{}` so `0.0` works for both `double` and `std::complex<double>`).
  - [ ] Update member & free arithmetic operators (`+=`, `-=`, `*=`, `/=`, `+`, `-`, `*`, `transpose()`).
- [ ] _(Optional)_ Template `Vector<T = double>` in `vector.hpp` using the same pattern.
- [ ] **Verify in `tests/test_matrix.cpp`:**
  - [x] Confirm existing `Matrix<>` / `Matrix<double>` tests still pass unchanged.
  - [x] Add `<complex>` test cases: construct a `Matrix<std::complex<double>>`, verify `+=`, scalar multiply by `std::complex<double>(0.0, 1.0)`, `transpose()`, and `i-k-j` matrix product (e.g., Pauli-$Y$ $\begin{pmatrix} 0 & -i \\ i & 0 \end{pmatrix}$ squared equals $I_2$).

### Phase 2: Packaging `selus-math` for Sibling Projects

- [ ] **Organize public headers** under `include/selus/` (`matrix.hpp`, `vector.hpp`, and soon `fft.hpp`) so includes read `#include <selus/matrix.hpp>`.
- [ ] **Add a minimal build/install or include setup** (`CMakeLists.txt` interface target or `justfile` flags `-I../selus-math/include -std=c++20`).
- [ ] **Smoke-test from a sibling directory (`../bec-sim`):**
  - [ ] Create `bec-sim/main.cpp`, `#include <selus/matrix.hpp>`, instantiate a $64 \times 64$ `selus::Matrix<std::complex<double>>` wavefunction grid, and compile cleanly.

### Phase 3: 1D $\rightarrow$ 2D Cooley-Tukey FFT (`include/selus/fft.hpp`)

- [ ] **1D Radix-2 FFT (`fft` / `ifft`):**
  - [ ] Bit-reversal permutation pass in-place on `std::span<std::complex<double>>` (require power-of-two length $N$).
  - [ ] Iterative butterfly stages ($\log_2 N$ stages) using twiddle factors $W_N^k = e^{\mp 2\pi i k / N}$, scaling by $1/N$ on `ifft`.
  - [ ] Test round-trip `ifft(fft(x)) ≈ x` and Parseval's theorem $\sum |x_n|^2 = \frac{1}{N}\sum |X_k|^2$.
- [ ] **2D FFT (`fft2` / `ifft2` on `Matrix<std::complex<double>>`):**
  - [ ] Apply 1D `fft` row-by-row via zero-copy `grid[r]` spans.
  - [ ] Transpose $\rightarrow$ apply 1D `fft` row-by-row again $\rightarrow$ transpose back (keeping every 1D FFT pass contiguous in L1 cache!).
  - [ ] Test 2D round-trip `ifft2(fft2(grid)) ≈ grid` before plugging into Split-Step Fourier time evolution in `bec-sim`.

---

## 🧠 Key C++ & Physics Reminders for Today

- **Why templates live in headers:** The compiler generates machine code for `Matrix<std::complex<double>>` only when a `.cpp` file instantiates it—if method definitions stay hidden in `matrix.cpp`, the linker throws `undefined reference` errors.
- **Conjugate transpose vs. transpose:** Remember `transpose()` swaps $(r, c) \leftrightarrow (c, r)$ without complex conjugation; if we need Hermitian adjoint $A^\dagger$ later for quantum operators, add a separate `dagger()` / `conj_transpose()` method!
- **Keep scope bounded:** Aim to finish **Phase 1** (and Phase 2 smoke-test if energy permits) today, then tackle **Phase 3 (FFT)** fresh.

# 🧭 Today's Quest — Sunday, Nov 15, 2026

## 🎯 North Star: Two-Stage `selus-math` Roadmap

1. **Stage 1 (This Week — Computational Physics):** Generalize `selus-math` to support templated `Matrix<T>` (specifically `Matrix<std::complex<double>>`), transpose, elementwise ops, and a 1D/2D Cooley-Tukey FFT $\rightarrow$ call `selus-math` from a separate **`bec-sim`** repo to run a 1D $\rightarrow$ 2D Split-Step Fourier Gross-Pitaevskii (BEC) simulation and render plots/GIFs.
2. **Stage 2 (Week 2+ — ML Systems & Kernels):** Add cache-friendly `i-k-j` matrix multiplication (`GEMM`), benchmark against naive `i-j-k` (CS:APP cache-line check), and build a tiny tape-based reverse-mode autodiff engine.

---

## 🛠️ Quest 1: `selus-math` — Lock In `Matrix` Core (60–90 min)

_Starting point: `Vector` complete; `Matrix` header & constructor draft written._

- [x] **Fix & Compile `Matrix` Constructors (`matrix.cpp`):**
  - Initialize/resize `elements` (`rows * cols`) before writing in `std::vector<std::vector<double>>` and `flat` constructors.
  - Add row-width validation (`std::invalid_argument` on jagged rows or mismatched flat size) and empty-matrix guard (`mat.empty()`).
  - Delegate `std::initializer_list<std::vector<double>>` constructor to the `std::vector<std::vector<double>>` constructor.
- [x] **Implement Core Element Access & Metadata (`const`-correct):**
  - `rows() const`, `cols() const`, and `flat_idx(r, c) const`.
  - `double& operator()(std::size_t r, std::size_t c)` and `const double& operator()(std::size_t r, std::size_t c) const`.
  - _(Optional C++20 flex)_ `std::span<double> operator[](std::size_t row)` so `m[r][c]` works zero-copy.
- [x] **Implement Basic Matrix Operations:**
  - `operator==` (mark `const` on both `Vector` and `Matrix`), `operator+=`, `operator-=`, scalar `*=`, `/=`, and elementwise Hadamard product (`hadamard` or `elem_mul`).
  - `transpose() const` (critical so 2D column-FFTs run contiguously in L1 cache!).
- [x] **Sanity Test & Commit:**
  - Write a quick `tests/test_matrix.cpp` (or `main.cpp` assertions) verifying constructors, `(r, c)` indexing, transpose, and jagged-row exception handling $\rightarrow$ `git commit`.

---

## 📚 Quest 2: Sunday Weekly Review & Grade Guardrail (15–20 min)

_Cookie Academy Sunday check-in — protect the 80% grade floor without overworking._

- [ ] **Canvas Quick Scan:** Verify all upcoming deadlines for **Computer Logic Design** (priority grade watch), **Software Design**, **Systems Programming (C++)**, and **Intro to Philosophy**.
- [ ] **Prep Next Session's Hook:** Leave a 2-line note at the bottom of `README.md` or `quest.md` noting where `Matrix` stopped so the next session jumps straight into templating `Matrix<std::complex<double>>` + 1D Cooley-Tukey FFT.

---

## 🧸 Reward / Cooldown

- Protect your evening free block once `Matrix` compiles and passes sanity checks — zero productivity debt!

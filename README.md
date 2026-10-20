# selus-math ⚡

A modern C++20 header-and-source numerical math library built for physical simulations, graphics pipelines, and scientific computing. Designed from the hardware up with cache locality, SIMD vectorization, and compile-time evaluation in mind.

## Motivation & Architecture
Many general-purpose linear algebra libraries are either heavy legacy monoliths or abstract away low-level memory layout. `selus-math` explores the direct link:

$$\text{Mathematical Formulation} \longrightarrow \text{Contiguous Cache Alignment} \longrightarrow \text{Hardware SIMD Vectorization}$$

Built to serve as the high-throughput numerical backbone for fluid and dynamical solvers (such as *SliPpy* [a future planned project for fluid dynamics]), while establishing idiomatic modern C++ systems patterns.

## Features
- **Modern C++20 / C++23:** Constrained templates, `constexpr` math pipelines, and zero-cost abstraction.
- **Hardware-Conscious Layout:** Explicit data alignment (`alignas(16)`, `alignas(32)`) for AVX2/NEON vector instructions.
- **Strict RAII & Ownership:** Explicit Rule-of-Five copy/move semantics; zero unmanaged heap allocations or raw pointer leaks.
- **Cache-Optimized Storage:** Row-major dynamic matrix buffers designed for sequential stride and cache-line friendliness.
- **Benchmarking Suite:** Integrated microbenchmarks measuring latency, throughput, and cache misses against standard naive implementations.

## Directory Structure


# Selus Math ⚡ Mission Map

Selus is a learning project for exploring **modern C++, numerical computing, and eventually high-performance computing** by building a small linear algebra library.

The goal is **not** to recreate Eigen or BLAS.

The goal is to repeatedly:

> build something → understand it → measure it → improve it

Correctness and understanding come before clever optimization.

---

## 🌱 Mission 1: A Real Vector Type

Turn the current baby `Vector` into something pleasant enough to actually use for linear algebra.

Possible capabilities:

- Vector construction and initialization
- Read and write element access
- Const-correct element access
- Vector addition and subtraction
- Scalar multiplication
- Dot product
- Norm / squared norm
- Dimension checking
- Useful printing/debugging

### C++ concepts encountered

Learn these as they become necessary rather than studying all of them in advance.

- Constructors
- References
- `const`
- Operator overloading
- Range-based loops
- Exceptions / assertions
- Header and implementation organization
- Standard library containers

### Finish line

We should be able to naturally express computations such as:

```cpp
Vector a{/* ... */};
Vector b{/* ... */};

Vector c = a + b;
double d = dot(a, b);
```

and understand the important C++ machinery that makes this work.

---

## 🧮 Mission 2: Enter the Matrix

Build a basic dense `Matrix` type.

Explore:

- Contiguous matrix storage
- `(row, column)` indexing
- Matrix-vector multiplication
- Matrix-matrix multiplication
- Transpose
- Identity and zero matrices
- Dimension checking

### Important question

How should a 2D mathematical object actually be represented in 1D memory?

This is our first bridge from **linear algebra → memory layout → computer architecture**.

---

## 🧬 Mission 3: Generic Mathematics

Our library currently assumes `double`.

Investigate whether vectors and matrices should instead support multiple numeric types.

Possible destination:

```cpp
Vector<float>
Vector<double>
Matrix<double>
```

Topics may include:

- Templates
- Type deduction
- Concepts / constraints
- Compile-time vs runtime decisions

Do not generalize merely because C++ allows it. We should have a reason.

---

## 🧪 Mission 4: Trust the Math

Before chasing speed, make Selus trustworthy.

Add:

- Unit tests
- Floating-point comparison helpers
- Edge-case tests
- Debug assertions
- Simple numerical experiments

Compare selected results against known answers or an established numerical library.

**Rule:** an optimized wrong answer is still wrong, only faster.

---

## ⏱️ Mission 5: Measure Before Optimizing

Create benchmarks for important operations:

- Dot product
- Vector addition
- Matrix-vector multiplication
- Matrix-matrix multiplication

Learn to distinguish:

- Algorithmic cost
- Constant factors
- Compiler optimization
- Measurement noise
- Debug vs release builds

Establish boring, obvious implementations as baselines.

Then measure them.

---

## 🧠 Mission 6: Meet the Hardware

Now Selus and CS:APP begin colliding.

Investigate:

- Cache locality
- Row-major vs column-major traversal
- Memory bandwidth
- Compiler auto-vectorization
- Loop transformations
- Data alignment
- SIMD

For each optimization:

1. Predict what should happen.
2. Benchmark before.
3. Change one meaningful thing.
4. Benchmark after.
5. Explain the result.

Treat performance work like an experiment.

---

## ⚔️ Mission 7: Matrix Multiplication Boss Fight

Use matrix multiplication as our first serious optimization laboratory.

Start with the obvious triple loop.

Then investigate things such as:

- Loop ordering
- Cache behavior
- Blocking / tiling
- SIMD
- Parallelism

Compare against a serious implementation such as Eigen or BLAS.

The interesting question isn't merely:

> "Are we slower?"

It is:

> **Why?**

---

# 🌌 Later Possibilities

Only unlock these when earlier missions give us a reason.

- Iterators
- `std::span`
- Move semantics
- Expression templates
- Custom allocators
- Multithreading
- Sparse matrices
- Numerical decompositions
- Automatic differentiation
- GPU computation

Selus may eventually become useful infrastructure for future physics, graphics, autograd, or fluid-dynamics projects.

But there is no rush.

---

# 🍪 Selus Rules

1. **Understand before abstracting.**
2. **Correctness before performance.**
3. **Measure before optimizing.**
4. **Prefer experiments over performance folklore.**
5. **Use modern C++ when it solves an actual problem.**
6. **Do not turn Selus into Tutorial Purgatory.**
7. **It is okay for the implementation to be naive. That's what gives us something to improve.**

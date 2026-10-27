# 🍪 Selus Math: Today's Quest

## 🧮 Main Quest: Matrix Begins

`Vector` has a basic safety net now. Time to begin the Matrix arc.

### Goal

Design the **representation** of a `Matrix` before implementing lots of matrix operations.

We want something that can eventually support:

- matrix-vector multiplication
- matrix-matrix multiplication
- transpose
- numerical experiments
- cache/locality experiments
- SIMD and other optimization work later

But today: **representation first.**

---

## Quest 1: How Does a Matrix Live in Memory?

Suppose we want:

$[A =
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6
\end{bmatrix}]$

Before writing `Matrix`, answer:

### A. What are some possible C++ representations?

Think of at least **two**.

For example, could we use:

- several vectors?
- one vector?
- something else?

Don't worry yet about which is best.

### B. If all six values are stored in one contiguous array as:

```text
1 2 3 4 5 6
```

how could we map:

```text
(row, column)
```

onto a single array index?

Try to derive the formula yourself for a matrix with:

```text
rows = R
columns = C
```

Assume indexing begins at zero.

### C. Predict the hardware consequence

Suppose we traverse a large matrix in these two orders:

```cpp
for (row ...)
    for (col ...)
        use(matrix(row, col));
```

versus:

```cpp
for (col ...)
    for (row ...)
        use(matrix(row, col));
```

If our representation stores complete rows contiguously, which traversal would you predict is faster?

Explain **why**, using what you remember from CS about memory/cache behavior.

No benchmarking yet. Prediction first. 🔬

---

## Quest 2: Sketch the Class

Once the representation decision makes sense, sketch a minimal interface.

Something approximately capable of:

```cpp
Matrix A(2, 3);

A(0, 0) = 1;
A(0, 1) = 2;

const Matrix B{/* someday */};
double x = B(1, 2);
```

Questions to decide:

1. What private data does `Matrix` actually need?
2. How should `operator()` map `(row, col)` onto storage?
3. Do we need both const and non-const versions of `operator()`?
4. Which lessons from `Vector` can we reuse instead of rediscovering?

Don't implement matrix arithmetic yet.

---

## 🧪 Tiny Vector Cleanup

Before Matrix work, add these remaining tests if they aren't already present:

- ordinary arithmetic does not mutate its operands
- a `const Vector` can be indexed
- `dot(a, b)` throws when dimensions disagree

Then Vector gets to rest. It has worked hard. :3

---

## 🌱 Optional Rabbit Hole

Only if curiosity strikes:

> Why might `std::vector<std::vector<double>>` behave differently from one flat `std::vector<double>` even though both can represent the same mathematical matrix?

Try reasoning from object layout and memory locality before looking anything up.

---

## 🏁 Success Condition

Today is successful if I can explain:

> **how Selus will represent a matrix, why we chose that representation, and how `(row, col)` becomes a memory location.**

Actually implementing the whole Matrix class is **not required**.

Understanding the representation is the quest.

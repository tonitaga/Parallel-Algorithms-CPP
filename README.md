# Parallel Algorithms


## Install

---
To install the parallel algorithms implementation, follow these steps:

1. Clone or download the matrix library repository.

```shell
git clone https://github.com/tonitaga/Parallel-Algorithms-CPP.git
```

2. Ensure you have the g++ compiler installed on your system.
3. Build all targets

```shell
make all
```

Or build them separately

```shell
make ant
```

```shell
make gauss
```

```shell
make winograd
```

4. Run need target

```shell
make run_ant
```

```shell
make run_gauss
```

```shell
make run_winograd
```

## Ant colony optimization

---

[Ant Colony Optimization article <- click](https://habr.com/ru/companies/timeweb/articles/754462/)

The Ant Colony Optimization algorithm is a algorithm
inspired by the foraging behavior of ants.

It uses a probabilistic approach to find optimal solutions 
by simulating the pheromone trail communication and collective
decision-making of ants, effectively exploring and exploiting solution spaces.

In the parallel version, we employed two approaches within
the same algorithm based on the size of the input data:
1) If the graph size exceeds 50, additional computation threads are utilized.
2) If the graph size is less than 50, we employ parallel computation using the `<execution> -> std::execution::par` library.
Irrespective of the graph size, ants are created in parallel
in the parallel algorithm to expedite their creation time.

## Gauss elimination

---

The Gauss Algorithm, also known as the Gauss Method, is an alternative way
to solve a system of linear algebraic equations.

The advantage of this method is its simplicity,
as it only requires a piece of paper and knowledge of addition and
subtraction.

To implement parallel calculations, we have used OpenMP
directives, specifically parallelization of the main for loop using the
'#pragma omp parallel for' directive.

It is well-known that parallel computation can be costly,
so sequential computation will be faster for small data sizes.
To observe the performance, create a matrix with sizes starting
from 250.

## Winograd algorithm

---

The Winograd algorithm is an optimized matrix multiplication 
method that was proposed by Winograd

This algorithm is based on the observation that some calculations
in a standard matrix multiplication algorithm can be performed
in advance and their results can be reused to reduce the number of
"operations.

#include <benchmark/benchmark.h>
#include <matrix_cache/matrix.h>

static void BM_Matrix_Constructor(benchmark::State &state) {
  for (auto _ : state) {
    Matrix m(state.range(0), state.range(0));
  }
}

static void BM_Matrix_Randomization(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix m(state.range(0), state.range(0));
    state.ResumeTiming();
    m.randomize(1, 1e0);
  }
}

static void BM_Matrix_Transposition(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix m(state.range(0), state.range(0));
    m.randomize(1, 1e0);
    state.ResumeTiming();
    m.transpose();
  }
}

static void BM_Matrix_Multiplication(benchmark::State &state) {
  for (auto _ : state) {
    Matrix m1(state.range(0), state.range(0));
    Matrix m2(state.range(0), state.range(0));

    m1.randomize(1, 1e10);
    m2.randomize(1, 1e10);

    m1 *m2;
  }
}

static void BM_Matrix_Multiplication_transposed(benchmark::State &state) {
  for (auto _ : state) {
    Matrix m1(state.range(0), state.range(0));
    Matrix m2(state.range(0), state.range(0));

    m1.randomize(1, 1e10);
    m2.randomize(1, 1e10);

    m1 ^ m2.transpose();
  }
}

BENCHMARK(BM_Matrix_Constructor)->DenseRange(200, 2e3, 200);
BENCHMARK(BM_Matrix_Randomization)->DenseRange(200, 2e3, 200);
BENCHMARK(BM_Matrix_Transposition)->DenseRange(200, 2e3, 200);
BENCHMARK(BM_Matrix_Multiplication)->DenseRange(200, 2e3, 200);
BENCHMARK(BM_Matrix_Multiplication_transposed)->DenseRange(200, 2e3, 200);
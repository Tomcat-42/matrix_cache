#include <benchmark/benchmark.h>
#include <matrix_cache/matrix.h>
#define INITIAL_SIZE 200
#define FINAL_SIZE 2e3
#define STEP_SIZE 200

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
    state.PauseTiming();
    Matrix m1(state.range(0), state.range(0));
    Matrix m2(state.range(0), state.range(0));

    m1.randomize(1, 1e10);
    m2.randomize(1, 1e10);
    state.PauseTiming();

    m1 *m2;
  }
}

static void BM_Matrix_Multiplication_transposed(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix m1(state.range(0), state.range(0));
    Matrix m2(state.range(0), state.range(0));
    Matrix m3;

    m1.randomize(1, 1e10);
    m2.randomize(1, 1e10);
    state.ResumeTiming();

    m1 ^ m2.transpose();
  }
}

static void BM_Matrix_Multiplication_transposed_without_transposition_time(
    benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    Matrix m1(state.range(0), state.range(0));
    Matrix m2(state.range(0), state.range(0));
    Matrix m3;

    m1.randomize(1, 1e10);
    m2.randomize(1, 1e10);
    m3 = m2.transpose();
    state.ResumeTiming();

    m1 ^ m3;
  }
}

BENCHMARK(BM_Matrix_Constructor)
    ->DenseRange(200, 2e3, 200)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(INITIAL_SIZE, FINAL_SIZE, STEP_SIZE);

BENCHMARK(BM_Matrix_Randomization)
    ->DenseRange(200, 2e3, 200)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(INITIAL_SIZE, FINAL_SIZE, STEP_SIZE);

BENCHMARK(BM_Matrix_Transposition)
    ->DenseRange(200, 2e3, 200)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(INITIAL_SIZE, FINAL_SIZE, STEP_SIZE);

BENCHMARK(BM_Matrix_Multiplication)
    ->DenseRange(200, 2e3, 200)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(200, 400, 200);

BENCHMARK(BM_Matrix_Multiplication_transposed)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(INITIAL_SIZE, FINAL_SIZE, STEP_SIZE);

BENCHMARK(BM_Matrix_Multiplication_transposed_without_transposition_time)
    ->ComputeStatistics("min",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::min_element(std::begin(v), std::end(v)));
                        })
    ->ComputeStatistics("max",
                        [](const std::vector<double> &v) -> double {
                          return *(
                              std::max_element(std::begin(v), std::end(v)));
                        })
    ->DenseRange(INITIAL_SIZE, FINAL_SIZE, STEP_SIZE);
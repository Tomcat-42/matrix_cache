#include <matrix_cache/utils.h>

#include <iostream>
#include <random>

using namespace std;

namespace utils {
using std::fabs;
using std::mt19937;
using std::numeric_limits;
using std::random_device;
using std::uniform_real_distribution;

RandomNumberBetween::RandomNumberBetween(double low, double high)
    : random_engine_(random_device()()), distribution_(low, high) {}

double RandomNumberBetween::operator()() {
  return distribution_(random_engine_);
}

bool absolute_tolerance_compare(double x, double y) {
  const double diff = fabs(x - y);
  // const double epsilon = numeric_limits<double>::epsilon();
  constexpr double epsilon = 1e-6;
  const bool result = diff <= epsilon;
  return result;
}
}  // namespace utils
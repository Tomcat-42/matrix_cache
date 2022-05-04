#include <matrix_cache/utils.h>

#include <random>

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
  return fabs(x - y) <= numeric_limits<double>::epsilon();
}

}  // namespace utils
#include <matrix_cache/utils.h>

#include <random>

namespace utils {

using std::default_random_engine;
using std::uniform_real_distribution;

double get_random_value(double min, double max) {
  uniform_real_distribution<double> distribution(min, max);
  default_random_engine generator;
  return distribution(generator);
}

}  // namespace utils
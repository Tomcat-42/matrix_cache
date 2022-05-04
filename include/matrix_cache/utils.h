#pragma once
#include <random>

namespace utils {

using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;

class RandomNumberBetween {
 public:
  RandomNumberBetween(double low, double high);
  double operator()();

 private:
  mt19937 random_engine_;
  uniform_real_distribution<double> distribution_;
};

bool absolute_tolerance_compare(double, double);

}  // namespace utils
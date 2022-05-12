#include <matrix_cache/matrix.h>

#include <cxxopts.hpp>
#include <iostream>

using cxxopts::Options;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {
  try {
    Options options(argv[0], "Matrix multiplication");

    // options.positional_help("[optional args]").show_positional_help();

    options.set_width(80).set_tab_expansion().allow_unrecognised_options();

    // clang-format off
    options.add_options()
      ("m,matrix", "The matrix dimensions e.g.: 3x3", cxxopts::value<std::vector<int>>())
      ("b,matrixb", "The B matrix dimensions e.g.: 3x3 3x3", cxxopts::value<std::vector<int>>())
      ("t,tranpose", "Method of multiplication set to transpose",cxxopts::value<bool>()->default_value("false"))
      ("h,help", "Print help");
    // clang-format on

    auto result = options.parse(argc, argv);
    auto a = result["matrix"].as<std::vector<int>>();
    if (result.count("help") || a.size() != 4) {
      cout << options.help() << endl;
      exit(0);
    }

    Matrix m1(a[0], a[1]);
    Matrix m2(a[2], a[3]);
    Matrix mr;
    bool transpose = result["tranpose"].as<bool>();

    m1.randomize(0, 1e10);
    m2.randomize(0, 1e10);

    cout << transpose << endl;

    mr = transpose ? m1 ^ m2.transpose() : m1 * m2;
  } catch (const cxxopts::OptionException& e) {
    cout << "error parsing options: " << e.what() << endl;
    return 1;
  } catch (const std::exception& e) {
    cout << "error: " << e.what() << endl;
    return 1;
  }
}
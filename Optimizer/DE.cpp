#include "DE.hpp"

#include <iostream>
#include <random>

auto initialize(int n, int dim, int seed) {
  std::vector<std::vector<double>> pop;
  pop.reserve(n);

  std::mt19937 mt(seed);
  std::uniform_real_distribution<> dist(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    std::vector<double> x;
    x.reserve(dim);
    for (int k = 0; k < dim; ++k) { x.emplace_back(dist(mt)); }
    pop.emplace_back(x);
  }
  return pop;
}

std::vector<double> DE::optimize(const FunctionInterface& func) {
  std::cerr << "[DE] start optimize" << std::endl;

  auto x = initialize(NP, dim, seed);
  for (const auto& p : x) {
    std::cout << p[0] << " " << p[1] << std::endl;
    auto y = func.f(p);
    std::cout << y << std::endl;
  }

  return {};
}

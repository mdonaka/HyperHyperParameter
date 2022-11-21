#include "DE.hpp"

#include <iostream>
#include <unordered_set>

auto initialize(int n, OptSettings& s) {
  std::vector<std::vector<double>> pop;
  pop.reserve(n);

  std::uniform_real_distribution<> dist(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    std::vector<double> x;
    x.reserve(s.dim);
    for (int k = 0; k < s.dim; ++k) { x.emplace_back(dist(s.mt)); }
    pop.emplace_back(x);
  }
  return pop;
}

auto mutation(int n, double f, const std::vector<std::vector<double>>& pops,
              OptSettings& s) {
  int dim = pops[0].size();
  std::vector<std::vector<double>> ms;
  ms.reserve(n);
  std::uniform_int_distribution<> dist(0, n - 1);
  for (int tgt = 0; tgt < n; ++tgt) {
    std::unordered_set<int> its;
    while (its.size() < 3) {
      auto it = dist(s.mt);
      if (it == tgt) { continue; }
      its.emplace(it);
    }
    auto v = std::vector<int>(its.begin(), its.end());
    std::vector<double> m;
    m.reserve(dim);
    for (int d = 0; d < dim; ++d) {
      m.emplace_back(pops[v[0]][d] - f * (pops[v[1]][d] - pops[v[2]][d]));
    }
    ms.emplace_back(m);
  }
  return ms;
}

std::vector<double> DE::optimize(const FunctionInterface& func) {
  std::cerr << "[DE] start optimize" << std::endl;

  auto pops = initialize(NP, settings);
  for (int g = 0; g < (EVAL / NP) - 1; ++g) {
    std::cerr << "[DE] generation " << g << std::endl;
    auto ms = mutation(NP, F, pops, settings);
    for (const auto& m : ms) {
      for (const auto& d : m) { std::cout << d << " "; }
      std::cout << std::endl;
    }
  }

  return {};
}

#include "DE.hpp"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <unordered_set>

auto initialize(const std::shared_ptr<FunctionInterface>& func, int n,
                OptSettings& s) {
  std::vector<Poplation> pop;
  pop.reserve(n);

  std::uniform_real_distribution<> dist(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    std::vector<double> x;
    x.reserve(s.dim);
    for (int k = 0; k < s.dim; ++k) { x.emplace_back(dist(s.mt)); }
    pop.emplace_back(x, func->f(x));
  }
  return pop;
}

auto mutation(int n, double f, const std::vector<Poplation>& pops,
              OptSettings& s) {
  int dim = pops[0].x.size();
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
      m.emplace_back(pops[v[0]].x[d] - f * (pops[v[1]].x[d] - pops[v[2]].x[d]));
    }
    ms.emplace_back(m);
  }
  return ms;
}

auto crossover(const std::shared_ptr<FunctionInterface>& func, int n, double cr,
               std::vector<std::vector<double>> ms,
               const std::vector<Poplation>& pops, OptSettings& s) {
  int dim = pops[0].x.size();
  std::vector<Poplation> npops;
  npops.reserve(n);
  std::uniform_int_distribution<> dist_int(0, dim - 1);
  std::uniform_real_distribution<> dist_real(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    std::vector<double> p;
    p.reserve(dim);
    int sel = dist_int(s.mt);
    for (int d = 0; d < dim; ++d) {
      if (sel == d) {
        p.emplace_back(ms[i][d]);
      } else {
        int r = dist_real(s.mt);
        p.emplace_back((r < cr) ? ms[i][d] : pops[i].x[d]);
      }
    }
    npops.emplace_back(p, func->f(p));
  }
  return npops;
}

auto selection(int n, const std::vector<Poplation>& pop1,
               const std::vector<Poplation>& pop2) {
  std::vector<Poplation> dom;
  dom.reserve(n);
  for (int i = 0; i < n; ++i) {
    dom.emplace_back((pop1[i].y < pop2[i].y) ? pop1[i] : pop2[i]);
  }
  return dom;
}

Poplation DE::optimize(const std::shared_ptr<FunctionInterface>& func, bool log,
                       const std::string& result_file) {
  if (log) { std::cerr << "[DE] start optimize" << std::endl; }

  std::deque<double> result;
  auto pops = initialize(func, settings.np, settings);
  auto ans = pops[0];
  for (const auto& p : pops) { ans = std::min(ans, p); }
  result.emplace_back(ans.y);

  auto loop = settings.evalLim / settings.np - 1;
  for (int g = 0; g < loop; ++g) {
    if (log) { std::cerr << "[DE] generation " << g << std::endl; }
    auto ms = mutation(settings.np, F, pops, settings);
    auto npops = crossover(func, settings.np, CR, ms, pops, settings);
    pops = selection(settings.np, pops, npops);

    for (const auto& p : pops) { ans = std::min(ans, p); }
    result.emplace_back(ans.y);
  }
  if (result_file != "") {
    std::ofstream of("../Result/" + result_file);
    for (const auto& r : result) { of << r << std::endl; }
    of.close();
  }
  return ans;
}

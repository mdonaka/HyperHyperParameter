#include "Function.hpp"

#include <vector>

#include "DE.hpp"
#include "Parameter.hpp"

double Rosenbrock::f(const std::vector<double>& x_) const {
  int size = x_.size();

  std::vector<double> x;
  x.reserve(size);
  for (const auto& p : x_) { x.emplace_back(p * (max - min) + min); }

  double ret = 0.0;
  for (int i = 0; i < size - 1; ++i) {
    auto a = x[i + 1] - x[i] * x[i];
    auto b = x[i] - 1;
    ret += 100 * a * a + b * b;
  }
  return ret;
}

double F1::f(const std::vector<double>& x) const {
  auto settings = OptSettings(2, Param::NP, Param::EVAL, seed);
  auto de = DE(settings, x[0], x[1]);
  auto f = F();
  auto p = de.optimize(f);
  return p.y;
}

double F2::f(const std::vector<double>& x) const {
  auto settings = OptSettings(2, Param::NP, Param::EVAL, seed);
  auto de = DE(settings, x[0], x[1]);
  auto f = F1(seed);
  auto p = de.optimize(f);
  return p.y;
}


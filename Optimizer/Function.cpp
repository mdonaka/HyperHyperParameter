#include "Function.hpp"

#include <vector>

#include "DE.hpp"

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
  auto settings = OptSettings(2, 10, 100, seed);
  auto de = DE(settings, x[0], x[1]);
  auto f = F();
  auto [_, y] = de.optimize(f);
  return y;
}


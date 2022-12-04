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
double Rastrigin::f(const std::vector<double>& x_) const {
  int size = x_.size();

  std::vector<double> x;
  x.reserve(size);
  for (const auto& p : x_) { x.emplace_back(p * (max - min) + min); }

  double ret = 10.0 * size;
  const auto pi = std::acos(-1);
  for (const auto& t : x) { ret += t * t - 10.0 * std::cos(2.0 * pi * t); }
  return ret;
}
double Schwefel::f(const std::vector<double>& x_) const {
  int size = x_.size();

  std::vector<double> x;
  x.reserve(size);
  for (const auto& p : x_) { x.emplace_back(p * (max - min) + min); }

  double ret = 0.0;
  for (const auto& t : x) { ret += t * std::sin(std::sqrt(std::abs(t))); }
  return ret;
}

double F1::f(const std::vector<double>& x) const {
  auto settings = OptSettings(2, Param::NP, Param::EVAL, seed);
  auto de = DE(settings, x[0], x[1]);
  auto p = de.optimize(func);
  return p.y;
}

double F2::f(const std::vector<double>& x) const {
  auto settings = OptSettings(2, Param::NP, Param::EVAL, seed);
  auto de = DE(settings, x[0], x[1]);
  auto p = de.optimize(std::make_unique<F1>(func, seed));
  return p.y;
}
std::shared_ptr<FunctionInterface> selectFunction(const std::string& name) {
  if (name == "Rosenbrock") { return std::make_shared<Rosenbrock>(); }
  if (name == "Rastrigin") { return std::make_shared<Rastrigin>(); }
  if (name == "Schwefel") { return std::make_shared<Schwefel>(); }
  throw std::runtime_error("TODO");
}

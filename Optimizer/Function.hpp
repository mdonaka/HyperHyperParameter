#pragma once
#include <iostream>
#include <vector>

class FunctionInterface {
 public:
  virtual double f(const std::vector<double>& x) const = 0;
};

class Rosenbrock : public FunctionInterface {
  static inline int cnt = 0;
  static constexpr double min = -5;
  static constexpr double max = 5;

 public:
  double f(const std::vector<double>&) const;
};

class F1 : public FunctionInterface {
  // TODO: template
  using F = Rosenbrock;
  const int seed;

 public:
  F1(int seed) : seed(seed) {}
  double f(const std::vector<double>&) const;
};

class F2 : public FunctionInterface {
  // TODO: template
  using F = Rosenbrock;
  const int seed;

 public:
  F2(int seed) : seed(seed) {}
  double f(const std::vector<double>&) const;
};


#pragma once
#include <iostream>
#include <memory>
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
class Rastrigin : public FunctionInterface {
  static inline int cnt = 0;
  static constexpr double min = -5.12;
  static constexpr double max = 5.12;

 public:
  double f(const std::vector<double>&) const;
};

class Schwefel : public FunctionInterface {
  static inline int cnt = 0;
  static constexpr double min = -500.0;
  static constexpr double max = 500.0;

 public:
  double f(const std::vector<double>&) const;
};

class F1 : public FunctionInterface {
  const std::shared_ptr<FunctionInterface> func;
  const int seed;

 public:
  F1(const std::shared_ptr<FunctionInterface>& func, int seed)
      : func(std::move(func)), seed(seed) {}
  double f(const std::vector<double>&) const;
};

class F2 : public FunctionInterface {
  const std::shared_ptr<FunctionInterface> func;
  const int seed;

 public:
  F2(const std::shared_ptr<FunctionInterface>& func, int seed)
      : func(std::move(func)), seed(seed) {}
  double f(const std::vector<double>&) const;
};

std::shared_ptr<FunctionInterface> selectFunction(const std::string& name);

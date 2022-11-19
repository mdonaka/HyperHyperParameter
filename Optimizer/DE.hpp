#pragma once
#include <vector>

#include "Function.hpp"

class DE {
  static constexpr int NP = 10;

  const int dim;
  const double CR;
  const double F;
  const int seed;

 public:
  DE(int dim, double CR = 0.5, double F = 1.0, int seed = 112358)
      : dim(dim), CR(CR), F(F), seed(seed) {}
  std::vector<double> optimize(const FunctionInterface&);
};

#pragma once
#include <vector>

#include "Function.hpp"

class OptSettings {
 public:
  const int dim;
  const int evalLim;
  const int seed;
  OptSettings(int dim, int evalLim, int seed)
      : dim(dim), evalLim(evalLim), seed(seed) {}
};

class DE {
  const OptSettings settings;

  static constexpr int NP = 10;
  const double CR;
  const double F;

 public:
  DE(const OptSettings settings, double CR = 0.5, double F = 1.0)
      : settings(settings), CR(CR), F(F) {}
  std::vector<double> optimize(const FunctionInterface&);
};

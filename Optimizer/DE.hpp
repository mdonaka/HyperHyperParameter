#pragma once
#include <random>
#include <vector>

#include "Function.hpp"

class OptSettings {
 public:
  const int dim;
  const int evalLim;
  // TODO: 乱数だけ切り離してconst claasにする
  std::mt19937 mt;
  OptSettings(int dim, int evalLim, int seed)
      : dim(dim), evalLim(evalLim), mt(seed) {}
};

class DE {
  OptSettings settings;

  static constexpr int EVAL = 50;
  static constexpr int NP = 10;
  const double CR;
  const double F;

 public:
  DE(const OptSettings settings, double CR = 0.5, double F = 1.0)
      : settings(settings), CR(CR), F(F) {}
  std::vector<double> optimize(const FunctionInterface&);
};

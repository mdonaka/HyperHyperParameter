#pragma once
#include <random>
#include <vector>

#include "Function.hpp"

class OptSettings {
 public:
  const int dim;
  const int np;
  const int evalLim;
  // TODO: 乱数だけ切り離してconst claasにする
  std::mt19937 mt;
  OptSettings(int dim, int np, int evalLim, int seed)
      : dim(dim), np(np), evalLim(evalLim), mt(seed) {}
};

class DE {
  OptSettings settings;

  double min;
  std::vector<double> ans;
  std::vector<double> tmp;

  const double CR;
  const double F;

  void update(const std::vector<std::vector<double>>&,
              const FunctionInterface&);

 public:
  DE(const OptSettings settings, double CR = 0.5, double F = 1.0)
      : settings(settings), min(1e18), CR(CR), F(F) {}
  std::vector<double> optimize(const FunctionInterface&);
};

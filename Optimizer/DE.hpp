#pragma once
#include <random>
#include <vector>

#include "Function.hpp"
#include "Poplation.hpp"

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

  const double CR;
  const double F;

 public:
  DE(const OptSettings settings, double CR = 0.5, double F = 1.0)
      : settings(settings), CR(CR), F(F) {}
  Poplation optimize(const std::unique_ptr<FunctionInterface>&,
                     bool log = false, const std::string& result_file = "");
};

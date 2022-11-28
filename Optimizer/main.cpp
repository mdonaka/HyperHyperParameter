#include <iostream>

#include "DE.hpp"
#include "Function.hpp"
#include "Parameter.hpp"

auto run_f2(const FunctionInterface& f, int seed) {
  auto f2 = F2(seed);
  auto f1 = F1(seed);

  auto de2 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p2 = de2.optimize(f2, true);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), p2.x[0], p2.x[1]);
  auto p1 = de1.optimize(f1);

  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), p1.x[0], p1.x[1]);
  auto p0 = de0.optimize(f, false, "f2");

  p2.output();
  p1.output();
  p0.output();
}

auto run_f1(const FunctionInterface& f, int seed) {
  auto f1 = F1(seed);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p1 = de1.optimize(f1, true);

  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), p1.x[0], p1.x[1]);
  auto p0 = de0.optimize(f, false, "f1");

  p1.output();
  p0.output();
}

auto run_f0(const FunctionInterface& f, int seed) {
  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto pop = de0.optimize(f, true, "f0");

  pop.output();
}

int main() {
  int seed = 112358;
  auto rosen = Rosenbrock();

  run_f2(rosen, seed);
  run_f1(rosen, seed);
  run_f0(rosen, seed);
}

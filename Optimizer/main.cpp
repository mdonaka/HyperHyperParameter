#include <iostream>

#include "DE.hpp"
#include "Function.hpp"
#include "Parameter.hpp"

auto output(const std::vector<double>& x, double y) {
  std::cout << "x = { ";
  for (const auto& p : x) { std::cout << p << ", "; }
  std::cout << "}" << std::endl;
  std::cout << "y = " << y << std::endl;
}

auto run_f2(const FunctionInterface& f, int seed) {
  auto f2 = F2(seed);
  auto f1 = F1(seed);

  auto de2 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto [x2, y2] = de2.optimize(f2, true);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), x2[0], x2[1]);
  auto [x1, y1] = de1.optimize(f1);

  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), x1[0], x1[1]);
  auto [x0, y0] = de0.optimize(f, false, "f2");

  output(x2, y2);
  output(x1, y1);
  output(x0, y0);
}

auto run_f1(const FunctionInterface& f, int seed) {
  auto f1 = F1(seed);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto [x1, y1] = de1.optimize(f1, true);

  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), x1[0], x1[1]);
  auto [x0, y0] = de0.optimize(f, false, "f1");

  output(x1, y1);
  output(x0, y0);
}

auto run_f0(const FunctionInterface& f, int seed) {
  auto de0 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto [x0, y0] = de0.optimize(f, true, "f0");

  output(x0, y0);
}

int main() {
  int seed = 112358;
  auto rosen = Rosenbrock();

  run_f2(rosen, seed);
  run_f1(rosen, seed);
  run_f0(rosen, seed);
}

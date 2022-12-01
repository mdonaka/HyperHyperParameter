#include <iostream>
#include <random>

#include "DE.hpp"
#include "Function.hpp"
#include "Parameter.hpp"

auto run_f2(const FunctionInterface& f, int seed) {
  auto f2 = F2(seed);
  auto f1 = F1(seed);

  auto de2 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p2 = de2.optimize(f2);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), p2.x[0], p2.x[1]);
  auto p1 = de1.optimize(f1);

  p1.output();
  return std::pair<double, double>{p1.x[0], p1.x[1]};
}

auto run_f1(const FunctionInterface& f, int seed) {
  auto f1 = F1(seed);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p1 = de1.optimize(f1);

  p1.output();
  return std::pair<double, double>{p1.x[0], p1.x[1]};
}

auto run(std::string file, const FunctionInterface& f, double CR, double F) {
  auto seed = std::random_device()();
  std::mt19937 mt(seed);
  constexpr int loop = 100;
  for (int i = 0; i < 100; ++i) {
    auto de = DE(OptSettings(2, Param::NP, Param::EVAL, mt()), CR, F);
    de.optimize(f, false, file + std::to_string(i));
  }
}

int main() {
  int seed = 112358;
  auto rosen = Rosenbrock();

  {
    std::cerr << "[DE] start F2" << std::endl;
    auto [CR, F] = run_f2(rosen, seed);
    run("f2/result", rosen, CR, F);
  }
  {
    std::cerr << "[DE] start F1" << std::endl;
    auto [CR, F] = run_f1(rosen, seed);
    run("f1/result", rosen, CR, F);
  }
  {
    std::cerr << "[DE] start F1" << std::endl;
    run("f0/result", rosen, 0.5, 0.5);
  }
}

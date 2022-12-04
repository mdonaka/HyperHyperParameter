#include <iostream>
#include <random>

#include "DE.hpp"
#include "Function.hpp"
#include "Parameter.hpp"

auto run_f2(const std::shared_ptr<FunctionInterface>& f, int seed) {
  std::shared_ptr<FunctionInterface> f2 = std::make_shared<F2>(f, seed);
  std::shared_ptr<FunctionInterface> f1 = std::make_shared<F1>(f, seed);

  auto de2 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p2 = de2.optimize(f2);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed), p2.x[0], p2.x[1]);
  auto p1 = de1.optimize(f1);

  p1.output();
  return std::pair<double, double>{p1.x[0], p1.x[1]};
}

auto run_f1(const std::shared_ptr<FunctionInterface>& f, int seed) {
  std::shared_ptr<FunctionInterface> f1 = std::make_shared<F1>(f, seed);

  auto de1 = DE(OptSettings(2, Param::NP, Param::EVAL, seed));
  auto p1 = de1.optimize(f1);

  p1.output();
  return std::pair<double, double>{p1.x[0], p1.x[1]};
}

auto run(std::string file, const std::shared_ptr<FunctionInterface>& f,
         double CR, double F) {
  auto seed = std::random_device()();
  std::mt19937 mt(seed);
  constexpr int loop = 1;
  for (int i = 0; i < loop; ++i) {
    auto de = DE(OptSettings(2, Param::NP, Param::EVAL, mt()), CR, F);
    auto p = de.optimize(f, false, file + std::to_string(i));
    p.output();
  }
}

int main() {
  int seed = 112358;
  std::string func_name = "Schwefel";
  auto func = selectFunction(func_name);

  // {
  //   std::cerr << "[DE] start F2" << std::endl;
  //   auto [CR, F] = run_f2(func, seed);
  //   run(func_name + "/f2/result", func, CR, F);
  // }
  // {
  //   std::cerr << "[DE] start F1" << std::endl;
  //   auto [CR, F] = run_f1(func, seed);
  //   run(func_name + "/f1/result", func, CR, F);
  // }
  {
    std::cerr << "[DE] start F0" << std::endl;
    run(func_name + "f0/result", func, 0.5, 0.5);
  }
}

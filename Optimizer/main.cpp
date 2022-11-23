#include <iostream>

#include "DE.hpp"
#include "Function.hpp"

auto output(const std::vector<double>& x, double y) {
  std::cout << "x = { ";
  for (const auto& p : x) { std::cout << p << ", "; }
  std::cout << "}" << std::endl;
  std::cout << "y = " << y << std::endl;
}

int main() {
  int seed = 112358;
  auto rosen = Rosenbrock();
  auto f1 = F1(112358);
  auto f2 = F2(112358);

  auto de22 = DE(OptSettings(2, 10, 100, seed));
  auto [x22, y22] = de22.optimize(f2);

  auto de21 = DE(OptSettings(2, 10, 100, seed), x22[0], x22[1]);
  auto [x21, y21] = de21.optimize(f1);

  auto de20 = DE(OptSettings(2, 10, 100, seed), x21[0], x21[1]);
  auto [x20, y20] = de20.optimize(rosen);

  auto de = DE(OptSettings(2, 10, 100, seed));
  auto [x, y] = de.optimize(rosen);

  output(x22, y22);
  output(x21, y21);
  output(x20, y20);
  output(x, y);
}

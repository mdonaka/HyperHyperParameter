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

  auto de1 = DE(OptSettings(2, 10, 100, seed));
  auto [x1, y1] = de1.optimize(f1);

  auto de0 = DE(OptSettings(2, 10, 100, seed), x1[0], x1[1]);
  auto [x0, y0] = de0.optimize(rosen);

  auto de = DE(OptSettings(2, 10, 100, seed));
  auto [x, y] = de.optimize(rosen);

  output(x1, y1);
  output(x0, y0);
  output(x, y);
}

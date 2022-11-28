#pragma once
#include <iostream>
#include <vector>

class Poplation {
 public:
  std::vector<double> x;
  double y;

  Poplation(const std::vector<double>& x, double y) : x(x), y(y) {}

  auto operator<(const Poplation& p) const { return y < p.y; }

  auto output() {
    std::cout << "x = {";
    for (const auto& t : x) { std::cout << t << ", "; }
    std::cout << "}" << std::endl;
    std::cout << "y = " << y << std::endl;
  }
};

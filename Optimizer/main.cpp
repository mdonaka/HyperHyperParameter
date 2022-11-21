#include <iostream>

#include "DE.hpp"
#include "Function.hpp"

int main() {
  auto settings = OptSettings(2, 10, 100, 112358);
  auto de = DE(settings);
  auto f = Rosenbrock();
  de.optimize(f);
}

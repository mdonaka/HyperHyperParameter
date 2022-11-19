#include <iostream>

#include "DE.hpp"
#include "Function.hpp"

int main() {
  auto de = DE(2);
  auto f = Rosenbrock();
  de.optimize(f);
}

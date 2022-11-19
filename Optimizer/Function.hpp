#include <vector>

class FunctionInterface {
 public:
  virtual double f(const std::vector<double>& x) const = 0;
};

class Rosenbrock : public FunctionInterface {
  static constexpr double min = -5;
  static constexpr double max = 5;

 public:
  double f(const std::vector<double>& x_) const {
    int size = x_.size();

    std::vector<double> x;
    x.reserve(size);
    for (const auto& p : x_) { x.emplace_back(p * (max - min) + min); }

    double ret = 0.0;
    for (int i = 0; i < size - 1; ++i) {
      auto a = x[i + 1] - x[i] * x[i];
      auto b = x[i] - 1;
      ret += 100 * a * a + b * b;
    }
    return ret;
  }
};


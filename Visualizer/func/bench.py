"""
Thanks to https://qiita.com/nabenabe0928/items/08ed6495853c3dd08f1e.
"""

import numpy as np


class rosenbrock():
    def __init__(self):
        print("this is Rosenbrock function.")
        self.boundaries = np.array([-5, 5])
        print("boundary is {}".format(self.boundaries))
        print("minimum is {}".format(0))

    def f(self, x):
        val = 0
        for i in range(0, len(x) - 1):
            t1 = 100 * (x[i + 1] - x[i] ** 2) ** 2
            t2 = (x[i] - 1) ** 2
            val += t1 + t2
        return val


class rastrigin():
    def __init__(self):
        print("this is Rastrigin function")
        self.boundaries = np.array([-5.12, 5.12])
        print("boundary is {}".format(self.boundaries))
        print("minimum is {}".format(0))

    def f(self, x):
        t1 = 10 * len(x)
        t2 = np.sum(x ** 2)
        t3 = - 10 * np.sum(np.cos(2 * np.pi * x))
        return t1 + t2 + t3


class schwefel():
    def __init__(self):
        print("this is Schwefel function")
        self.boundaries = np.array([-500, 500])
        print("boundary is {}".format(self.boundaries))
        print("minimum is {} times n_dim".format(-418.9829))

    def f(self, x):
        return - np.sum(x * np.sin(np.sqrt(np.abs(x))))

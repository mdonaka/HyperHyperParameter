"""
Thanks to https://qiita.com/nabenabe0928/items/08ed6495853c3dd08f1e.
"""

from dataclasses import dataclass, field
from typing import ClassVar

import numpy as np


@dataclass(frozen=True)
class Rosenbrock():
    lower: float = field(default=-5, init=False)
    upper: float = field(default=5, init=False)

    def __post_init__(self):
        print("this is Rosenbrock function.")
        print("minimum is {}".format(0))

    def f(self, x):
        val = 0
        for i in range(0, len(x) - 1):
            t1 = 100 * (x[i + 1] - x[i] ** 2) ** 2
            t2 = (x[i] - 1) ** 2
            val += t1 + t2
        return val


@dataclass(frozen=True)
class Rastrigin():
    lower: float = field(default=-5.12, init=False)
    upper: float = field(default=5.12, init=False)

    def __init__(self):
        print("this is Rastrigin function")
        print("minimum is {}".format(0))

    def f(self, x):
        t1 = 10 * len(x)
        t2 = np.sum(x ** 2)
        t3 = - 10 * np.sum(np.cos(2 * np.pi * x))
        return t1 + t2 + t3


@dataclass(frozen=True)
class Schwefel():
    lower: float = field(default=-500, init=False)
    upper: float = field(default=500, init=False)

    def __init__(self):
        print("this is Schwefel function")
        print("minimum is {} times n_dim".format(-418.9829))

    def f(self, x):
        val = -np.sum(x * np.sin(np.sqrt(np.abs(x))))
        return val

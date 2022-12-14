import csv
from dataclasses import dataclass
from typing import Final

import matplotlib.pyplot as plt
import numpy as np

trial: Final = 5


def read_data(file):
    with open(file, "r") as f:
        reader = csv.reader(f)
        y = np.array([float(t[0]) for t in reader])
        return y


@dataclass(frozen=True)
class Data:
    file: str
    label: str
    c: str


def plot_data(data: list[Data]):
    loop = 100
    for d in data:
        y: np.ndarray = None
        for num in range(loop):
            y_ = read_data(d.file+str(num))
            if y is None:
                y = y_
            else:
                y += y_
        y /= loop
        x = np.array([t+1 for t in range(len(y))])
        plt.plot(x, y, label=d.label, c=d.c)


if __name__ == '__main__':
    # Rastrigin, Rosenbrock, Schwefel
    func_dir = "Schwefel"
    data = [
        Data(f"../Result/{func_dir}/f0/result", "f0", "r"),
        Data(f"../Result/{func_dir}/f1/result", "f1", "g"),
        Data(f"../Result/{func_dir}/f2/result", "f2", "b"),
    ]

    plot_data(data)

    plt.yscale('log')
    plt.legend()
    plt.grid()
    plt.show()

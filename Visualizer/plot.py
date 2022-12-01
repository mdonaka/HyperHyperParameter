import csv
from dataclasses import dataclass

import matplotlib.pyplot as plt


def read_data(file):
    with open(file, "r") as f:
        reader = csv.reader(f)
        y = [float(t[0]) for t in reader]
        x = [t+1 for t in range(len(y))]
        return x, y


@dataclass(frozen=True)
class Data:
    file: str
    label: str
    c: str


def plot_data(data: list[Data]):
    for d in data:
        x, y = read_data(d.file)
        plt.plot(x, y, label=d.label, c=d.c)


if __name__ == '__main__':
    data = [
        Data("../Result/f0", "hoge", "b"),
        Data("../Result/f0", "hoge", "r"),
    ]

    plot_data(data)

    plt.yscale('log')
    plt.legend()
    plt.grid()
    plt.show()

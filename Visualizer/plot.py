import csv

import matplotlib.pyplot as plt


def read_data(file):
    with open(file, "r") as f:
        reader = csv.reader(f)
        y = [float(t[0]) for t in reader]
        x = [t+1 for t in range(len(y))]
        return x, y


if __name__ == '__main__':
    x, y = read_data("../Result/f0")
    plt.yscale('log')
    plt.plot(x, y, label="hoge", c="b")
    plt.plot(x, y, label="huga", c="r")
    plt.legend()
    plt.grid()
    plt.show()

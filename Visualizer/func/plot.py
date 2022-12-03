import matplotlib.pyplot as plt
import numpy as np
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

import bench


def plot(func):
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')

    data = np.linspace(func.lower, func.upper, 100)
    x, y = np.meshgrid(data, data)
    z = np.array([[func.f(np.array([p, q]))
                   for p, q in zip(a, b)]
                 for a, b in zip(x, y)])
    # ax.scatter(x, y, z, s=1, c="red")
    ax.plot_surface(x, y, z, cmap=cm.hsv)
    plt.show()


if __name__ == '__main__':
    # plot(bench.Rosenbrock())
    # plot(bench.Rastrigin())
    plot(bench.Schwefel())
    # plt.show()

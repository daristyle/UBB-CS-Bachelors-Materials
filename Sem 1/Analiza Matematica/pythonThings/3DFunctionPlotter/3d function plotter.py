import matplotlib.pyplot as plt
import numpy as np
from fontTools.misc.bezierTools import epsilon
from pyparsing import alphas


class PlanePoint:
    def __init__(self, x, y, z, color):
        self.x = x
        self.y = y
        self.z = z
        self.color = color


def plot_everything(lambda1: float, lambda2: float, points: list[PlanePoint], label: str) -> None:
    x = np.linspace(-2, 2, 100)
    y = np.linspace(-2, 2, 100)
    X, Y = np.meshgrid(x, y)

    Z = (lambda1 * X * X + lambda2 * Y * Y) / 2

    fig = plt.figure(figsize=(8, 8))
    ax = fig.add_subplot(projection='3d')

    ax.plot_surface(X, Y, Z, cmap='plasma', alpha=0.8, zorder=2)

    mn = np.min(Z)
    mx = np.max(Z)

    ax.contour(X, Y, Z, zdir='z', offset=mn, cmap='plasma', zorder=0)

    for point in points:
        point.z = ((lambda1 * point.x * point.x + lambda2 * point.y * point.y) / 2)

        Z = lambda1 * point.x * X + lambda2 * point.y * Y - point.z
        Z[Z + 0.001 < mn] = np.nan
        Z[Z - 0.001 > mx] = np.nan

        ax.plot_surface(X, Y, Z, color=point.color, alpha=0.6, zorder=1)
        ax.plot([point.x], [point.y], [point.z], c='white', marker='o', markeredgecolor='white', markersize=8, markeredgewidth=2, zorder=3, alpha=1)


    ax.set_zlim(mn, mx)
    ax.set_title(label, fontsize= 20)

    plt.savefig(label + "_plot.png")
    plt.show()



points = [PlanePoint(-1, 1, 0, 'red'), PlanePoint(1, 1, 0, 'green'), PlanePoint(-1, -1, 0, 'blue')]

for [lambda1, lambda2, label] in [[1, 1, "Minimum point"], [-1, -1, "Maximum point"], [1, -1, "Saddle point"]]:
    plot_everything(lambda1, lambda2, points, label)
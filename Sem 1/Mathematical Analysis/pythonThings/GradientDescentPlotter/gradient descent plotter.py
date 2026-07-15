"""
Remarks:
 - the smaller be is the slower the sequence converges to the minimum
"""

import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np


def gradient_descent_plot(x:float, y:float, b:float, points:int) -> None:
    x_new, y_new = x, y
    x_coords = []
    y_coords = []

    for _ in range(points):
        x, y = x_new, y_new
        x_coords.append(x)
        y_coords.append(y)

        if (x, y) == (0, 0):
            break

        s = (x ** 2 + b * y ** 2)/(x ** 2 + (b ** 2) * (y ** 2))
        x_new = (1 - s) * x
        y_new = (1 - b * s) * y
    while(len(x_coords) < points):
        x_coords.append(0)
        y_coords.append(0)

    ax = plt.subplot()

    ax.scatter(x_coords, y_coords, color='red')

    for i in range(1, points):
        ax.plot(x_coords[i - 1:i + 1], y_coords[i - 1:i + 1], color='red', linestyle='--')

    for i in range(points):
        r = (x_coords[i]**2 + y_coords[i]**2)**0.5

        if r < 0.1:
            continue

        circle = patches.Circle((0, 0), radius=r, facecolor='none', edgecolor='blue', zorder=1)
        ax.add_patch(circle)

        theta = np.arctan(y_coords[i]/x_coords[i])
        x = r * np.cos(theta + np.pi/ 2)
        y = r * np.sin(theta + np.pi / 2)

        ax.text(x, y, f'{r:.2f}', color='black', fontsize=8, fontweight='bold')
    ax.set_aspect('equal')

    plt.savefig("gradient_descent_plot_for_b_" + str(b) + "_with_" + str(points) + "_points.png")
    plt.show()


for b in [1, .5, .2, .1]:
    for points in [3, 4, 5, 6, 7]:
        gradient_descent_plot(3, 1, b, points)
import matplotlib.pyplot as plt
import numpy as np


def get_random_point_in_unit_ball(p:float) -> tuple:
    x = np.random.uniform(-1,1)
    m = (1 - abs(x) ** p) ** (1/p)
    y = np.random.uniform(-m,m)

    return x,y

def plot_unit_ball(n: int, p:float):
    x_coords = []
    y_coords = []
    for _ in range(n):
        x, y = get_random_point_in_unit_ball(p)
        x_coords.append(x)
        y_coords.append(y)


    plt.scatter(x_coords, y_coords)
    plt.grid(True)
    plt.minorticks_on()
    plt.grid(which='major', linestyle='-', linewidth='0.5', color='black')
    plt.grid(which='minor', linestyle=':', linewidth='0.5', color='gray')

    plt.savefig("unit_ball_plot_" + str(n) + "_points_" + str(p) + "_norm.png")
    plt.show()


for p in [1.25, 1.5, 3, 8]:
    for n in [10, 10 ** 2, 10 ** 3, 10 ** 4, 10 ** 5]:
        plot_unit_ball(n, p)
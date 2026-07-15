"""
Remarks:
    - the gradient value affects the speed at which the sequence converges(I capped  it at 1 million iterations)
    - the values may overflow even in Python and are not exact(some gradients a little bigger would increase the duration
    of the program by a huge factor due to the large number of operations happening on BigInt)
    - different starting position may give different values of convergence for the sequence in the case of nonconvex functions
    - in the case of convex functions the intial position only affects the speed at which the convergence value will be approched
    - the results would have looked prettier in a table, but that would increase the waiting time of the program to run
    and the current format is more ore less a table with extra words
"""
import math
import sys

sys.set_int_max_str_digits(1_000_000)

def gradient_descent_method(niu: float, x: float, f, fd, fstr: str) -> None:
    cpy = x
    x_new = x
    x = x - 1
    n = 0
    while x_new != x and n < 1e6:
        x = x_new
        x_new = x - niu * fd(x)
        n += 1

    print("The sequence converges to ", x, "and the value of the function ", fstr," in this point is ", f(x), ". This was achived "
          "in ", n, "steps, starting from ", cpy, " with a gradient of ", niu)

def f1(x: float) -> float:
    return x ** 2
def f1d(x: float) -> float:
    return 2 * x

def f2(x: float) -> float:
    return math.exp(x)

def f3(x: float) -> float:
    if x == float("-inf") or x == float("inf"):
        return x
    return x ** 3 - 3 * x
def f3d(x: float) -> float:
    return 3 * x ** 2 - 3


for (f, fd, str) in [(f1, f1d, "x^2"), (f2, f2, "e^x")]:
    for i in [0.001, 0.01, 0.1, 0.5, 0.75, 0.99, 1, 1.5]:
        for pos in [-10, -5, -1, 0, 1, 5, 10]:
            gradient_descent_method(i, pos, f, fd, str)
for pos in [-10, -5, -1, 0, 1, 5, 10]:
    gradient_descent_method(10000, pos, f2, f2, "e^x")
for i in [0.001, 0.01, 0.1, 0.5]:
    for pos in [-1, 0, 1, 2]:
        gradient_descent_method(i, pos, f3, f3d, "x^3 - 3 * x")#nonconvex
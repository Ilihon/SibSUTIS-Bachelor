import numpy as np
from scipy.integrate import quad as itg


def fun(x):
    return 1 / x


def orig(l, r):
    return itg(fun, l, r)[0]


def Trapez(xs, xe, h):
    x = np.arange(xs, xe + h, h)
    y = [fun(i) for i in x]
    result = 0
    for i in range(1, len(x)):
        result += h * ((y[i] + y[i - 1]) / 2)
    return result


def Simpson(xs, xe, h):
    x = np.arange(xs, xe + h, h)
    y = [fun(i) for i in x]
    result = 0
    for i in range(2, len(x), 2):
        result += (2 * h) * ((y[i] + y[i - 2]) / 6 + y[i - 1] * (2 / 3))
    return result

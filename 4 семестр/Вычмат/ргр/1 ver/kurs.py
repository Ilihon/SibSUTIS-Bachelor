import math
import numpy as np


def f(x, y, z):
    F = [0.0, 0.0]
    F[0] = z
    F[1] = (math.exp(x) + y + z) / 3
    return F


def Runge_Kutta(a, b, h, y, z, flag):
    n = round((b - a) / h) + 1
    X = [a + i * h for i in range(n)]
    Y = [y, z]
    if flag:
        print("%.4f, %.10f, %.10f" % (X[0], Y[0], Y[1]))
    for i in range(1, n, 1):
        K1 = f(X[i-1], Y[0], Y[1])
        K2 = f(X[i-1] + h / 2, Y[0] + h / 2 * K1[0], Y[1] + h / 2 * K1[1])
        K3 = f(X[i-1] + h / 2, Y[0] + h / 2 * K2[0], Y[1] + h / 2 * K2[1])
        K4 = f(X[i-1] + h, Y[0] + h * K3[0], Y[1] + h * K3[1])
        Y[0] = Y[0] + h / 6 * (K1[0] + 2 * K2[0] + 2 * K3[0] + K4[0])
        Y[1] = Y[1] + h / 6 * (K1[1] + 2 * K2[1] + 2 * K3[1] + K4[1])

        if flag:
            print("%.4f, %.10f, %.10f" % (X[i], Y[0], Y[1]))
    F = np.zeros(2)
    F[0] = Y[0]
    F[1] = Y[1]
    return F


def prist(eps, h, a, b, y0, y1):
    angle = [(y1-y0)/(b - a), (y1-y0)/(b - a)]
    # angle = [1, 1]
    exp = Runge_Kutta(a, b, h, y0, angle[0], 0)
    if exp[0] < y1:
        while exp[0] < y1:
            angle[1] += 1
            exp = Runge_Kutta(a, b, h, y0, angle[1], 0)
    elif exp[0] > y1:
        while exp[0] > y1:
            angle[1] -= 1
            exp = Runge_Kutta(a, b, h, y0, angle[1], 0)
    if angle[0] > angle[1]:
        angle[0], angle[1] = angle[1], angle[0]

    left = angle[0]
    right = angle[1]
    midle = (left + right) / 2
    exp = Runge_Kutta(a, b, h, y0, midle, 0)

    while abs(exp[0] - y1) > eps:
        if exp[0] < y1:
            left = midle
        elif exp[0] > y1:
            right = midle
        midle = (left + right) / 2
        exp = Runge_Kutta(a, b, h, y0, midle, 0)
    return midle


def dv_peresch(eps, h, a, b, y0, y1):
    Y1 = Runge_Kutta(a, b, h, y0, y1, 0)
    Y2 = Runge_Kutta(a, b, h / 2, y0, y1, 0)
    if abs(Y1[0] - Y2[0]) < eps:
        return h
    while abs(Y1[0] - Y2[0]) > eps:
        h /= 2
        Y1 = Y2
        Y2 = Runge_Kutta(a, b, h / 2, y0, y1, 0)
    print('-' * 20)
    print('h = ', h / 2)
    return h / 2


e = 0.0000001
h = 0.1
a = 0
b = 1
y0 = 1
y1 = 2.718281828

angle = prist(e, h, a, b, y0, y1)
h_new = dv_peresch(e, h, a, b, y0, angle)
angle = prist(e, h_new, a, b, y0, y1)
Y = Runge_Kutta(a, b, h_new, y0, angle, 1)

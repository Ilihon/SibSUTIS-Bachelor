import sympy as sym
from sympy import lambdify
import matplotlib.pyplot as plt
import numpy as np
from numpy import linspace
import math
from functions import *


def main():
    orig_func = 'x ** 2'
    func = 'a+b*x+c*(sqrt(x))'
    g = ['1', 'x', '(sqrt(x))']
    X = np.arange(0, 3.1, 1)  # набор Х
    # x = sym.symbols('x')
    a, b, c, d, e, f, x = sym.symbols('a b c d e f x')  # обозначаем символы
    symb_turp = (a, b, c, d, e, f)  # кортеж коэфицентов
    Y_podstav = lambdify(x, sym.S(orig_func), "numpy")  # подставляем набор X в оригинальную функцию
    Y = [Y_podstav(n) for n in X]  # набор Y
    print('X = ', X)
    print('Y = ', Y)
    koefs = CountSum(x, g, X, Y)
    print('Коэффиценты = ', koefs)

    Aprox_podstav = lambdify([x] + [symb_turp[n] for n in range(len(g))], sym.S(func), "numpy")
    y_nodes = [Aprox_podstav(n, koefs[0], koefs[1], koefs[2]) for n in X]
    print('Y апроксимации = ', y_nodes)

    x_graph = linspace(0, 4, num=100, dtype='float')
    y_graph_orig = [Y_podstav(n) for n in x_graph]
    plt.plot(X, Y, 'ro')
    plt.plot(x_graph, y_graph_orig, '-r', label='Оригинальная функция')

    y_graph = [Aprox_podstav(n, koefs[0], koefs[1], koefs[2]) for n in x_graph]
    plt.plot(X, y_nodes, 'bo')
    plt.plot(x_graph, y_graph, '-b', label='Апроксимация')

    plt.title(func)
    plt.grid(True)
    # plt.get_current_fig_manager().full_screen_toggle()
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()

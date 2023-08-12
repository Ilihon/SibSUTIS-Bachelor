from matplotlib import pyplot as plt
from numpy import linspace
import numpy as np

import functions


def fun(x: float):
    return x ** 2


def main():
    start_x_arr = np.arange(-4, 4.1, 1)
    start_x_arr = [complex(n, 0) for n in start_x_arr]
    start_y_arr = [fun(n) for n in start_x_arr]

    start_x_graph = linspace(-4, 4, num=100, dtype='float')
    start_y_graph = [fun(n) for n in start_x_graph]

    x_nodes = [-3, -2, -1, 0, 1, 2, 3]
    y_nodes = [functions.interpolate_trigonometry(start_x_arr, start_y_arr, n) for n in x_nodes]
    # y_nodes_real = [n.real for n in y_nodes]
    y_nodes_imag = [n.imag for n in y_nodes]

    x_graph = linspace(-4, 4, num=100, dtype='float')
    y_graph = [functions.interpolate_trigonometry(x_nodes, y_nodes, n) for n in x_graph]
    y_graph_real = [n.real for n in y_graph]
    y_graph_imag = [n.imag for n in y_graph]

    """ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ """

    plt.plot(start_x_graph, start_y_graph, '-r', label='Оригинальная функция')

    plt.plot(x_nodes, y_nodes_imag, 'go')
    plt.plot(x_graph, y_graph_imag, '--g', label='Интерполяция мнимая')

    plt.plot(x_nodes, y_nodes, 'bo')
    plt.plot(x_graph, y_graph_real, '-b', label='Интерполяция действительная')

    plt.title('f(x) = x^2')
    plt.grid(True)
    # plt.get_current_fig_manager().full_screen_toggle()
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()

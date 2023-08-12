from sympy import sin, cos
import matplotlib.pyplot as plt
from numpy import linspace
from decimal import Decimal as d
import functions


def main():
    start_x_left, start_x_right, start_step = (-5, 5, 1)
    start_x_arr = [d(n) for n in functions.drange(start_x_left, start_x_right + start_step, start_step)]
    start_y_arr = [cos(n) for n in start_x_arr]
    start_x_graph = [d(n) for n in functions.drange(start_x_left, start_x_right + 0.1, 0.1)]
    start_y_graph = [cos(n) for n in start_x_graph]

    x_nodes = [d(n) for n in (-4, -3, -2, -1, 0, 1, 2, 3, 4)]
    y_nodes = [functions.Cube_Spline(start_x_arr, start_y_arr, n) for n in x_nodes]

    x_graph = linspace(-4, 4, num=200, dtype='float')
    y_graph = [functions.Cube_Spline(x_nodes, y_nodes, d(n)) for n in x_graph]

    """ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ """

    fig = plt.figure()
    # ax = fig.add_subplot(1, 1, 1)
    # Move left y-axis and bottom x-axis to centre, passing through (0,0)
    # ax.spines['left'].set_position('center')
    # ax.spines['bottom'].set_position('center')

    # Eliminate upper and right axes
    # ax.spines['right'].set_color('none')
    # ax.spines['top'].set_color('none')

    # Show ticks in the left and lower axes only
    # ax.xaxis.set_ticks_position('bottom')
    # ax.yaxis.set_ticks_position('left')

    plt.plot(start_x_graph, start_y_graph, '-r', label='Оригинальная функция')

    plt.plot(x_nodes, y_nodes, 'bo')
    plt.plot(x_graph, y_graph, '-b', label='Интерполяция')
    plt.title('f(x) = cos(x)')

    plt.grid(True)
    # plt.get_current_fig_manager().full_screen_toggle()
    plt.legend()
    plt.show()


if __name__ == '__main__':
    main()

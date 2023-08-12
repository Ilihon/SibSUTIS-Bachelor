from numpy.linalg import solve as gauss_method
from numpy import array
from decimal import Decimal as d


def drange(start, stop, step):
    start = d(start.__str__())
    stop = d(stop.__str__())
    step = d(step.__str__())

    values = []

    if start <= stop and step > 0:
        values.append(start)
        while start + step < stop:
            start += step
            values.append(start)
    elif start >= stop and step < 0:
        values.append(start)
        while start + step > stop:
            start += stop
            values.append(start)
    else:
        raise ValueError('Wrong sequence')

    return values


def Cube_Spline(x_arr, y_arr, x):
    if len(x_arr) != len(y_arr):
        return RuntimeError('Некорретные списки точек. Размер списков не равен')
    if len(x_arr) > 2:
        n = len(x_arr) - 1
    else:
        raise NotImplementedError('Невозможно посчитать на менее чем 3 точках')
    h_arr = [x_arr[i] - x_arr[i - 1] for i in range(1, n + 1)]
    cm_matrix = array(count_cm_matrix(h_arr), dtype='float')
    d_vector = array(count_d_vector(h_arr, y_arr), dtype='float')
    cmd_vector = [[d(num) for num in row] for row in gauss_method(cm_matrix, d_vector)]
    cmd_vector.insert(0, [d(0)])
    cmd_vector.append([d(0)])
    result = count_result(x_arr, y_arr, cmd_vector, h_arr, x)
    return result


def count_cm_matrix(h_arr):
    size = len(h_arr) - 1
    c_matrix = [[[] for _ in range(size)] for _ in range(size)]  # создание квадратной матрицы size X size
    for i in range(size):
        for j in range(size):
            if i == j:
                c_matrix[i][j] = (h_arr[i] + h_arr[i + 1]) / 3
            elif j == i + 1:
                c_matrix[i][j] = (h_arr[i + 1]) / 6
            elif j == i - 1:
                c_matrix[i][j] = h_arr[i] / 6
            else:
                c_matrix[i][j] = 0
    return c_matrix


def count_d_vector(h_arr, y_arr):
    size = len(h_arr) - 1
    d_vector = [[] for _ in range(size)]
    for i in range(1, size + 1):
        d_vector[i - 1].append(((y_arr[i + 1] - y_arr[i]) / h_arr[i]) - ((y_arr[i] - y_arr[i - 1]) / h_arr[i - 1]))
    return d_vector


def count_result(x_arr, y_arr, M, h, x):
    i = None
    for j in range(len(x_arr) - 1):
        if x_arr[j] <= x <= x_arr[j + 1]:
            i = int(j + 1)
            break
    if i is None:
        raise RuntimeError('x должен быть внутри диапазона')
    m1 = M[i - 1][0] * ((x_arr[i] - x) ** 3 / (6 * h[i - 1]))
    m2 = M[i][0] * ((x - x_arr[i - 1]) ** 3 / (6 * h[i - 1]))
    m3 = (y_arr[i - 1] - (M[i - 1][0] * h[i - 1] ** 2) / 6) * ((x_arr[i] - x) / h[i - 1])
    m4 = (y_arr[i] - (M[i][0] * (h[i - 1] ** 2)) / 6) * ((x - x_arr[i - 1]) / h[i - 1])
    return m1 + m2 + m3 + m4

import cmath
from typing import List


def interpolate_trigonometry(x_arr: List[complex or float], y_arr: List[complex or float], x: float) -> complex:
    if len(x_arr) != len(y_arr):
        raise RuntimeError('Входные точки не корректны. Списки координат не равны')
    n = len(x_arr)
    h = x_arr[1] - x_arr[0]
    j_range = range(-n // 2 + 1, n // 2 + 1)
    a_arr = []
    for j in j_range:
        a_arr.append(count_a(y_arr, n, j))
    result = 0 + 0j
    i = 1j
    index = 0
    for j in j_range:
        result += a_arr[index] * cmath.exp(2 * cmath.pi * i * j * ((x - x_arr[0]) / (n * h)))
        index += 1
    return result / n


def count_a(y_arr: List[float], n: int, j: int):
    i = 1j
    result = 0
    for k in range(n):
        result += y_arr[k] * cmath.exp(-2 * cmath.pi * i * (k * j / n))
    return result

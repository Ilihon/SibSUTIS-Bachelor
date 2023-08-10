#!/usr/bin/env python3

import random

import numpy as np

OPERATIONS = 0


def generate_random_matrix(rows, cols, lower_border=0, upper_border=10):
    return np.array([[random.randint(lower_border, upper_border) for _ in range(cols)] for _ in range(rows)])


def generate_zeroed_matrix(rows, cols):
    return np.array([[0 for _ in range(cols)] for _ in range(rows)])


def generate_increment_matrix(rows, cols):
    return np.array([[i * cols + j + 1 for j in range(cols)] for i in range(rows)])


def generate_first_matrix(rows, cols):
    return np.array([[(-1) ** (i + j) for j in range(cols)] for i in range(rows)])


def generate_second_matrix(rows, cols):
    return np.array([[i - j for j in range(cols)] for i in range(rows)])


def multiply_matrix_default(a, b):
    global OPERATIONS
    c = generate_zeroed_matrix(len(a), len(b[0]))
    for i in range(len(a)):
        for j in range(len(b[0])):
            for k in range(len(b)):
                OPERATIONS += 1
                c[i][j] += a[i][k] * b[k][j]
    return c


def multiply_matrix_fast(a, b):
    rows = len(a)
    cols = len(b[0])

    if rows % 2 == 1 and cols % 2 == 1:
        return multiply_matrix_default(a, b)
    else:
        a1 = a[:rows // 2, :cols // 2]
        a2 = a[:rows // 2, cols // 2:]
        a3 = a[rows // 2:, :cols // 2]
        a4 = a[rows // 2:, cols // 2:]

        b1 = b[:rows // 2, :cols // 2]
        b2 = b[:rows // 2, cols // 2:]
        b3 = b[rows // 2:, :cols // 2]
        b4 = b[rows // 2:, cols // 2:]

        m1 = multiply_matrix_fast(a2 - a4, b3 + b4)
        m2 = multiply_matrix_fast(a1 + a4, b1 + b4)
        m3 = multiply_matrix_fast(a1 - a3, b1 + b2)
        m4 = multiply_matrix_fast(a1 + a2, b4)
        m5 = multiply_matrix_fast(a1, b2 - b4)
        m6 = multiply_matrix_fast(a4, b3 - b1)
        m7 = multiply_matrix_fast(a3 + a4, b1)
        c1 = m1 + m2 - m4 + m6
        c2 = m4 + m5
        c3 = m6 + m7
        c4 = m2 - m3 + m5 - m7

    return np.bmat([[c1, c2], [c3, c4]])


size = 100
a = generate_first_matrix(size, size)
b = generate_second_matrix(size, size)

print(a)
print()
print(b)
print()

OPERATIONS = 0
result_default = multiply_matrix_default(a, b)
print('Operations:', OPERATIONS)
print(result_default)
print()

OPERATIONS = 0
result_fast = multiply_matrix_fast(a, b)
print('Operations:', OPERATIONS)
print(result_fast)
print()

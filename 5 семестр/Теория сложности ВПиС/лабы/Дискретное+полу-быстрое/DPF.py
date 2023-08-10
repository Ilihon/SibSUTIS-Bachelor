import cmath
import numpy as np
import math


def D_Fourier(numb, f):
    mas_A = []
    i = complex(0, 1)
    for k in range(numb):
        a = complex(0, 0)
        for j in range(len(f)):
            a += f[j] * cmath.exp((-2) * math.pi * i * k * j / numb)
        mas_A.append(a / numb)
    return mas_A


def D_Fourier_reverse(numb, a):
    mas_f = []
    i = complex(0, 1)
    for k in range(numb):
        f = complex(0, 0)
        for j in range(len(a)):
            f += a[j] * cmath.exp(2 * math.pi * i * k * j / numb)
        mas_f.append(f)
    return mas_f


def PP_Fourier(numb, f):
    p1 = 1
    p2 = numb
    for i in np.arange(1, math.sqrt(numb) + 1, 1):
        # print(i)
        if (numb % i == 0) and ((numb / i - i) < (numb - 1)):
            p1 = int(i)
            p2 = int(numb / p1)
    print(p1, p2)
    a = [0 + 0j] * numb
    i = complex(0, 1)
    for k1 in range(p1):
        for j2 in range(p2):
            for j1 in range(p1):
                a[k1 + p1 * j2] += f[j2 + p2 * j1] * cmath.exp((-2) * math.pi * i * j1 * k1 / p1)
            a[k1 + p1 * j2] /= p1
    print(a)
    result = [0 + 0j] * numb
    for k1 in range(p1):
        for k2 in range(p2):
            for j2 in range(p2):
                result[k1 + p1 * k2] += a[k1 + p1 * j2] * cmath.exp((-2) * math.pi * i * j2 / numb * (k1 + p1 * k2))
            result[k1 + p1 * k2] /= p2
    print(result)
    return result


def print_massive(massive):
    for i in range(len(massive)):
        print(round(massive[i].real, 4), round(massive[i].imag, 4), "* i")


massive = []
copy_massive = massive
print("Введите количество элементов:")
n = int(input())
print("Вводите числа:")
for i in range(n):
    massive.append(int(input()))

t = len(massive) ** 2 * 5

mas_dpf = D_Fourier(len(massive), massive)
mas_rev = D_Fourier_reverse(len(mas_dpf), mas_dpf)
mas_ppf = PP_Fourier(len(massive), massive)
print("Дискретное преобразование Фурье:")
print_massive(mas_dpf)
print("Обратное преобразование:")
print_massive(mas_rev)
print("Полубыстрое преобразование Фурье:")
print_massive(mas_ppf)

print("Трудоемкость ДПФ:", t)

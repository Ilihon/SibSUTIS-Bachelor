import sympy as sym
from sympy import lambdify
import matplotlib.pyplot as plt
import numpy as np
import functions

def main():
    func = 'sqrt(x)'
    XY = ((1, 1), (2, 1.4142), (3,1.7321), (4, 2))
    XY_new = ((1, 1), (1.35, 1.1618), (1.70, 1.3038), (2, 1.4142))
    n = len(XY)-1  # количество точек для интерполяции
    n_new = len(XY_new)-1
    xn = 1.69
    pogresh = 10 ** (-3)  # точность погрешности
    h = 1

    dots = np.arange(1, 3.1,2)
    dots2 = np.arange(0, 4.1,4)

    t1 = np.arange(0, 3, 0.001)
    t2 = np.arange(0, 3, 0.001)
    # print(t1)
    # print(dots)
    x = sym.Symbol('x')
    func_orig = lambdify(x, sym.S(func))
    print(func_orig(n))
    proizv = sym.diff(func, x, n + 1)
    gp = lambdify(x, proizv)
    proizv_podstav = proizv.subs(x, xn)
    print(f"Производная {n + 1} степени = {proizv}")
    print(f"Подставим {xn} = {gp(xn)}")
    # print(gp(xn))

    print(f'P{n}({xn}) Лангранж = {functions.Langraj(XY, xn, n)}')
    print(f'P{n}({xn}) Эйткен = {functions.Eitken(XY, xn, 0, n)}')
    print(f'P{n}({xn}) Первая формула Ньютона = {functions.Newton1(XY, xn, n, h)}')
    print(f'P{n}({xn}) Вторая формула Ньютона = {functions.Newton2(XY, xn, n, h)}')
    functions.Ereal(XY, xn, n, pogresh, proizv_podstav)
    itog =functions.Langraj(XY, dots, n)
    print(itog)

    try:
        plt.figure()
        plt.subplot(221)
        plt.plot(t2, func_orig(t2), 'r-')
        plt.title('Оригинальная функция')
        plt.grid(True)

        plt.subplot(222)
        plt.plot(t2, func_orig(t2), 'r-')
        plt.plot(t1, functions.Langraj(XY, t1, n), 'm-')
        # plt.plot(t1, functions.Langraj(XY_new, t1, n_new), 'b-')
        # plt.plot(dots, functions.Langraj(XY, dots, n), 'yo-')

        coefficients = np.polyfit([1,2,3], [1, 1.4142, 1.7321], 1)
        polynomial = np.poly1d(coefficients)
        x_axis = np.linspace(0, 5)
        y_axis = polynomial(x_axis)
        # plt.plot(x_axis, y_axis, linestyle='dashed')
        plt.plot(1, 1, 1.35, 1.1618, 1.70, 1.3038, 2, 1.4142, marker='o', color='red')

        plt.title('Формула Лангранжа')
        plt.grid(True)

        plt.subplot(223)
        plt.plot(t2, func_orig(t2), 'r-')
        # plt.plot(t1, functions.Eitken(XY, t1, 0, n), 'm-')
        plt.plot(t1, functions.Eitken(XY_new, t1, 0, n_new), 'b-')
        # plt.plot(dots, functions.Eitken(XY, dots, 0, n), 'yo-')

        # coefficients = np.polyfit([1,3], [1, 1.7321], 1)
        # polynomial = np.poly1d(coefficients)
        # x_axis = np.linspace(0, 5)
        # y_axis = polynomial(x_axis)
        # plt.plot(x_axis, y_axis, linestyle='dashed')
        plt.plot(1, 1, 1.35, 1.1618, 1.70, 1.3038, 2, 1.4142, marker='o', color='red')

        plt.title('Схема Эйткена')
        plt.grid(True)

        plt.subplot(224)
        plt.plot(t2, func_orig(t2), 'r-')
        # plt.plot(t1, functions.Newton1(XY, t1, n, h), 'm-')
        # plt.plot(t1, functions.Newton2(XY, t1, n, h), 'm-')
        plt.plot(t1, functions.Newton1(XY, t1, n_new, h), 'g-')
        plt.plot(t1, functions.Newton2(XY, t1, n_new, h), 'b-')
        # plt.plot(t1, functions.Eitken(XY_new, t1, 0, n_new), 'b-')
        # plt.plot(dots, functions.Newton1(XY, dots, n, h), 'yo-')

        # coefficients = np.polyfit([1,3], [1, 1.7321], 1)
        # polynomial = np.poly1d(coefficients)
        # x_axis = np.linspace(0, 5)
        # y_axis = polynomial(x_axis)
        # plt.plot(x_axis, y_axis, linestyle='dashed')
        plt.plot(1, 1, 1.35, 1.1618, 1.70, 1.3038, 2, 1.4142, marker='o', color='red')

        plt.title('Методы Ньютона')
        plt.grid(True)

        plt.show()

    except:
        print("Что-то пошло не так")


if __name__ == '__main__':
    main()
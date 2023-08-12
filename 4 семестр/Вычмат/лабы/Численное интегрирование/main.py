from math import fabs
import functions


def main():
    e = 10 ** (-8)
    h = 0.1
    a, b = 1, 2
    org = functions.orig(a, b)
    rt = 0
    step = 0
    print("Формула трапеции")
    while fabs(org - rt) > e:
        step += 1
        rt = functions.Trapez(a, b, h)
        print("---------------------------")
        print("Шаг:", step)
        print("h:", h)
        print("Оригинальная функция:", org)
        print("Результат:", rt)
        h /= 2

    rs = 0
    step = 0
    h = 0.1
    print("---------------------------\n\nФомрула Симпсона")
    while fabs(org - rs) > e:
        step += 1
        rs = functions.Simpson(a, b, h)
        print("---------------------------")
        print("Шаг:", step)
        print("h:", h)
        print("Оригинальная функция:", org)
        print("Результат:", rs)
        h /= 2


if __name__ == '__main__':
    main()

import random

from math import sqrt, ceil


# проверка на простоту числа используя теореме Ферма
def check_prime(p):
    if p <= 1:
        return False
    elif p == 2:
        return True
    a = random.randint(2, p - 1)
    # print(p, "-", a)
    if pow_module(a, (p - 1), p) != 1 or gcd(p, a) > 1:
        return False
    return True


# генерируем простое число в указанных границах
def generate_prime(left, right):
    while True:
        p = random.randint(left, right)
        # print("--", p)
        if check_prime(p):
            return p


# возведение в степень по модулю
def pow_module(a, x, p):
    result = 1
    a = a % p
    if a == 0:
        return 0;
    while x > 0:
        if x & 1 == 1:  # если крайний правый бит степени равен lib
            result = (result * a) % p
        a = (a ** 2) % p
        x >>= 1  # побитово смещаем степень
    return result


# Алгоритм Евклида, для нахождения наибольшего общего делителя
def gcd(a, b):
    while b != 0:
        r = a % b
        a = b
        b = r
    return a


# Обобщённый Алгоритм Евклида, для нахождения наибольшего общего делителя и двух неизвестных уравнения
def gcd_modified(a, b):
    U = (a, 1, 0)
    V = (b, 0, 1)
    while V[0] != 0:
        q = U[0] // V[0]
        T = (U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2])
        U = V
        V = T
    return U


# Система Диффи-Хеллмана
def diffie_hellman_algorithm():
    q, p, g, Xa, Xb = 0, 0, 0, 0, 0

    print("Общие параметры:")
    while True:
        q = generate_prime(0, 10 ** 9)
        p = 2 * q + 1
        if check_prime(p):
            break
    print(f"q = {q}\np = {p}")

    while pow_module(g, q, p) != 1:
        g = random.randint(2, p - 1)
    print(f"g = {g}\n")

    Xa = random.randint(1, p)  # generate_prime(lib, p)
    Xb = random.randint(1, p)  # generate_prime(lib, p)
    print(f"Закрытые ключи:\nXa = {Xa}\nXb = {Xb}\n")

    Ya = pow_module(g, Xa, p)
    Yb = pow_module(g, Xb, p)
    print(f"Открытые ключи:\nYa = {Ya}\nYb = {Yb}")

    Zab = pow_module(Yb, Xa, p)
    Zba = pow_module(Ya, Xb, p)
    print(f"Секретные ключи:\nZab = {Zab}\nZba = {Zba}\n")
    return Zab, Zba


# Шаг младенца Шаг великана
def giant_baby_step(a, p, y):
    k = m = ceil(sqrt(p))

    baby = {pow_module(a, j, p) * y % p: j for j in range(m)}
    print(baby)
    giant = [pow_module(a, (m * i), p) for i in range(1, k + 1)]
    print(giant)

    for i, element in enumerate(giant, 1):
        if (j := baby.get(element)) is not None:
            return i * m - j
    return None


if __name__ == '__main__':
    # print(pow_module(5, 20, 7))
    # print(gcd(28,19))
    print(gcd(2, 3))
    print(pow_module(4, 2, 3))
    print(generate_prime(1, 7))
    # diffie_hellman_algorithm()

    # print(giant_baby_step(88, 107, 47))

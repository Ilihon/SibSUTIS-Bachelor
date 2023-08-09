from lib.lab2 import *
import os
import shutil
import hashlib
from colorama import Fore, init


def ElGamal_sign(m) -> list:
    g = 0
    while True:
        q = generate_prime(0, 10 ** 9)
        p = 2 * q + 1
        if check_prime(p):
            break
    print("p = ", p)
    while pow_module(g, q, p) != 1:
        g = random.randint(2, p - 1)

    print("g = ", g)
    x = generate_prime(0, p - 1)
    print("x = ", x)
    y = pow_module(g, x, p)
    print("y = ", y)

    k = generate_coprime(p - 1)
    print("k = ", k)
    r = pow_module(g, k, p)
    print("r = ", r)
    keys['gamal_sign'] = {'p': p, 'g': g, 'y': y, 'r': r}

    h = hashlib.md5(m).hexdigest()
    print('Sign:')
    print(f'ElGamal md5 hash: {h}')
    # числовое представление хэш функции для проверки подлинности
    h_b = ''.join(str(pow_module(g, int(i, 16), p)) for i in h)
    print(f'Sign: ElGamal md5 hash numeric representation: {h_b}')

    u = [(int(i, 16) - x * r) % (p - 1) for i in h]
    s = [(gcd_modified(k, p - 1)[1] * i) % (p - 1) for i in u]

    return s


def ElGamal_signcheck(m: bytearray, s: list):
    p = keys["gamal_sign"]["p"]
    y = keys["gamal_sign"]["y"]
    r = keys["gamal_sign"]["r"]
    g = keys["gamal_sign"]["g"]
    # Хэш функция проверяемого сообщения
    h = hashlib.md5(m).hexdigest()
    print('Unsign:')
    print(f'ElGamal md5 hash: {h}')
    # числовое представление хэш функции для проверки подлинности
    h_b = ''.join(str(pow_module(g, int(i, 16), p)) for i in h)
    print(f'ElGamal md5 hash numeric representation: {h_b}')
    res = ''.join(str(pow_module(y, r, p) * pow_module(r, i, p) % p) for i in s)
    print(f'ElGamal authenticity check: {res}')

    print("Result of authenticity check: " + ((Fore.CYAN + 'same') if res == h_b else (Fore.RED + 'fake')) + Fore.RESET)


def RSA_sign(m) -> list:

    P = generate_prime(0, 10 ** 9)
    print("P = ", P)
    Q = generate_prime(0, 10 ** 9)
    print("Q = ", Q)
    N = P * Q
    print("N = ", N)
    Phi = (P - 1) * (Q - 1)
    print("Phi = ", Phi)

    d = generate_coprime(Phi)
    print("d = ", d)
    c = gcd_modified(d, Phi)[1]
    if c < 0:
        c += Phi
    print("c = ", c)
    keys['RSA_sign'] = {'N': N, 'd': d}  # , 'P': P, 'Q': Q, 'Phi': Phi, 'c': c}
    # Хэш функция подписанного сообщения
    h = hashlib.md5(m).hexdigest()
    print('Sign:')
    print(f'RSA md5 hash: {h}')
    # числовое представление хэш функции для проверки подлинности
    h_b = ''.join(str(int(i, 16)) for i in h)
    print(f'RSA md5 hash numeric representation: {h_b}')
    # наша подпись
    s = [pow_module(int(i, 16), c, N) for i in h]

    return s


def RSA_signcheck(m: bytearray, s: list):
    d = keys["RSA_sign"]["d"]
    N = keys["RSA_sign"]["N"]
    # Хэш функция проверяемого сообщения
    h = hashlib.md5(m).hexdigest()
    print('Unsign:')
    print(f'RSA md5 hash: {h}')
    # числовое представление хэш функции для проверки подлинности
    h_b = ''.join(str(int(i, 16)) for i in h)
    print(f'RSA md5 hash numeric representation: {h_b}')
    e = ''.join(str(pow_module(i, d, N)) for i in s)
    print(f'RSA authenticity check: {e}')

    print("Result of authenticity check: " + ((Fore.CYAN + 'same') if e == h_b else (Fore.RED + 'fake')) + Fore.RESET)


def GOST_sign(m: bytearray) -> bool:
    q = random.getrandbits(16)
    b = random.getrandbits(16)
    while not check_prime(q * b + 1):
        b = random.getrandbits(16)
        p = q * b + 1

    print("p = ", p)
    print("q = ", q)
    print("b = ", b)

    g = random.randint(1, p - 1)
    a = pow_module(g, b, p)
    while not a > 1:
        g = random.randint(1, p - 1)
        a = pow_module(g, b, p)

    x = random.randint(1, q-1)
    print("x = ", x)
    y = pow_module(a, x, p)
    print("y = ", y)

    h = hashlib.md5(m).hexdigest()
    print(f'GOST md5 hash: {h}')
    h = int(h, 16)

    r = 0
    s = 0
    while s == 0:
        while r == 0:
            k = random.randint(1, q-1)
            r = pow_module(a, k, p) % q
        s = (k * h + x * r) % q

    keys['GOST_sign'] = {'q': q, 'a': a, 'y': y, 'p': p, 'r': r}

    with open(r'..\signs\GOST_sign.txt', 'w') as f:
        f.write(str(s))

    return s


def GOST_signcheck(m: bytearray, s: list):
    q = keys["GOST_sign"]["q"]
    y = keys["GOST_sign"]["y"]
    r = keys["GOST_sign"]["r"]
    a = keys["GOST_sign"]["a"]
    p = keys["GOST_sign"]["p"]
    # Хэш функция проверяемого сообщения
    h = hashlib.md5(m).hexdigest()

    temp = gcd_modified(h, q)[1]
    print(temp)
    if temp < 1:
        temp += q

    u1 = (s * temp) % q
    u2 = (-r * temp) % q
    v = ((pow_module(a, u1, p) * pow_module(y, u2, p)) % p) % q

    print("Result of authenticity check: " + ((Fore.CYAN + 'same') if v == r else (Fore.RED + 'fake')) + Fore.RESET)


if __name__ == '__main__':
    try:
        shutil.rmtree('..\signs')
    except OSError:
        pass
    os.mkdir('..\signs')
    filename = '..\input'
    filename_fake = "..\input_fake"
    ext = 'txt'
    m = read_file(filename, ext)
    m_fake = read_file(filename_fake, ext)
    print(m)
    print()
    s = RSA_sign(m)
    with open(r'..\signs\rsa_sign.txt', 'w') as f:
        f.write(str(s))
    RSA_signcheck(m, s)
    print()
    s = ElGamal_sign(m)
    with open(r'..\signs\elgamal_sign.txt', 'w') as f:
        f.write(str(s))
    ElGamal_signcheck(m, s)
    print()
    GOST_sign(m)
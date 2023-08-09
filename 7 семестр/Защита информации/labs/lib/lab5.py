from lib.lab4 import *
from sys import byteorder
import collections

voting_options = {"No": 0, "Yes": 1, "Abstain": 2}
voting_options_count = len(voting_options)


class Server:
    def __init__(self):
        # P = Q = 0
        # while P == Q:
            # P = generate_prime(0, 10 ** 9)
            # print("P = ", P)
            # Q = generate_prime(0, 10 ** 9)
            # print("Q = ", Q)
        while P := random.getrandbits(512):
            if check_prime(P):
                break
        # print("P = ", P)
        while Q := random.getrandbits(512):
            if check_prime(Q):
                break
        # print("Q = ", Q)
        self.N = P * Q
        print("N:", self.N)
        phi = (P - 1) * (Q - 1)
        self.D = generate_coprime(phi)
        print("D:", self.D)
        self.C = gcd_modified(self.D, phi)[1]
        while self.C < 0:
            self.C += phi
        self.voted = set()
        self.blanks = list()
        print(f'Сервер запущен')


def my_sha(n: int) -> int:
    return int.from_bytes(hashlib.sha3_256(n.to_bytes(ceil(n.bit_length() / 8), byteorder=byteorder)).digest(),
                          byteorder=byteorder)


def inverse(n: int, p: int) -> int:
    inv = gcd_modified(n, p)[1]
    if inv < 0:
        inv += p
    return inv


def vote(name, choice):
    print(f'\n#{name} голосует#')
    if name in server.voted:
        return print(f'Голос от избирателя {name} уже есть.')

    # вычисление подписи
    rnd = random.getrandbits(256)
    v = voting_options[choice]
    n = rnd << 257 | v
    r = generate_coprime(server.N)
    h = my_sha(n)
    _h = h * pow_module(r, server.D, server.N) % server.N

    # отправление подписи на сервер
    server.voted.add(name)
    _s = pow_module(_h, server.C, server.N)
    s = _s * inverse(r, server.N) % server.N

    print(f'#Ответ сервера-голосования#')
    # blanks = set()
    if my_sha(n) == pow_module(s, server.D, server.N):
        print(f'Голос принят.')
        server.blanks.append((n, s))
    else:
        print(f'Голос отклонен')
        print(my_sha(n))
        print(pow_module(s, server.D, server.N))


if __name__ == '__main__':
    server = Server()
    vote("Boris", "Abstain")
    vote("Alice", "Yes")
    vote("Mike", "No")
    vote("Borisss", "No")
    vote("MikeMike", "Yes")

    print("\nПроголосовавшие:")
    for vote in server.voted:
        print(vote)
    counter = collections.Counter()
    for blank in server.blanks:
        counter[blank[0] & voting_options_count] += 1
    print("\nРезультат голосования:")
    print("За: \t\t ", counter[1])
    print("Против:\t\t ", counter[0])
    print("Воздержались:", counter[2])
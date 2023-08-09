from lib.lab3 import *
from colorama import Fore, init


# ♠ ♣ ♥ ♦ S - пики, C - трефы, H - червы, D - бубны
def gen_deck() -> dict:
    suits = ['♠', '♣', '♥', '♦']
    faces = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']

    cards = []
    for suit in suits:
        for face in faces:
            cards.append(str(suit + face))
    return {i: cards[i - 2] for i in range(2, 54)}


def mental_poker(players_num):

    # подготовка к игре
    while True:
        q = generate_prime(0, 10 ** 9)
        p = 2 * q + 1
        if check_prime(p):
            break
    print("P:", p)

    C = list()
    D = list()
    for _ in range(players_num):
        C_temp = generate_coprime(p-1)
        D_temp = gcd_modified(C_temp, p-1)[1]
        if D_temp < 0:
            D_temp += (p - 1)
        C.append(C_temp)
        D.append(D_temp)
    print("C:", C)
    print("D:", D)

    # создание колоды
    origin_deck = gen_deck()
    print("Deck:", origin_deck)
    deck_keys = list(origin_deck.keys())
    print(deck_keys)

    # random.shuffle(deck_keys)
    # print(deck_keys)
    # deck = {key: origin_deck[key] for key in deck_keys}
    # print(deck)
    # deck_keys = list(deck.keys())
    # print(deck_keys)

    # шифруем колоду секретными ключами C
    for i in range(players_num):
        deck_keys = [pow_module(j, C[i], p) for j in deck_keys]
        random.shuffle(deck_keys)
        print(f"Shuffle {i+1}: {deck_keys}")

    # раздаём карты игрокам
    hands = list()
    ################################
    # сразу по две каждому
    for i in range(players_num):
        hands.append([])
        for j in range(2):
            card = deck_keys[j]
            deck_keys.remove(card)
            hands[i].append(card)
    ################################
    # по одной карте по кругу
    # for i in range(players_num):
    #     hands.append([])
    # for j in range(2):
    #     for i in range(players_num):
    #         card = deck_keys[0]
    #         deck_keys.remove(card)
    #         hands[i].append(card)
    ################################
    print("Hands:",  hands)

    table = deck_keys[:5]
    print("Table:", table)

    # расшифровка карт на столе
    for i in range(players_num):
        table = [pow_module(table[j], D[i], p) for j in range(len(table))]
    print("Table decoded:", table)
    table = {key: origin_deck[key] for key in table}
    # print(f'\nCards on the table: {list(table.values())}')
    print("\nCards on the table:", end=' ')
    for i in table.values():
        if i[0] == "♠" or i[0] == "♣":
            print(Fore.WHITE + i + Fore.RESET, end=' ')
        else:
            print(Fore.RED + i + Fore.RESET, end=' ')
    print()

    # расшифровка карт в руках игроков
    for i in range(players_num):
        for j in range(players_num):
            if i != j:
                v = 0
                while v < len(hands[0]):
                    hands[i][v] = pow_module(hands[i][v], D[j], p)
                    v += 1
        v = 0
        while v < len(hands[0]):
            hands[i][v] = pow_module(hands[i][v], D[i], p)
            v += 1
    hands = [{key: origin_deck[key] for key in hand} for hand in hands]
    for i in range(players_num):
        # print(f'Player {i + 1} has cards: {list(hands[i].values())}')
        print(f"Player {i + 1} has cards:", end=' ')
        for j in hands[i].values():
            if j[0] == "♠" or j[0] == "♣":
                print(Fore.WHITE + j + Fore.RESET, end=' ')
            else:
                print(Fore.RED + j + Fore.RESET, end=' ')
        print()

    return 0


if __name__ == '__main__':
    print("♠ ♣ ♥ ♦ ")
    mental_poker(3)
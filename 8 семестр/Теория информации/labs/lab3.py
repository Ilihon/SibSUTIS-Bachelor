from lab2 import *
import re
from collections import Counter
from math import log2, ceil


def decimal_converter(num):
    if num == 0.0:
        return 0.0
    while num > 1:
        num /= 10
    return num


def float_bin(number: float, places: int):
    whole, dec = str(number).split(".")
    whole = int(whole)
    dec = int(dec)
    res = bin(whole).strip("0b") + "."
    for x in range(places):
        whole, dec = str((decimal_converter(dec)) * 2).split(".")
        dec = int(dec)
        res += whole
    return res


def shanon_code(text: str):
    split_line = list(text[i: i + 1] for i in range(len(text)))

    probabilities = {k: v / len(split_line) for k, v in Counter(split_line).items()}
    probabilities = dict(
        sorted(probabilities.items(), key=lambda item: item[1], reverse=True)
    )
    # print(probabilities)

    code_length = [ceil(-log2(i)) for i in probabilities.values()]
    # print(code_length)

    cumulative_probs = [float(0) for _ in range(len(probabilities))]
    for i in range(1, len(probabilities)):
        cumulative_probs[i] = (
            cumulative_probs[i - 1] + list(probabilities.values())[i - 1]
        )
    # print(cumulative_probs)

    codes = list()
    for i in range(len(cumulative_probs)):
        codes.append(float_bin(cumulative_probs[i], code_length[i])[1:])
        print(
            f"{list(probabilities.keys())[i]}: {list(probabilities.values())[i]:.4f} - {codes[i]}"
        )

    l_average = sum(
        list(probabilities.values())[i] * code_length[i]
        for i in range(len(probabilities.items()))
    )
    print("L среднее:", l_average)

    with open("coded_text.txt", "w") as f:
        for i in text:
            index = list(probabilities.keys()).index(i)
            f.write(codes[index])

    with open("coded_text.txt", "r") as f:
        text = f.readline()
    for i in range(1, 4):
        print(f'Энтропия для {i} символа(ов) подряд:', calc_entropy_modified(text, i))
    return l_average


def main():
    text = preprocess_file("sao.txt")
    orig_entropy = calc_entropy_modified(text, 1)
    print("Энтропия оригинального текста:", orig_entropy)
    # избыточность кодироавния
    print("r =", shanon_code(text) - orig_entropy)
    return 0


if __name__ == "__main__":
    exit(main())

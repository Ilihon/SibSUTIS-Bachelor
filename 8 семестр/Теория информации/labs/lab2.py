from lab1 import *
from collections import Counter
import re

def preprocess_file(filename: str):
    with open(filename, 'r') as f:
        line = f.read()
        f.close()
    line = line.lower()
    line = re.sub(r'[^\w\s]', '', line)
    line = line.replace("\n", '')
    return line


def calc_entropy_modified(line, symb_in_row):
    # split_line = []
    # for i in range(len(line)):
    #     if i + symb_in_row >= len(line):
    #         break
    #     split_line.append(line[i: i + symb_in_row])

    # print(line)
    # print(split_line)

    # symb_occur = {}
    # for c in split_line:
    #     if c in symb_occur:
    #         symb_occur.update({c: symb_occur.get(c) + symb_in_row})
    #     else:
    #         symb_occur.update({c: 1})

    # print(split_line)
    # actual_probability = {k: v / len(line) / symb_in_row for k, v in Counter(split_line).items()}
    # print(Counter(split_line))

    split_line = list(
        line[i: i + symb_in_row] for i in range(len(line) - symb_in_row + 1)
    )

    actual_probability = {k: v / len(line) for k, v in Counter(split_line).items()}
    # print(f'Фактическая вероятность: {sorted(actual_probability.items())}')

    result = -sum(x * log2(x) for x in actual_probability.values())

    return result / symb_in_row


# название файла, и до какого количества чисел подряд считаем
def count_alphabet_entropy_using_created_file(filename, symbols_streak):
    for i in range(1, symbols_streak):
        print(f'Энтропия для {i} символа(ов) подряд: {calc_entropy_modified(filename, i)} \n')


def main():
    equal_prob = {'a': 1 / 3, 'b': 1 / 3, 'c': 1 / 3}
    diff_prob = {'a': 0.1, 'b': 0.3, 'c': 0.6}

    print("F1")
    count_alphabet_entropy_creating_random_file(equal_prob, 'f1.txt', 50000)
    # print("F2")
    # count_alphabet_entropy_creating_random_file(diff_prob, 'f2.txt', 50000)
    print("Готовый текст")
    line = preprocess_file('sao.txt')
    count_alphabet_entropy_using_created_file(line, 3)
    return 0


if __name__ == '__main__':
    exit(main())

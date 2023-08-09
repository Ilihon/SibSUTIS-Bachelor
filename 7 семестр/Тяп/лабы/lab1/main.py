from dataclasses import dataclass
from typing import Dict, List


@dataclass
class Grammar:
    VT: List[str]
    VN: List[str]
    P: Dict[str, List[str]]
    S: str


def grammar_input():
    result = dict()
    VT = list(map(str, input("Введите терминальные символы: ").split()))
    VN = list(map(str, input("Введите не терминальные символы: ").split()))
    n = int(input("Введите количество правил: "))
    P = dict()
    for _ in range(n):
        r = input("Введите терминал правила: ")
        rs = input("Введите правило:").split()
        P[r] = rs
    S = str(input("Введите целевой символ: "))
    VT.append("_")
    return {"VT": VT, "VN": VN, "P": P, "S": S}


def count_non_term_sym(grammar, sequence):
    length = 0
    for sym in sequence:
        if sym in grammar.VT:
            length += 1
    return length


# data = {"VT": ["a", "b", "c"],
#         "VN": ["A", "B", "C"],
#         "P": {"A": ["aBbbC"], "B": ["aaBb", ""], "C": ["cC", ""]},
#         "S": "A"}
data = {"VT": ["0", "1"],
        "VN": ["A", "B"],
        "P": {"A": ["0A1A", "1A0A", ""]},
        "S": "A"}
# data = grammar_input()
left_border, right_border = map(int, input("Введите диапозон цепочек ОТ и ДО\n").split())

if __name__ == '__main__':
    grammar = Grammar(data["VT"], data["VN"], data["P"], data["S"])
    print(grammar)
    rules = list(grammar.S)
    used_sequence = set()
    while rules:
        sequence = rules.pop()
        # print("seq: " + sequence)
        if sequence in used_sequence:
            continue
        used_sequence.add(sequence)
        no_term = True
        for i, symbol in enumerate(sequence):
            # print("symbol: " + symbol)
            if symbol in grammar.VN:
                no_term = False
                for elem in grammar.P[symbol]:
                    temp = sequence[:i] + elem + sequence[i + 1:]
                    # print(len(temp), right_border+1)
                    if count_non_term_sym(grammar, temp) <= right_border and temp not in rules:
                        rules.append(temp)
            elif symbol not in grammar.VT:
                no_term = False
                print("цепочка " + sequence + " не разрешима")
                break
        # for elem in rules:
        #     print("rule: " + elem)
        # print("******")
        if no_term and left_border <= len(sequence) <= right_border:
            print(sequence if sequence else "лямбда")

from collections import defaultdict
import random


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


# генерируем взаимно-простое число
def generate_coprime(p):
    result = random.randint(2, p)
    # print(result)
    while gcd(p, result) != 1:
        result = random.randint(2, p)
        # print(result)
    return result


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


def Fill_Graph():
    try:
        with open('Path.txt', 'r') as f:
            nums = f.read().splitlines()
    except OSError:
        print("Ошибка открытия файла с графами")
        return -1
    # print(nums)

    N = int(nums[0])
    M = int(nums[1])
    id = list()
    firststr = "\t"

    for i in range(N):
        id.append(i + 1)
        firststr += str(i + 1) + "\t"
    # print(id)
    # print(firststr)

    Graph_G = [[0] * N for i in range(N)]
    Graph_H = [[0] * N for i in range(N)]
    # print(Graph_G)

    print("Стартовый граф:")
    print(firststr)
    for i in range(len(Graph_G)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(Graph_G[i])):
            Graph_G[i][j] = 0
            print(Graph_G[i][j], end="\t")
        print("\n", end="")
    print()

    # заполнение графа Алисой
    for k in range(M):
        line = nums[k + 2]
        split_line = line.split(",")
        i = int(split_line[0])
        j = int(split_line[1])
        Graph_G[i - 1][j - 1] = 1
        Graph_G[j - 1][i - 1] = 1
        Graph_H[i - 1][j - 1] = 1
        Graph_H[j - 1][i - 1] = 1
    # print(Graph_G)
    # print(Graph_H)

    print("Граф после заполнения Алисой:")
    print(firststr)
    for i in range(len(Graph_G)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(Graph_G[i])):
            print(Graph_G[i][j], end="\t")
        print("\n", end="")

    return N, M, Graph_G, Graph_H, firststr


def All_Path(Graph):
    Dict = defaultdict(list)
    for i in range(len(Graph)):
        for j in range(len(Graph[i])):
            if Graph[i][j] == 1:
                Dict[i].append(j + 1)
    return Dict


def Search_Gamilton_Cycle(G, size, pt, path=[]):
    if pt not in set(path):
        path.append(pt)
        if len(path) == size:
            return path
        for pt_next in G.get(pt - 1, []):
            res_path = [i for i in path]
            candidate = Search_Gamilton_Cycle(G, size, pt_next, res_path)
            if candidate is not None:
                return candidate


def RSA_Matrix_Encode(NewGraph, x, p, N):
    TempGraph = [[0] * N for i in range(N)]
    for i in range(len(NewGraph)):
        for j in range(len(NewGraph[i])):
            TempGraph[i][j] = pow_module(NewGraph[i][j], x, p)

    return TempGraph


def Gamilton_Cycle():
    N, M, Graph_G, Graph_H, firststr = Fill_Graph()

    List_Path = list()
    New_Graph_H = [[0] * N for i in range(N)]
    New_Graph_G = [[0] * N for i in range(N)]
    LeftRandom = list(range(1, N + 1))
    random.shuffle(LeftRandom)

    print(f"\nN = {N}, M = {M}")

    # Находим все переходы из вершин
    Dict = All_Path(Graph_G)
    print("\nПереходы:")
    for i in range(len(Dict)):
        print(f"{i + 1}: {Dict[i]}")

    # Поиск Гамильтонова цикла
    Path = Search_Gamilton_Cycle(Dict, N, 1, List_Path)
    print(f"\nГамильтонов цикл: {Path}\n")

    print("--------------------------------------")
    print("Действия первого абонента - Алисы")
    print("--------------------------------------")

    NewList = list(range(N))
    random.shuffle(NewList)
    NewList_str = [i + 1 for i in NewList]
    print(f"Алиса рандомит вершины графа: {NewList_str} \n")

    k = 0
    z = 0
    for i in NewList:
        for j in NewList:
            # print(f"[{i}][{j}]: {Graph_G[int(i)][int(j)]}")
            New_Graph_H[k][z] = Graph_G[int(i)][int(j)]
            z += 1
        z = 0
        k += 1

    print("Изоморфный граф: ")
    print(firststr)
    for i in range(len(New_Graph_H)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(New_Graph_H[i])):
            print(New_Graph_H[i][j], end="\t")
        print("\n", end="")

    print("\nПеред кодировкой алгоритмом RSA\n" +
          f"Припишем рандомное число из списка {LeftRandom}")
    k = 0
    z = 0
    for i in LeftRandom:
        for j in LeftRandom:
            New_Graph_H[k][z] = int(str(j) + str(New_Graph_H[k][z]))
            z += 1
        z = 0
        k += 1

    print("\nПодготовленная матрица до RSA:")
    print(firststr)
    for i in range(len(New_Graph_H)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(New_Graph_H[i])):
            print(New_Graph_H[i][j], end="\t")
        print("\n", end="")

    print("\nАлиса генерирует ключи;")
    P = generate_prime(0, 10 ** 9)
    # print("P = ", P)
    Q = generate_prime(0, 10 ** 9)
    # print("Q = ", Q)
    N_encode = P * Q
    print("Ключ N: ", N_encode)
    Phi = (P - 1) * (Q - 1)
    # print("Phi = ", Phi)

    d = generate_coprime(Phi)

    c = gcd_modified(d, Phi)[1]
    if c < 0:
        c += Phi
    print("Ключ c: ", c)

    Graph_F = RSA_Matrix_Encode(New_Graph_H, d, N_encode, N)

    print("\nМатрица после RSA, для Боба:")
    print(firststr)
    for i in range(len(Graph_F)):
        print(" " + str(i + 1), end="\t")
        for j in range(len(Graph_F[i])):
            print(Graph_F[i][j], end="\t")
        print("\n", end="")

    print()
    print("--------------------------------------")
    print("Действия Второго абонента - Боба")
    print("--------------------------------------")
    print("Боб получил матрицу F\n")
    print("Какой вопрос выберет Боб?")
    print("1.'Алиса, каков Гамильтонов цикл для графа H?'")
    print("2.'Алиса, действительно ли граф H изоморфен G?'")
    answer = int(input())

    if answer == 1:
        print("-'Алиса, покажи Гамильтонов цикл?'")
        print("Алиса отсылает Бобу Гамильтонов цикл")
        print(f"Гамильтонов цикл: {Path}")
        print("Боб проходит по Матрице Н-штрих, преобразуя соответствующий элемент цикла")
        print("Если элементы Матрицы F равны этим преобразованным, то Боб пытается по данному циклу пройти свой граф\n" +
              "Если ему это удается, то Все впорядке. Если нет, то возникла ошибка в алгоритме")

        Bob_Check = RSA_Matrix_Encode(New_Graph_H, d, N_encode, N)

        flag = False
        check = 0
        for i in range(len(Graph_F)):
            for j in range(len(Graph_F[i])):
                if Bob_Check[i][j] == Graph_F[i][j]:
                    check += 1
        if check == pow(N, 2):
            flag = True
        if flag:
            print(f"\nМатрицы идентичны, т.к. flag = {flag}")
            print(f"Гамильтонов цикл Алисы: {Path}")
            print(f"Гамильтонов цикл Боба: {Path}")
        else:
            print(f"Матрицы разные flag = {flag}")

    if answer == 2:
        print("-'Докажи изоморфизм, Алиса?'")
        print("\nАлиса отсылает Бобу матрицу, которая еще не преобразования в RSA\n" +
              "И рандом столбцов, который она использовала после получения Гамильтонова цикла")
        print("\nБоб проверяет матрицы: сравнивает матрицы F и H-штрих путем\n" +
              "повторного шифрования и сравнения матриц")

        Bob_Check = RSA_Matrix_Encode(New_Graph_H, d, N_encode, N)

        flag = False
        check = 0
        for i in range(len(Graph_F)):
            for j in range(len(Graph_F[i])):
                if Bob_Check[i][j] == Graph_F[i][j]:
                    check += 1
        if check == pow(N, 2):
            flag = True
        if flag:
            print(f"\nМатрицы идентичны, т.к. flag = {flag}")
        else:
            print(f"\nМатрицы разные flag = {flag}")

        print("Далее Боб отбрасывает все разряды кроме единичного от каждого элемента матрицы и получает матрицу,\n" +
              "изоморфную стартовой\n")

        print(firststr)
        for i in range(len(New_Graph_H)):
            print(" " + str(i + 1), end="\t")
            for j in range(len(New_Graph_H[i])):
                Numstr = str(New_Graph_H[i][j])
                New_Graph_H[i][j] = int(Numstr[-1])
                print(New_Graph_H[i][j], end="\t")
            print("\n", end="")

        print("\nЗатем Боб переставляет столбцы в соответствии с полученной нумерацией от Алисы")
        print(f"\nРандом Алисы вершин графа: {NewList_str}")

        k = 0
        z = 0
        for i in NewList:
            for j in NewList:
                # print(f"{i},{j}")
                # print(f"{k},{z}")
                New_Graph_G[int(i)][int(j)] = New_Graph_H[k][z]
                z += 1
            z = 0
            k += 1

        print("\nЗатем Алиса проверяет граф H,преобразуя его по ряду Алисы, и исходный граф Алисы\n" +
              "Если они идентичны, то из графа H мы получили граф G")

        flag = False
        check = 0
        for i in range(len(New_Graph_G)):
            for j in range(len(New_Graph_G[i])):
                # print(f"[{i}][{j}]: {Graph_G[int(i)][int(j)]}")
                if Graph_H[i][j] == New_Graph_G[i][j]:
                    check += 1
        if check == pow(N, 2):
            flag = True
        if flag:
            print()
            print(f"Матрицы идентичны, т.к. flag = {flag}")
        else:
            print(f"Матрицы разные flag = {flag}")
        #
        # print(firststr)
        # for i in range(len(New_Graph_G)):
        #     print(" " + str(i + 1), end="\t")
        #     for j in range(len(New_Graph_G[i])):
        #         Numstr = str(New_Graph_G[i][j])
        #         New_Graph_G[i][j] = int(Numstr[-1])
        #         print(New_Graph_G[i][j], end="\t")
        #     print("\n", end="")


if __name__ == '__main__':
    Gamilton_Cycle()

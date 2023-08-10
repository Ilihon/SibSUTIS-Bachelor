import copy

S = []


def new2(mas):
    global S
    min = 0
    ct = 0
    for i in range(len(mas)):
        if i not in S:
            if mas[i] < 0:
                ct += 1
    if ct >= (len(mas) - len(S)):
        return -1
    while True:
        for j in range(len(mas)):
            if j not in S:
                if mas[j] == min:
                    return j
        min += 1
        # print(min)


with open('input-2g.txt') as f:
    matrix = [list(map(int, row.split())) for row in f.readlines()]
n = matrix[0][0]
matrix.pop(0)
print(n)

for i in range(n):
    for j in range(n):
        print("{:4d}".format(matrix[i][j]), end="")
    print()

print("Введите вершину")
ver = int(input())
S.append(ver)
print(S)

D = [0] * n
D2 = []
for i in range(n):
    if i != ver:
        D[i] = matrix[ver][i]

print(D)
z = new2(D)
print(z)
S.append(z)
D3 = copy.deepcopy(D)

while len(S) != n:
    print(D, "Do")
    for j in range(n):
        if j not in S:
            print(S)
            print(D[j])
            print(D[S[-1]] + matrix[S[-1]][j], "---", D[S[-1]], matrix[z][j])
            if D[j] == -1 and (D[S[-1]] == -1 or matrix[S[-1]][j] == -1):
                D[j] = -1
            elif D[j] == -1:
                D[j] = D[S[-1]] + matrix[S[-1]][j]
            elif D[S[-1]] == -1 or matrix[S[-1]][j] == -1:
                D[j] = D[j]
                # print("ya")
            else:
                D[j] = min(D[j], (D[S[-1]] + matrix[S[-1]][j]))
    print(D, "posle")
    z = new2(D)
    D3[z] = D[z]
    S.append(z)
print(D3)
print("Кратчайшие расстояния от {} вершины до всех остальных:".format(ver))
for i in range(len(D)):
    print("Из {} в {} =".format(ver, i), D3[i])

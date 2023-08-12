def factorial(n):
    factor = 1
    for i in range(2, n + 1):
        factor *= i
    return factor


def Langraj(XY, xn, n):
    Pn = 0
    for i in range(n + 1):
        # print(i)
        chisl = 1
        znam = 1
        for j in range(n + 1):
            if j != i:
                chisl *= xn - XY[j][0]
        # print('Chisl =', chisl)
        for j in range(n + 1):
            if j != i:
                znam *= XY[i][0] - XY[j][0]
        # print('Znam =', znam)
        Pn += XY[i][1] * chisl / znam
        # print(XY[i][1]*chisl/znam)
    # print(f'P{n}({xn}) = {Pn}')
    return Pn


def Eitken(XY,xn,x_first,x_last):
    if(x_first == x_last):
        return XY[x_first][1]
    Pn=(Eitken(XY, xn, x_first, x_last-1)*(xn - XY[x_last][0]) - Eitken(XY, xn, x_first+1, x_last)*(xn - XY[x_first][0]))/(XY[x_first][0]-XY[x_last][0])
    return Pn


def Newton1(XY, xn, n, h):
    matriza = [[XY[i][1] for i in range(len(XY))]]
    for i in range(n):
        matriza.append([0] * (n-i))
    for i in range(n):
        for j in range(n-i-h+1):
            matriza[i+1][j] = matriza[i][j+h] - matriza[i][j]
    # print(matriza)
    Pn = matriza[0][0]
    # print(Pn)
    q = (xn - XY[0][0])/h
    # print(q)
    for i in range(1, n+1):
        qvrem = q
        for j in range(1, i):
            qvrem *= q-j
        Pn += (matriza[i][0]/factorial(i))*qvrem
        # print(Pn, matriza[i][0], factorial(i), qvrem)
    return Pn

def Newton2(XY, xn, n, h):
    matriza = [[XY[i][1] for i in range(len(XY))]]
    for i in range(n):
        matriza.append([0] * (n-i))
    for i in range(n):
        for j in range(n-i-h+1):
            matriza[i+1][j] = matriza[i][j+h] - matriza[i][j]
    # print(matriza)
    Pn = matriza[0][n]
    # print(Pn)
    q = (xn - XY[n][0])/h
    # print(f'q: ({xn} - {XY[n][0]})/{h}')
    for i in range(1, n+1):
        qvrem = q
        for j in range(1, i):
            qvrem = qvrem * (q+j)
        Pn += (matriza[i][n-i]/factorial(i))*qvrem
        # print(xn,Pn, matriza[i][n-i], factorial(i), qvrem)
    return Pn

def Ereal(XY, xn, n, pogresh, proizv_podstav):
    Eokrug = 2 ** (n - 1) * pogresh
    print('Eокруглённое =', Eokrug)
    Eusech = 1
    for i in range(n + 1):
        Eusech *= xn - XY[i][0]
    Eusech *= proizv_podstav
    Eusech /= factorial(n)
    print('Eусечённое =', Eusech)
    print('Eреальное =', Eokrug + Eusech)

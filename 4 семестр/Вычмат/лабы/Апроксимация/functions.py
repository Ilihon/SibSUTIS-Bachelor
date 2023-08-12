import sympy as sym
from sympy import lambdify
import numpy as np

def CountSum(x, g, X, Y):
    n = len(g)
    SLAU = []
    for i in range(n):
        SLAU.append([])
        for j in range(n):
            sum = 0
            element1 = lambdify(x, sym.S(g[i]))
            element2 = lambdify(x, sym.S(g[j]))
            for v in range(len(X)):
                sum = sum + (element1(X[v]) * element2(X[v]))
            SLAU[i].append(sum)
    print('A = ', SLAU)
    b = []
    for i in range(n):
        sum = 0
        element = lambdify(x, sym.S(g[i]))
        for v in range(len(X)):
            sum = sum + element(X[v]) * Y[v]
        b.append(sum)
    print('B = ', b)
    koefs = np.linalg.solve(SLAU, b)
    # for i in range(len(koefs)):
        # if(koefs[i]<10 ** (-14)):
            # koefs[i] = 0
            # a=0
    return koefs

def fun(xx):
    return xx ** 2 - 6 * xx


def gold(left, right):
    eps, e, step = 10 ** (-8), 1, 0
    k1 = 0.382
    k2 = 0.618
    lam = [left + k1 * (right - left), left + k2 * (right - left)]
    f = [fun(i) for i in lam]
    while e > eps:
        step += 1
        if f[0] > f[1]:
            left = lam[0]
            lam = [left + k1 * (right - left), left + k2 * (right - left)]
            f = [fun(i) for i in lam]
        else:
            right = lam[1]
            lam = [left + k1 * (right - left), left + k2 * (right - left)]
            f = [fun(i) for i in lam]
        e = abs(right - left)

        print("-------------------\nStep:", step, "\nleft:", left, "\nright:", right)
    print("x = ", (left + right) / 2, "f(x) =", fun((left + right) / 2))
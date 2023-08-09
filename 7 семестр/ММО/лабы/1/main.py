import csv
from math import sqrt
from sklearn.model_selection import train_test_split


def loo_h(X_train, h_max: int = 10):
    h_calc = 0
    h_accuracy = 0

    for h in range(2, h_max + 1):
        correct = 0
        incorrect = 0

        for dot in X_train:
            class_0 = 0
            class_1 = 0

            for influence_dot in X_train:
                if not dot == influence_dot:
                    if core(distance(dot, influence_dot) / h) <= 1:
                        if influence_dot[2] == 0:
                            class_0 += 1
                        else:
                            class_1 += 1

            if class_0 + class_1 == 0:
                continue

            if class_0 >= class_1:
                calc = 0
            else:
                calc = 1

            # print(calc)

            if dot[2] == calc:
                correct += 1
            else:
                incorrect += 1

        accuracy = correct / (correct + incorrect)
        print("Для {0} процент точности = {1}".format(h, accuracy * 100), "%")
        if h_accuracy < accuracy:
            h_accuracy = accuracy
            h_calc = h
    return h_calc


def loo_k(X_train, k_max: int = 10):
    k_calc = 0
    k_accuracy = 0

    for k in range(2, k_max + 1):
        correct = 0
        incorrect = 0

        for dot in X_train:
            class_0 = 0
            class_1 = 0
            with_calculated_distance = []  # [(dot, distance), (dot, distance), (dot, distance)]
            for neighbor_dot in X_train:
                dist = distance(dot, neighbor_dot)
                with_calculated_distance.append((neighbor_dot, dist))

            # with_calculated_distance_sorted = sorted(with_calculated_distance, key=lambda x: x[1])
            # k_div = with_calculated_distance_sorted[k + 1]
            k_div = sorted(with_calculated_distance, key=lambda x: x[1])[k + 1][1]

            for neighbor_dot, dist in with_calculated_distance:
                if not dot == neighbor_dot:
                    if core(dist / k_div) <= 1:
                        if neighbor_dot[2] == 0:
                            class_0 += 1
                        else:
                            class_1 += 1

            if class_0 >= class_1:
                calc = 0
            else:
                calc = 1
         # print(calc)
            if dot[2] == calc:
                correct += 1
            else:
                incorrect += 1
        accuracy = correct / (correct + incorrect)
        print("Для {0} процент точности = {1}".format(k, accuracy * 100), "%")
        if k_accuracy < accuracy:
            k_accuracy = accuracy
            k_calc = k
    return k_calc


def parzen_h(X_test, X_train, h):
    correct = 0

    for dot in X_test:
        class_0 = 0
        class_1 = 0
        for influence_dot in X_train:
            if not (dot[0] == influence_dot[0] and dot[1] == influence_dot[1]):
                if core(distance(dot, influence_dot) / h) <= 1:
                    if influence_dot[2] == 0:
                        class_0 += 1
                    else:
                        class_1 += 1
        if class_0 >= class_1:
            calc = 0
        else:
            calc = 1

        if dot[2] == calc:
            correct += 1

    return correct

def parzen_k(X_test, X_train, k):
    correct = 0

    for dot in X_test:
        class_0 = 0
        class_1 = 0
        with_calculated_distance = []  # [(dot, distance), (dot, distance), (dot, distance)]
        for neighbor_dot in X_train:
            dist = distance(dot, neighbor_dot)
            with_calculated_distance.append((neighbor_dot, dist))

        k_div = sorted(with_calculated_distance, key=lambda x: x[1])[k + 1][1]

        for neighbor_dot, dist in with_calculated_distance:
            if not dot == neighbor_dot:
                if core(dist / k_div) <= 1:
                    if neighbor_dot[2] == 0:
                        class_0 += 1
                    else:
                        class_1 += 1

        if class_0 >= class_1:
            calc = 0
        else:
            calc = 1
        # print(calc)
        if dot[2] == calc:
            correct += 1
    return correct


def distance(central_dot, influence_dot):
    return sqrt((central_dot[0] - influence_dot[0]) ** 2 + (central_dot[1] - influence_dot[1]) ** 2)


def core(r):
    return abs(1 - r)


X_data = []
with open("data4.csv") as f:
    csv_iter = csv.reader(f, delimiter=',')
    next(csv_iter)
    for row in csv_iter:
        X_data.append(row)

for row in X_data:
    row[0] = int(row[0])
    row[1] = int(row[1])
    row[2] = int(row[2])

X_train, X_test = train_test_split(X_data, test_size=0.33)

#print("Поиск подходящего h")
h = loo_h(X_train, 5)
print(h)
acc = parzen_h(X_test, X_train, h)
#print("Поиск подходящего k")
#k = loo_k(X_train, 5)
#print(k)
#acc = parzen_k(X_test, X_train, k)
print("Точность на тестовой выборке {0}".format(acc / len(X_test) * 100), "%")

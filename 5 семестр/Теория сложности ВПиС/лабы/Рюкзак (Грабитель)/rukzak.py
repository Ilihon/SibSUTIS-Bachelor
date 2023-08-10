with open('rukzak.txt') as f:
    items = [list(map(int, row.split())) for row in f.readlines()]
max_weight = items[0][0]
copy = max_weight
items.pop(0)

print("Вместимость рюкзака:", max_weight)
weights = [item[0] for item in items]
prices = [item[1] for item in items]
buf = [0] * len(prices)
gold = [0] * (max_weight + 1)
elements = [0] * len(weights)
for i in range(max_weight + 1):
    for j in range(len(weights)):
        if i - weights[j] >= 0:
            buf[j] = gold[i - weights[j]] + prices[j]
    gold[i] = max(buf)
    buf = [0] * len(prices)

while max_weight > 0:
    if gold[max_weight] - min(weights) < 0:
        break
    for j in range(len(weights)):
        if max_weight - weights[j] >= 0:
            if (gold[max_weight - weights[j]] + prices[j]) == gold[max_weight]:
                buf[j] = 1
                elements[j] += max(buf)
                max_weight -= weights[j]
                break
    buf = [0] * len(prices)

print("Места занято в рюкзаке:", copy - max_weight)
print("Места осталось в рюкзаке:", max_weight)
print("Итоговая стоимость предметов:", gold[copy])
print("Количество взятых предметов по весу:")
for i in range(len(prices)):
    print("Предмет весом {} и стоимостью {} взят в колчестве {}".format(weights[i], prices[i], elements[i]))


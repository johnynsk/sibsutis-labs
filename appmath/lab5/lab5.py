import math

accuracy = 0.0001
n = 5
a = 0
b = 0.5
l1 = 0.618
l2 = 0.382

def f(x, n = n):
    return math.e ** math.sqrt(x) * (x - 1) * (x - 10) * (x - n - 1) * (x - 0.5)


def iterate(a = a, b = b, iteration = 0, accuracy = accuracy):
    if b - a <= accuracy:
        x = (a + b) / 2
        return [x, f(x)]

    x1 = l1 * a + l2 * b
    x2 = l2 * a + l1 * b

    fx1, fx2 = [f(x1), f(x2)]

    if fx1 > fx2:
        x2, fx2 = [x1, fx1]
        x1 = l1 * a + l2 * b
        fx1 = f(x1)
        iteration += 1
        return iterate(a, x2, iteration, accuracy)

    x1, fx1 = [x2, fx2]
    x2 = l2 * a + l1 * b
    fx2 = f(x2)
    iteration +=1
    return iterate(x1, b, iteration, accuracy)


print(iterate(a, b, 0, accuracy))

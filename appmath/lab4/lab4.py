import math

c = 3 * ((0.1 * (5 + 1)) ** 3)
accuracy = 0.0001
accuracy_count = 4
h = (3 * accuracy / c) ** (1.0 / 3.0)
print 8 ** (1.0/3.0)
def a_round(value, accuracy = accuracy_count):
    return round(value, accuracy_count)

def f(x, c = c):
    return (1 / c ** 2) * math.cos(x * c)

def d1f(x, c = c):
    return - (1 / c) * math.sin(x * c)

def calc_values(c, h):
    fx = []
    for i in range(-1, 22):
        x = c + i * h
        fx.append((x, a_round(f(x, c))))

    i = 0
    di1fx = []
    d1fx = []
    for i in range(0, 20):
        x = c + i * h
        di1fx.append((x, a_round((fx[i][1] - fx[i + 2][1]) / (2 * h))))
        d1fx.append((x, a_round(d1f(x))))

    return [fx, di1fx, d1fx]

def pretty_print(fx, di1fx, d1fx):
    for i in range(len(fx) - 1):
        if i == 0 or i >= (len(fx) - 2):
            print [i, fx[i][0], fx[i][1]]
            continue
        print [i, fx[i][0], fx[i][1], d1fx[i - 1][1], di1fx[i - 1][1]]

print [c, h]
fx, di1fx, d1fx = calc_values(c, h)
pretty_print(fx, di1fx, d1fx)

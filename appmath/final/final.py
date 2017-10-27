# coding: utf8
import math
import collections

accuracy = 0.0001
h = 0.5
h2 = 0.1
y0 = 0.2
x0 = 0
x_max = 1

def around(value, accuracy = accuracy):
    if accuracy > 1:
        return value
    return round(value, int(math.floor(-1 * math.log(accuracy, 10))) + 1)

def f(x, y):
#    print "f(%s, %s)" % (x, y)
    return 1 -y + 3 * y * math.sin(x)

def Q(x):
    return x ** 2

def step_runge_kutt_4(x, y, h):
    k1 = f(x, y)
    k2 = f(x + h / 2.0, y + (h / 2.0) * k1)
    k3 = f(x + h / 2.0, y + (h / 2.0) * k2)
    k4 = f(x + h, y + h * k3)
    return y + h * (k1 / 6.0 + k2 / 3.0 + k3 / 3.0 + k4 / 6.0)

def double_calc_iterator(x, y, x_max, h, accuracy = accuracy):
    F1 = calc_by_runge_kutt_4(x, y, x_max, h)
    F2 = calc_by_runge_kutt_4(x, y, x_max, h / 2.0)
    print "Вычисления с шагом h=%s" % h
    print_result(F1)
    for x_it in F1.keys():
        if abs(F1[x_it] - F2[x_it]) > 15 * accuracy:
            return double_calc_iterator(x, y, x_max, h / 2.0, accuracy)
    return [F1, h]

def calc_by_runge_kutt_4(x, y, x_max, h):
    F = collections.OrderedDict()
    F[x] = y
    x += h
    while x <= x_max:
#        print "Для вычисления xk+1 = %s используем xk = %s, f(xk) = %s" % (around(x), next(reversed(F)), F[next(reversed(F))])
        F[around(x)] = step_runge_kutt_4(next(reversed(F)), F[next(reversed(F))], h)
        x += h
    return F

def find_interval(F, x):
    closest = min(F.keys(), key = lambda k: abs(k - x))
    if closest < x:
        next = F._OrderedDict__map[closest][1][2]
        return [(closest, F[closest]), (next, F[next])]
    previous = F._OrderedDict__map[closest][0][2]

    return [(previous, F[previous]), (closest, F[closest])]

def interpolate(x, a, b):
    return a[1] + (b[1] - a[1]) * (x - a[0]) / (b[0] - a[0])

def interpolate_by_step(F, a, b, h, accuracy = accuracy):
    Fi = collections.OrderedDict()
    while a <= b:
        if a in F:
            Fi[around(a)] = F[around(a)]
        else:
            point1, point2 = find_interval(F, around(a))
            Fi[around(a)] = interpolate(around(a), point1, point2)
        a += h

    return Fi

def simpson_integrate(f, a, b, h):
    sum = Q(f[around(a)])
    n = 0
    a += h
    while a < around(b - h):
        print ["a", around(a), "h", h]
        sum += (2 * (1 + (n % 2))) * Q(f[around(a)])
        n += 1
        a += h
        pass
    sum += Q(f[around(b)])
    print ["last", around(b), f[around(b)], Q(f[around(b)])]

    return sum * h/ 3.0

def print_result(F):
    for key in F:
        print "x = %s, y = %s" % (key, F[key])

F, step = double_calc_iterator(x0, y0, x_max, h)
print "Решение дифференциального уравнения"
print_result(F)
print "Вычисленный шаг = %s" % step
Fi = interpolate_by_step(F, x0, x_max, h2, accuracy)
print "Результаты интерполяции"
print_result(Fi)
Qf = simpson_integrate(Fi, x0, x_max, h2)
print "Количество теплоты [%s; %s] = %s" % (x0, x_max, Qf)

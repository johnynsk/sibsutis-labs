import math

ratios = {'a': 1, 'b': -3, 'c': -24, 'd': -8};
interval = [-100, 100]
accuracy = 0.0001

def f(x, a = ratios['a'], b = ratios['b'], c = ratios['c'], d = ratios['d']):
    return a * x ** 3 + b * x ** 2 + c * x + d

def d1f(x, a = ratios['a'], b = ratios['b'], c = ratios['c']):
    return 3 * a * x **2 + b * 2 * x + c

def d2f(x, a = ratios['a'], b = ratios['b']):
    return 6 * a * x + b * 2

def calc_d1f_roots(a = ratios['a'], b = ratios['b'], c = ratios['c']):
    roots = []
    sign = 1;
    for i in range(2):
        roots.append((-(2 * b) + sign * math.sqrt((2 * b) ** 2 - 4 * (3 * a) * c)) / (2 * 3 * a));
        sign *= -1;

    roots.sort()
    return roots

def calc_significant_intervals(f0, whole_interval = interval):
    points = []
    points.append(whole_interval[0]);
    points.extend(f0)
    points.append(whole_interval[-1]);
    return points;

def point_by_horde(a, b):
    return a - f(a) * (b - a) / (f(b) - f(a))

def calc_length(a, b):
    sign = 1
    if a * b > 0:
        sign = -1
    return abs(abs(a) + sign * abs(b))

def iteration(a, b, iterations_count = 0, current_iteration = 0, accuracy = accuracy):
    if iterations_count == 0:
        iterations_count = calc_iterations(a, b, accuracy)
#    c = point_by_horde(a, b)
    c = (a + b) / 2
    r = calc_length(a, b)

#    print ['rcba', r, c, b, a, current_iteration]
    if r > accuracy and current_iteration < iterations_count:
        if f(a) * f(c) < 0:
            b = c
        elif f(b) * f(c) < 0:
            a = c
        current_iteration += 1
#        print ['callnext', a, b, c]
        return iteration(a, b, iterations_count, current_iteration, accuracy)
    else:
        return [a, b, round((a + b) / 2, 5)]

#from calc_significant_intervals
def real_root_finding(intervals):
    roots = list()

    for i in range(1, len(intervals)):
        roots.append(iteration(intervals[i - 1], intervals[i]))
    return roots

def calc_iterations(a, b, accuracy):
    return math.ceil(math.log((b - a) / accuracy, 2))

def calc_acc_nueton(a, b):
    m1 = min([d1f(a), d1f(b)])
    m2 = max([d2f(a), d2f(b)])

sign_intervals = calc_significant_intervals(calc_d1f_roots(), interval)
print real_root_finding(sign_intervals)
#    return m2 / (2 * m1) * (

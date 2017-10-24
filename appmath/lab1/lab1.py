#!/usr/bin/python

import math
import operator
#def point(x, i, c, h):
#    return c + i * h + (i % 6 + 1) * h / 5;

def f(x):
    return round(2 * pow(c, 3) * math.sin(x/c), 4);

def calc(c, h):
    result = dict([])
    for i in range(0, 30):
        print {'i': i, 'val': round(c + i * h, 4)}
        result[round(c + i * h, 4)] = f(c + i * h);

    result = sorted(result.items(), key = operator.itemgetter(0))
    return result;

def find_nearest(model, x):
    left = model[0];
    right = model[-1];

    for pair in model:
        if pair[0] <= x and pair[0] >= left[0]:
            left = pair;
        if pair[0] >= x and pair[0] <= right[0]:
            right = pair;

    return [left, right];

def interpolate(model, points):
    result = dict([]);

    for point in points:
        nearest = find_nearest(model, point)
        left = nearest[0]
        right = nearest[1]

        print ["left", left, "right", right]
        # x-x1/x2-x1 = y-y1/y2-y1
        result[point] = round(left[1] + ((right[1] - left[1]) * (point - left[0])) / (right[0] - left[0]), 4)

    result = sorted(result.items(), key = operator.itemgetter(0))
    return result;

def pretty_print(model):
    for key in model:
        print {"x": key[0], "y": key[1]}

def calc_step(c):
    return math.sqrt(4 * 5 * 0.0001 / c)

c = 6.0
h = calc_step(c)
#h = 0.001
print ["h=", h]
model = calc(c,h)
pretty_print(model)

#model = dict([(0.0, 0), (1.0, -2), (2.0, 6)]);
points = []
for i in range(0, 29):
    point = round(c + i * h + ((i % 4 + 1) / 5.0) * h, 4)
    points.append(point);
print(points)
#print(process(model, [1.5, 2.7]));
interpolated = interpolate(model, points)
for pair in interpolated:
    print ["x", pair[0], "~f", pair[1], "f", f(pair[0])]





#!/usr/bin/python

import math

#def point(x, i, c, h):
#    return c + i * h + (i % 6 + 1) * h / 5;

def f(x):
    return 2 * pow(c, 3) * math.sin(x/c);

def calc(c, h):
    result = dict([])
    for i in range(0, 30):
        result[c + i * h] = f(c + i * h);

    return result;

def interpolate(model, x):
    left = model.keys()[0];
    right = model.keys()[-1];

    for modelX in model:
        if modelX <= x and modelX > left:
            left = modelX;
        if modelX >= x and modelX < right:
            right = modelX;

    return [left, right];

def process(model, points):
    result = {};

    for point in points:
        nearest = interpolate(model, point);
        # x-x1/x2-x1 = y-y1/y2-y1
        result[point] = (point - nearest[0]) * (model[nearest[1]] - model[nearest[0]]) / (nearest[1] - nearest[0]) + model[nearest[0]];

    return result;

h = 1.0;
c = 16.0;

model = calc(c,h)
print(model)
#model = dict([(0.0, 0), (1.0, -2), (2.0, 6)]);
points = []
for i in range(0, 29):
    point = c + i * h + ((i % 4 + 1) / 5.0) * h
    points.append(point);
print(points)
#print(process(model, [1.5, 2.7]));
print(process(model, points));





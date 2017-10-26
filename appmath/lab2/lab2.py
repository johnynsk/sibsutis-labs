# coding: utf8
import math
import numpy as np
c = 0.01 * 5;

A = [
    [0.95 + c, 0.26 + c, -0.17 + c, 0.27 + c],
    [-0.15 + c, 1.26 + c, 0.36 + c, 0.42 + c],
    [0.26 + c, -0.54 + c, -1.76 + c, 0.31 + c],
    [-0.44 + c, 0.29 + c, -0.78 + c, -1.78 + c]
]

B = [2.48, -3.16, 1.52, -1.29]

accuracy = 0.01

def prepare_iteration(A, B):
    X = []
    pB = []
    C = []
    pA = []
    for i in range(0, len(A)):
        X.append(A[i][i])
        pB.append(B[i] / A[i][i])
        C.append([])
        pA.append([])
        for j in range (0, len(A)):
            pA[i].append(A[i][j] / A[i][i])
            if j == i:
                C[i].append(0)
            else:
                C[i].append(pA[i][j])

    return [pA, X, pB, C]

def calc_norm(A):
    result = A;

    if type(A) != list:
        return A

    for i in range(0, len(A)):
        if type(A[i]) == list:
            A[i] = calc_norm(A[i])
            continue
    return A

def first_norm(A):
    sum = [];
    for i in range(0, len(A)):
        sum[i] = 0;
        for j in range(0, len(A)):
            sum[j] += abs(A[j][i]);

    return max(sum)

def second_norm(A):
    sum = 0;
    for i in range(0, len(A)):
        for j in range(0, len(A)):
            sum += pow(A[i][j], 2)

    return math.sqrt(sum);

def infinity_norm(A):
    sum = [];
    for i in range(0, len(A)):
        sum.append(0);
        for j in range(0, len(A)):
            sum[i] += abs(A[i][j])

        print ['sum', sum[i], i]
    return max(sum)

def first_norm_vector(A):
    sum = 0;
    for i in range(0, len(A)):
        sum += abs(A[i])

    return sum

def second_norm_vector(A):
    sum = 0;
    for i in range(0, len(A)):
        sum += pow(A[i], 2)

    return math.sqrt(sum)

def infinity_norm_vector(A):
    sum = [];
    for i in range(0, len(A)):
        sum.append(abs(A[i]))

    return max(sum)
"""
def mul_matrix(A, B):
    C = []
    if type(B[0] == 'float'): #vector
        for i in range(0, len(B)):
            sum = 0
            for j in range (0, len(A[i])):
                sum += A[i][j] * B[j]

    for i in range(0, len(B[0])):
        row = []
        for j in range(0, len(B[0])):


    return C
"""
 #cyberforum/python/thread1122626


def mul_matrix(m1,m2):
    s = 0
    t = []
    m3=[]
    if len(m2)!=len(m1[0]):
        print "Матрицы не могут быть перемножены"
    else:
        r1=len(m1) #количество строк в первой матрице
        c1=len(m1[0]) #Количество столбцов в 1
        r2=c1           #и строк во 2ой матрице
        c2=len(m2[0])  # количество столбцов во 2ой матрице
        for z in range(0,r1):
            for j in range(0,c2):
                for i in range(0,c1):
                   s=s+m1[z][i]*m2[i][j]
                t.append(s)
                s=0
            m3.append(t)
            t=[]
    return m3

def sum_vectors(A, B):
    if len(A) != len(B):
        raise Exception('not implemented')

    for i in range(0, len(A)):
        if type(A[i]) == 'list' or type(B[i]) == 'list':
            raise Exception('not implemented')
        A[i] += B[i]

    return A;

def iteration(X0, C, B):
    Cn = np.array(C)
    Bn = np.array(B)
    X0n = np.array(X0)
    Xn = np.subtract(Bn, Cn.dot(X0n))
    return Xn.tolist()

def calc_steps_theoretically(C, pB, accuracy):
    norm_C = infinity_norm(C)
    return math.log((accuracy * (1 - norm_C)) / infinity_norm_vector(pB)) / math.log(norm_C) - 1

def calc_steps_real(C, B, X):
    loop = True
    XN = B
    count = 0
    while loop:
        XN1 = iteration(XN, C, B)
        diff = np.subtract(np.array(XN1), (np.array(XN))).tolist()
        norm = infinity_norm_vector(diff)
        XN = XN1
        count += 1
        if norm <= accuracy:
            loop = False

    return [count, XN]


pA, X, pB, C = prepare_iteration(A, B)
#print ['pA', pA, 'X', X, 'pB', pB, 'C', C]

#C = [[0, -0.6, 0.2], [-0.5, 0, 0.25], [0.4, -0.4, 0]]
#pB = [0.2, 2, 1.6]
print infinity_norm(C)
print calc_steps_theoretically(C, pB, accuracy)
#print iteration(pB, C, pB)
steps, Xc = calc_steps_real(C, pB, X)
print Xc
#print calc_norm(B)
for i in range(len(A)):
    sum = 0;
    for j in range(len(A)):
        sum += A[i][j] * Xc[j];
    print B[i] - sum





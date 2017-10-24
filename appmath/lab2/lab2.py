c = 0.01 * 5;

A = [
    [0.95 + c, 0.26 + c, -0.17 + c, 0.27 + c],
    [-0.15 + c, 1.26 + c, 0.36 + c, 0.42 + c],
    [0.26 + c, -0.54 + c, -1.76 + c, 0.31 + c],
    [-0.44 + c, 0.24 + c, -0.78 + c, -1.78 + c]
]

B = [2.48, -3.16, 1.52, -1.29]

def prepare_iteration(A):
    result = A
    for i in range(0, len(A)):
        for j in range (0, len(A)):
            if j == i:
                continue
            A[i][j] = A[i][j] / A[i][i]

    return A

def calc_norm(A):
    result = A;

    if type(A) != list:
        return A

    for i in range(0, len(A)):
        if type(A[i]) == list:
            A[i] = calc_norm(A[i])
            continue
    return A

print calc_norm(B)




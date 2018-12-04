let {cloneDeep} = require('lodash')

let solver = (coeff, independ, output) => {
    let A = cloneDeep(coeff).map((value, index) => value.concat([independ[index]]))
    if (output) {
        console.log('precondition')
        console.log(A)
    }

    for (let step = 0; step < A.length; step++) {
        console.info('iteration ' + step)

        let max = A
            .map((value, key) => ({row: key, value: Math.abs(value[step]), original: value[step]}))
            .sort((a, b) => b.value - a.value)
            .filter(item => item.row >= step)[0]

        if (max.row != step) {
            [A[max.row], A[step]] = [A[step], A[max.row]]
        }

        if (output) {
            console.log('rows replacment')
            console.log(A)
        }
        let R = cloneDeep(A)

        for (let r = 0; r < A.length; r++) {
            for (let c = step; c < A[r].length; c++) {
                if (r == step) {
                    R[r][c] = A[r][c] / A[step][step]
                    continue;
                }


                if (c == step && r != step) {
                    R[r][c] = 0;
                    continue;
                }

                R[r][c] = A[r][c] - (A[step][c] * A[r][step]) / A[step][step]
                if (output) {
                    console.log(r, c, A[r][c], A[step][c], A[r][step],  A[step][step], R[r][c], A[step][c]*A[r][step])
                }
            }
        }

        if (output) {
            console.log('after')
            console.log(R)
        }

        A = cloneDeep(R);
    }

    return A
}

module.exports = solver

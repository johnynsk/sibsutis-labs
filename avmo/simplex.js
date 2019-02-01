'use strict';

let {cloneDeep} = require('lodash')
let FREE = 'FREE';
let BASIS = 'BASIS';
let TARGET = 'TARGET';
let VARIABLES = 'M';
/**
 * Finding solution with simplex method
 *
 * Constructor
 * public solve()
 * public setMatrix(char[][] keys)
 * public addCondition(float[] keys, float target)
 * public setTarget(float[] keys, float target)
 * public setAccuracy(float accuracy)
 */
let simplex = () => {
    let matrix, costs = [], target = null, accuracy, multiplyer;
    let that = {
        solve: null,
        setMatrix: (_matrix) => {matrix = _matrix; return that;},
        addCondition: (components, edge) => {
            if (target != null && components.length != target.vars.length) {
                throw `number of variables should be equals, expected ${target.vars.length}, got ${components.length}`
            } else if (costs.length > 0 && costs[0].vars.length != components.length) {
                throw `number of variables should be equals, expected ${costs[0].vars.length}, got ${components.length}`
            }

            costs.push({vars: components, target: edge});

            return that
        },
        setTarget: (components, _target) => {
            target = {vars: components, target: _target};

            return that
        },
        setAccuracy: (_accuracy) => {
            accuracy = _accuracy;

            return that
        },
        setMultiplyer: (_multiplyer) => {
            multiplyer = _multiplyer;

            return that
        }
    }

    /**
     * Generates an matrix based on the source data, setted with setters before
     */
    let initMatrix = function () {
        if (costs.length == 0) {
            throw "no any conditions was added";
        } else if (target == null) {
            throw "target function wasn't setted";
        }

        let result = [];
        let head = [BASIS, FREE];
        costs[0].vars.forEach((_, index) => head.push(index));
        costs.forEach((condition, index) => head.push(condition.vars.length + index));
        costs.forEach((condition, index) => {
            var y = condition.vars.length + costs.length + index;
            let row = [y, condition.target];
            row = row.concat(condition.vars);
            costs.forEach((_, intIndex) => row.push(intIndex == index ? -1 : 0));
            result.push(row);
        });

        let zRow = [TARGET, 0];
        zRow = zRow.concat(target.vars.map(item => -item));
        costs.forEach(() => zRow.push(0));

        let mRow = cloneDeep(result).reduce((acc, row) => acc.map((_, index) => acc[index] += row[index])).map(item => -item * multiplyer);
        mRow[0] = VARIABLES;

        result.unshift(head);
        result.push(zRow);
        result.push(mRow);
        return result;
    }

    /**
     * Method wich are searches the resolvent
     */
    let findSolution = function () {
        for (let i = matrix.length - 1; i > 0; i--) {
            if ([TARGET, VARIABLES].indexOf(matrix[i][0]) == -1) {
                continue;
            }

            let sorted = matrix[i]
                .map((value, key) => ({
                    value: value,
                    column: key
                }))
                .filter(item => item.value < 0 && item.column > 1)
                .sort((a, b) => a.value - b.value)

            if (!sorted.length) {
                return null
            }

            let simplex = matrix
                .map((row, key) => ({
                    value: row[sorted[0].column],
                    key: key
                }))
                .filter(item => [BASIS, VARIABLES, TARGET].indexOf(matrix[item.key][0]) == -1
                    && item.value > 0
                )
                .map(item => ({
                    value: item.value,
                    key: item.key,
                    sr: matrix[item.key][1] / item.value
                }))
                .sort((a, b) => a.sr - b.sr)

            if (!simplex.length) {
                return null
            }

            return {
                row: simplex[0].key,
                column: sorted[0].column,
                value: matrix[simplex[0].key][sorted[0].column]
            }
        }
    }

    /**
     * solves matrix with found resolventa
     */
    let resolve = function (_row, _column) {
        let result = []

        for (let row = 0; row < matrix.length; row++) {
            result[row] = []

            for (let column = 0; column < matrix[row].length; column++) {
                if (column == _column) {
                    continue
                }

                if ([TARGET, VARIABLES].indexOf(matrix[row][column]) != -1 || matrix[row][0] == BASIS) {
                    result[row].push(matrix[row][column])
                    continue
                }

                if (column == 0) {
                    if (row == _row) {
                        result[row].push(matrix[0][_column]);
                    } else {
                        result[row].push(matrix[row][0]);
                    }
                    continue
                }

                if (row != _row) {
                    result[row].push(matrix[row][column] - (matrix[_row][column] * matrix[row][_column] / matrix[_row][_column]))
                    continue
                }

                result[row].push(matrix[row][column] / matrix[row][_column])
            }
        }

        return result
    }

    /**
     * prepares found result to output
     */
    let prepareResult = () => {
        let X = matrix.filter(row => [BASIS, TARGET, VARIABLES].indexOf(row[0]) == -1)
            .filter((row, index) =>
                row.map((item, column) => {
                    return {item: item, column: column}
                })
                .filter(item => item.column > 1 && item.item.toPrecision(-Math.log10(accuracy)) == -1)
                .length > 0
            )

        let roots = costs[0].vars.map((_, index) => {
            let root = X.filter(row => row[0] == index).map(row => row[1])
            return root.length ? root[0] : 0;
        });

        return {
            roots: roots,
            matrix: matrix,
            solution: null,
            string: roots.map((root, index) => `x${index}=${root}`).join('; ')
        }
    }

    /**
     * controlling unit of algorithm
     */
    that.solve = function *(iterations) {
        if (!matrix) {
            matrix = initMatrix();
        }

        let result = {matrix: matrix, solution: null};

        for (let i = 0; i < iterations; i++) {
            let solution = findSolution();
            result.solution = solution;

            if (!solution) {
                result = prepareResult();
                yield result;
                break;
            }

            yield result;
            matrix = resolve(solution.row, solution.column)
            result.matrix = matrix;
        }

        return result
    }

    return that;
}

module.exports = simplex

'use strict';

let {cloneDeep} = require('lodash')

let simplex = () => {
    let matrix, costs = [], target = null, accuracy, multiplyer;
    let that = {
        solve: null,
        setMatrix: (_matrix) => {matrix = _matrix; return that;},
        setCosts: (_costs) => {costs = _costs; return that;},
        addCondition: (components, edge) => {
            costs.push({vars: components, target: edge});
        },
        setTarget: (components, _target) => {
            target = {vars: components, target: _target};
        },
        setAccuracy: (_accuracy) => {
            accuracy = _accuracy;
            multiplyer = 1 / _accuracy / 100;

            return that
        }
    }

    let initMatrix = function () {
        let result = [];
        let head = ['B', '1'];
        console.log(costs);
        costs[0].vars.forEach((_, index) => head.push(index));
        costs.forEach((condition, index) => head.push(condition.vars.length + index));
        costs.forEach((condition, index) => {
            var y = condition.vars.length + costs.length + index;
            let row = [y, condition.target];
            row = row.concat(condition.vars);
            costs.forEach((_, intIndex) => row.push(intIndex == index ? -1 : 0));
            result.push(row);
        });

        console.log(result);
        let zRow = ['Z', 0];
        zRow = zRow.concat(target.vars.map(item => -item));
        costs.forEach(() => zRow.push(0));

        let mRow = cloneDeep(result).reduce((acc, row) => acc.map((_, index) => acc[index] += row[index])).map(item => -item * multiplyer);
        mRow[0] = 'M';
        
        result.unshift(head);
        result.push(zRow);
        result.push(mRow);
        return result;
    }

    let findSolution = function () {
        for (let i = matrix.length - 1; i > 0; i--) {
            if (['Z', 'M'].indexOf(matrix[i][0]) == -1) {
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
                .filter(item => ['B', 'M', 'Z'].indexOf(matrix[item.key][0]) == -1
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

            return [simplex[0].key, sorted[0].column, matrix[simplex[0].key][sorted[0].column]]
        }
    }

    let resolve = function (_row, _column) {
        let result = []

        for (let row = 0; row < matrix.length; row++) {
            result[row] = []

            for (let column = 0; column < matrix[row].length; column++) {
                if (column == _column) {
                    continue
                }

                if (['Z', 'M'].indexOf(matrix[row][column]) != -1 || matrix[row][0] == 'B') {
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
                    result[row].push(
                        matrix[row][column] - (matrix[_row][column] * matrix[row][_column] / matrix[_row][_column]))
                } else {
                       result[row].push(matrix[row][column] / matrix[row][_column])
                }
            }
        }

        return result//.map((row, index) => index < 1 ? row : row.map((item, column) => column < 1 ? item : (Math.abs(item) < accuracy ? 0 : item)))
//        return result.map((row, index) => index < 1 ? row : row.map((item, column) => column < 1 ? item : Math.round(item, -Math.log10(accuracy))))
    }

    let prepareResult = () => {
        let X = matrix.filter(row => ['B', 'Z', 'M'].indexOf(row[0]) == -1)
            .filter((row, index) =>
                row.map((item, column) => {
                    return {item: item, column: column}
                })
                .filter(item => item.column > 1 && Math.round(item.item, -Math.log10(accuracy)) == -1)
                .length > 0
            )
        let roots = costs[0].vars.map((_, index) => {
            let root = X.filter(row => row[0] == index).map(row => row[1])
            return root.length ? root[0] : 0;
        });

        return {
            roots: roots,
            matrix: matrix,
            string: roots.map((root, index) => `x${index}=${root}`).join('; ')
        }
    }

    that.solve = function *(iterations) {
        if (!matrix) {
            matrix = initMatrix();
        }
        console.log('initial matrix', matrix);

        let result = {matrix: null};

        for (let i = 0; i < iterations; i++) {
            let solution = findSolution();

            console.log(`solution in step ${i}`, solution);
            
            if (!solution) {
                result = prepareResult();
                yield result;
                break;
            }

            matrix = resolve(solution[0], solution[1])
            result.matrix = matrix;
            yield result
        }

        return result
    }

    return that;
}

module.exports = simplex

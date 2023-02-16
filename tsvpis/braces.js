'use strict';

let _ = require('underscore')
let Vertex = require('./vertex')
let Result = require('./result');
let Stats = require('./stats')

let matrix = (source) => {
    let matrixes = _.clone(source)
    let stats = new Stats();
    let result = [];
    const N = matrixes.length;
    const R = source
        .map((item, index) => {
            if (index < matrixes.length -1) {
                return [item[0]];
            } else {
                return item;
            }
        })
        .reduce((accum, item) => {
            return accum.concat(item);
        }, []);

    matrixes.forEach((item, index) => R[index] = item[0]);
    
    let putBraces = (F, N) => {
        let prioritize = (l, r) => {
            if (l == r) {
                return l;
            } else if (r - l > 1) {
                //console.log(`min f(${l}, ${r}) is achievable on f(${l}, ${F[l][r].index}) + f(${F[l][r].index + 1}, ${r}):`);
                return [prioritize(l, F[l][r].index), prioritize(F[l][r].index + 1, r)];
            } else {
                return [l, r];
            }
        }

        let restore = (item) => {
            if (typeof item != 'object') {
                return 'M' + item;
            }

            let result = '';
            
            if (typeof item[0] == 'object') {
                result += '(' + restore(item[0]) + ')';
            } else {
                result += 'M' + item[0];
            }
            
            result += ' * ';

            if (typeof item[1] == 'object') {
                result += '(' + restore(item[1]) + ')';
            } else {
                result += 'M' + item[1];
            }

            return result;
        };

        let prioritized = prioritize(1, N);
        
        return {
            array: prioritized,
            string: restore(prioritized)
        };
    }

    let calculate = (R, N) => {
        let F = [];
        for (let i = 0; i < R.length; i++) {
            F[i] = [];
            for (let j = 0; j < R.length; j++) {
                F[i][j] = {
                    value: i == j ? 0 : Infinity,
                    index: 0
                }
            }
        }

        for (let t = 1; t < N; t++) { // length of a block
            for (let k = 1; k < N - t + 1; k++) { // calculations per block length
                // console.log(`f(${k}, ${k + t}) = min([`)
                
                let minValue = Infinity;
                let minIndex = undefined;

                for (let j = k; j < k + t; j++) {
                    let val = F[k][j].value + F[j + 1][k + t].value + R[k - 1] * R[j] * R[k + t];
                    // console.log(`\tf(${k}, ${j}) + f(${j + 1}, ${k + t}) + ${R[k - 1]} * ${R[j]} * ${R[k + t]} = ${val}`);
                
                    if (minValue > val) {
                        minValue = val;
                        minIndex = j;
                    }
                }

                // console.log(`])`);
                // console.log(`modifying F[k][k+t] from ${F[k][k + t].value}:${F[k][k + t].index} to ${minValue}:${minIndex}`);
                F[k][k + t].value = minValue;
                F[k][k + t].index = minIndex;
            }
        }

        return F;
    };

    // _.times(N + 1, index => result[index] = Array(N + 1).fill(0));

    // console.log(calculate(R, N));
    let F = calculate(R, N);
    let braces = putBraces(F, N);
    return {
        matrix: F,
        braces: braces
    };
}

module.exports = matrix;

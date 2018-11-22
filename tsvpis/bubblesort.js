'use strict';
let {clone} = require('underscore')
let Result = require('./result')
let Stats = require('./stats')

let sort = (source) => {
    let stats = new Stats();
    let result = clone(source);
    let isSorted = true;
    let i = 0;

    while (i < result.length) {
        stats.iterate();
        stats.compare();
        stats.access(2);
        if (i + 1 != result.length && result[i] > result[i + 1]) {
            isSorted = false;
            stats.swap();
            stats.access(2);
            [result[i], result[i + 1]] = [result[i + 1], result[i]];
        }

        i++;
        if (!isSorted && i == result.length) {
            isSorted = true;
            i = 0;
        }
    }

    return new Result(result, stats);
}

module.exports = sort;


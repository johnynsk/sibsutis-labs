'use strict';
let {clone} = require('underscore')
let Result = require('./result')
let Stats = require('./stats')

let sort = (source) => {
    let stats = new Stats();
    let result = clone(source);

    for (let i = 0; i < result.length; i++) {
        let min = i;
        stats.iterate();
        for (let j = i + 1; j < result.length; j++) {
            stats.iterate().compare().access(2);
            if (result[j] <= result[min]) {
                min = j;
            }
        }

        stats.access(2).swap();
        [result[i], result[min]] = [result[min], result[i]];
    }

    return new Result(result, stats);
}

module.exports = sort;


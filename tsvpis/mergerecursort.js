'use strict';
let {clone} = require('underscore')
let Result = require('./result')
let Stats = require('./mergestats')

let sort = (source) => {
    var stats = new Stats();
    let result = clone(source);

    let merge = (sourceLeft, sourceRight) => {
        let left = clone(sourceLeft)
        let right = clone(sourceRight)

        let result = []
        while(left.length && right.length) {
            if (left[0] <= right[0]) {
                result.push(left.shift());
                continue;
            }
            result.push(right.shift());
        }

        result = result.concat(left).concat(right);
        stats.log(Math.max(sourceLeft.length, sourceRight.length), `[${sourceLeft.join(',')}] + [${sourceRight.join(',')}] => [${result.join(',')}]`)
        return result;
    }

    let sliceAndMerge = (source) => {
        let result = clone(source);

        if (result.length <= 1) {
            return result;
        }

        let middle = parseInt(result.length / 2);
        let left = sliceAndMerge(result.slice(0, middle));
        let right = sliceAndMerge(result.slice(middle));
        return merge(left, right);
    }

    result = sliceAndMerge(result);
    return new Result(result, stats);
}

module.exports = sort;


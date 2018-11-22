'use strict';
let {clone} = require('underscore')
let Result = require('./result')
let Stats = require('./stats')

let sort = (source) => {
    var stats = new Stats();
    let result = clone(source);

    for (let block = 1; block < result.length; block *= 2)
    {
        for (let chunk = 0; chunk < result.length - block; chunk += 2 * block)
        {
            let left = 0;
            let right = 0;

            let edges = {
                left: chunk,
                middle: chunk + block,
                right: chunk + 2 * block
            }

            if (edges.right > result.length) {
                edges.right = result.length;
            }

            let buffer = [];
            var leftc = [];
            var rightc = [];

            for (let i = edges.left; i < edges.middle; i++) {
                leftc.push(result[i]);
            }

            for (let i = edges.middle; i < edges.right; i++) {
                rightc.push(result[i]);
            }

//            console.log([leftc, rightc]);

            while (edges.left + left < edges.middle && edges.middle + right < edges.right) {
                stats.access(2);
                stats.compare();
                if (result[edges.left + left] <= result[edges.middle + right]) {
                    stats.access(1);
                    buffer.push(result[edges.left + left]);
                    left += 1;
                } else {
                    stats.access(1);
                    buffer.push(result[edges.middle + right]);
                    right += 1;
                }
            }

            while (edges.left + left < edges.middle) {
                stats.access(1);
                buffer[left + right] = result[edges.left + left];
                left += 1;
            }

            while (edges.middle + right < edges.right) {
                stats.access(1);
                buffer[left + right] = result[edges.middle + right];
                right += 1;
            }
            console.log(block, chunk, `[${leftc.join(',')}] + [${rightc.join(',')}] => [${buffer.join(',')}]`)

            //console.log(buffer);
            for (let i = 0; i < left + right; i++) {
                stats.swap();
                result[edges.left + i] = buffer[i];
            }
        }
    }
console.log(result);
    return new Result(result, stats);
}

module.exports = sort;


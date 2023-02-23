'use strict';

let _ = require('underscore')
let Vertex = require('./vertex')
let Result = require('./result');
let Stats = require('./stats')

let fordBellman = (source, from) => {
    source = _.clone(source)
    let stats = new Stats();
    if (typeof from == "undefined") {
        from = 0;
    }

    let N = source.length;
    let D=[];
    let prevNodes=[];
    for (let i = 0; i < N; i++) {
        prevNodes[i] = undefined;
    }
    for (let i = 0; i <= N; i++) {
        D[i] = [];
        for (let j = 0; j < N; j++) {
            D[i][j] = Infinity;
        }
    }

    D[0][from] = 0;
    prevNodes[from] = -1;

    let unstable = true;
    let k = 0;
    while (unstable) {
        ++k;
        unstable = false;

        console.log(`iteration ${k}`)

        for (let i = 0; i < N; i++) {
            let min = [];
            let decorate_letters = [];
            let decorate_numbers = [];

            for (let j = 0; j < N; j++) {
                min.push({sum: D[k-1][j] + source[j][i], vertex: j});
                decorate_letters.push(`D^${k-1}(${j}) + C(${j},${i})`);
                decorate_numbers.push(D[k-1][j] + source[j][i] < Infinity ? D[k-1][j] + source[j][i] : '∞');
            }
            
            min.sort((a, b) => a.sum - b.sum);
            D[k][i] = min[0].sum;
            let cond = D[k][i] != D[k-1][i];

            if (D[k][i] != D[k-1][i]) {
                unstable = true;
                prevNodes[i] = min[0].vertex;
            }

            console.log(`D^${k}(${i}) = min(` + decorate_letters.join(', ') + ") = min (" + decorate_numbers.join(',') + ") = " + D[k][i] + `. \tprev vertex: ${prevNodes[i]}` + (D[k][i] == D[k-1][i] ? '   \tstabilization' : ''));
        }
    }

    let restore = (prevNodes, id) => {
        let path = [];

        while (id != -1) {
            path.push(id);
            id = prevNodes[id];
        }
        
        return path;
    }

    let nodes = [];
    for (let j = 0; j < N; j++) {
        nodes.push({id: j, cost: D[k][j], path: restore(prevNodes, j).reverse()});
    }

    return nodes;
}

module.exports = fordBellman;

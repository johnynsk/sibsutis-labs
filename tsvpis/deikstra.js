'use strict';

let _ = require('underscore')
let Vertex = require('./vertex')
let Result = require('./result');
let Stats = require('./stats')

let deikstra = (source, from) => {
    source = _.clone(source)
    if (typeof from == "undefined") {
        from = 0;
    }

    let result = [];
    _.times(source.length, index => result[index] = new Vertex(index));
    result[from] = new Vertex(from, 0);

    let dist = [];
    let prev = [];
    let used = [];
    _.times(source.length, index => {
        dist[index] = Infinity
        prev[index] = -1;
        used[index] = false;
    });
    dist[from] = 0;

    let min_dist = 0;
    let min_vertex = from;
    while (min_dist < Infinity) {
        let i = min_vertex;
        used[i] = true;

        for (let j in source[i]) {
            j = parseInt(j);
            let wt = source[i][j];

            if (dist[i] + wt < dist[j]) {
                dist[j] = dist[i] + wt;
                prev[j] = i;
            }
        }

        min_dist = Infinity;
        
        for (let j in source[i]) {
            j = parseInt(j);
            if (!used[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                min_vertex = j;
            }
        }

        console.log('S = ', 
            used.map((item, index) => item ? index : null).filter(item => item != null),
            '  \tw = ', i,
            '  \tD(w) = ', dist[i],
            '  \tD = ', dist);
    }

    let restore = (prev, id) => {
        let path = [];

        while (id != -1) {
            path.push(id);
            id = prev[id];
        }
        
        return path;
    }

    let nodes = [];
    for (let j = 0; j < source.length; j++) {
        nodes.push({id: j, cost: dist[j], path: restore(prev, j).reverse()});
    }

    return nodes;
}

module.exports = deikstra;

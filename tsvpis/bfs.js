'use strict';
let {clone} = require('underscore')
let Result = require('./result')
let Stats = require('./stats')

let bfs = (needle, haystack, from) => {
    // assert(from >= 0 && from <= haystack.length && needle >= 0 && needle <= haystack.length);
    let visited = [];
    let queue = [];
    queue.push(from);
    let i = 0;
    while(queue.length > 0 && i < 10) {
        ++i;
        let node = queue.shift();
        
        if (-1 != visited.indexOf(node)) {
            continue;
        }

        visited.push(node);

        console.log(node, visited, haystack[node]);
        let childs = haystack[node]
            .map((item, index) => item != Infinity ? index : Infinity)
            .filter(item => item != Infinity && visited.indexOf(item) == -1);

        queue = queue.concat(childs);
    }

    return {
        found: visited.indexOf(needle) != -1,
        visited: visited
    };
}

module.exports = bfs;


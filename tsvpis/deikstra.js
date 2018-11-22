'use strict';

let _ = require('underscore')
let Vertex = require('./vertex')
let Result = require('./result');
let Stats = require('./stats')

let deikstra = (source, from) => {
    source = _.clone(source)
    let stats = new Stats();
    if (typeof from == "undefined") {
        from = 0;
    }

    let result = [];
    _.times(source.length, index => result[index] = new Vertex(index));
    result[from] = new Vertex(from, 0);

    let currentVertex = result[from];
    do {
        let verticesSortedByCost = source[currentVertex.getNumber()]
            .map((value, index) => {
                return {
                    number: index,
                    cost: value
                }
            })
            .sort((a, b) => a.cost - b.cost)
            .filter(item => item.number != currentVertex.getNumber() && item.number != from && item.cost != Infinity)
            .map(item => {
                let vertex = result[item.number];
                if (vertex.getCost() > currentVertex.getCost() + item.cost) {
                    vertex.setCost(currentVertex.getCost() + item.cost)
                        .setPath(_.clone(currentVertex.getPath()).concat([currentVertex]));
                }
                return result[item.number]
            })
            .forEach(item => console.log(["from", currentVertex.getNumber(), "to", item.getNumber(), item.getCost()]));

        currentVertex.setVisited(true);

        let leastVertices = result
            .filter(item => !item.isVisited() && item.getPath().length > 0);

        if (leastVertices.length == 0) {
            break;
        }

        currentVertex = leastVertices[0];
    } while(result.filter(item => !item.isVisited()).length > 0)

    return new Result(result, stats)
}

module.exports = deikstra;

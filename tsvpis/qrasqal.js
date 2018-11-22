'use strict';
let {clone} = require('underscore')
let qrasqal = (source) => {
    let costs = [];
    source.forEach((row, rowId) => {
        row.forEach((cost, cellId) => {
            if (cellId <= rowId || cost == Infinity) {
                return;
            }

            costs.push({A: rowId, B: cellId, cost: cost});
        })
    })

    costs.sort((a, b) => {
        if (a.cost == b.cost) {
            if (a.A == b.A) {
                return a.B - b.B;
            }
            return a.A - b.A;
        }

        return a.cost - b.cost;
    });

    let result = [];
    let broken = [];
    let links = [];

    for (let costId in costs)  {
        if (links[0] && links[0].length == source.length) {
            console.log('done');
            return result;
        }
        let cost = costs[costId];
        let group = null;
        if (links.filter(item => item.indexOf(cost.A) >= 0 && item.indexOf(cost.B) >= 0).length) {
            console.log('broken', cost, links);
            continue;
        }

        let existsA = links.filter(item => item.indexOf(cost.A) >= 0);
        let existsB = links.filter(item => item.indexOf(cost.B) >= 0);
        if (existsA.length && existsB.length) {
            links = links.filter(item => item.indexOf(cost.A) == -1 || item.indexOf(cost.B) == -1)
            links.push(existsA.concat(existsB));
        } else if (existsA.length || existsB.length) {
            let exists = [existsA, existsB].filter(item => item.length);
            links = links.map(item => {
                if (item.indexOf(cost.A) >= 0) {
                    item.push(cost.B);
                } else if (item.indexOf(cost.B) >= 0) {
                    item.push(cost.A);
                }
            
                return item;
            })
        } else {
            links.push([cost.A, cost.B]);
        }
        console.log('applied', cost, links);
    }
    
    return result;
}

module.exports = qrasqal;

'use strict';
let expect = require('chai').expect
let selectSort = require('./selectsort')
let mergeSort = require('./mergesort')
let bubbleSort = require('./bubblesort')
let mergeRecursiveSort = require('./mergerecursort')
let mergeStats = require('./mergestats')
let qrasqal = require('./qrasqal')
let init = require('./init')
let deikstra = require('./deikstra')
let vertex = require('./vertex')
const {clone} = require('underscore')
const original = [-10, -55, -1, 0, 6, 1, 8, 3, 70, 30, 15, 9, -4, -3, -127.5, 255]
const expected = [-127.5, -55, -10, -4, -3, -1, 0, 1, 3, 6, 8, 9, 15, 30, 70, 255]

let tree = [
    [0, 2, 7, 4, 6, 3],
    [2, 0, 4, 5, 6, 1],
    [7, 4, 0, 8, 7, Infinity],
    [4, 5, 8, 0, 5, 7],
    [6, 6, 7, 5, 0, 3],
    [3, 1, Infinity, 7, 3, 0]
];

let deikstraTree = [
    [Infinity, 7, 9, Infinity, Infinity, 14, Infinity],
    [7, Infinity, 10, 15, Infinity, Infinity, Infinity],
    [9, 10, Infinity, 11, Infinity, 2, Infinity],
    [Infinity, 15, 11, Infinity, 6, Infinity, Infinity],
    [Infinity, Infinity, Infinity, 6, Infinity, 9, Infinity],
    [14, Infinity, 2, Infinity, 9, 0, Infinity],
    [Infinity, Infinity, Infinity, Infinity, Infinity, Infinity, Infinity]
]

let deikstraTreeExpectations = [0, 7, 9, 20, 20, 11, Infinity];


let methods = new Map([
    ["selectSort", selectSort],
    ["mergeSort", mergeSort],
    ["bubbleSort", bubbleSort],
    ["mergeRecursiveSort", mergeRecursiveSort],
]);
//methods = new Map([]);

let dumpStats = (stats) => {
    if (!stats || !stats.logs) {
        return;
    }

    Object.keys(stats.logs)
    .sort((a, b) => parseInt(a) - parseInt(b))
    .forEach(key => {
        Object.keys(stats.logs[key])
        .sort((a, b) => parseInt(a) - parseInt(b))
        .forEach(itemKey => console.log(key, itemKey, stats.logs[key][itemKey]));
    })
}

methods.forEach((method, name) => {
    describe(name, () => {
        it("sorts predefined array, n = 12", () => {
            let result = method(original);
            expect(result.getResult()).to.deep.equal(expected);

            dumpStats(result.getStats());
        });

        it("sorts generated array, n = 100", () => {
            let array = init(100, 20);
            let sorted = clone(array).sort((a, b) => a - b);
            let result = method(array);
            expect(result.getResult()).to.deep.equal(sorted);
            dumpStats(result.getStats())
        });
    });
});

describe("qrasqal", () => {
    it("predefined", () => {
        console.log(qrasqal(tree))
    });
});

describe("deikstra", () => {
    it("predefined", () => {
        let result = deikstra(deikstraTree, 0);
        result.getResult().forEach(item => console.log('vertex', item.getNumber(), 'cost', item.getCost(), 'path', item.getPath().map(item => item.getNumber())));

        expect(result.getResult().map(item => item.getCost()))
            .to.deep.equal(deikstraTreeExpectations);
    });
});


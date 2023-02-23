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
let braces = require('./braces')
let vertex = require('./vertex')
let bfs = require('./bfs')
let frog = require('./frog')
let graphGenerator = require('./graph-generator')
let fordBellman = require('./ford-bellman')
const {clone} = require('underscore')
const original = [-10, -55, -1, 0, 6, 1, 8, 3, 70, 30, 15, 9, -4, -3, -127.5, 255]
const expected = [-127.5, -55, -10, -4, -3, -1, 0, 1, 3, 6, 8, 9, 15, 30, 70, 255]
const inf = Infinity;

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

/*
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
*/

// describe("8 - qrasqal 8 ballow", () => {
//     it("methodics", () => {
//         let tree = [
//             [inf, 20,  inf, inf, inf, 23,  1 ],
//             [20,  inf, 5,   inf, inf, inf, 4 ],
//             [inf, 5,   inf, 3,   inf, inf, 9 ],
//             [inf, inf, 3,   inf, 17,  inf, 16],
//             [inf, inf, inf, 17,  inf, 28,  25],
//             [23,  inf, inf, inf, 28,  inf, 36],
//             [1,   4,   9,   16,  25,  36,  inf]
//         ];
//         console.log(qrasqal(tree))
//     });
    
// //     it("test on exam", () => {
// //         let tree = [
// //             [0, 2, 7,   4, 6, 3  ],
// //             [2, 0, 4,   5, 6, 1  ],
// //             [7, 4, 0,   8, 7, inf],
// //             [4, 5, 8,   0, 5, 7  ],
// //             [6, 6, 7,   5, 0, 3  ],
// //             [3, 1, inf, 7, 3, 0  ]
// //         ];
        
// //         console.log(qrasqal(tree))
// //     });
// });
/**/

// describe("7 - ford-bellman", () => {
//     it("predefined", () => {
//         let tree = [
//             [0, 25,  15,  7,   2  ],
//             [25,  0, 6,   inf, inf],
//             [15,  6,   0, 4,   inf],
//             [7,   inf, 4,   0, 3  ],
//             [2,   inf, inf, 3,   0]
//         ]

//         let expected = [
//             {id: 0, cost: 0, path: [0] },
//             {id: 1, cost: 15, path: [0, 4, 3, 2, 1]},
//             {id: 2, cost: 9, path: [0, 4, 3, 2]},
//             {id: 3, cost: 5, path: [0, 4, 3]},
//             {id: 4, cost: 2, path: [0, 4]}
//         ];

//         let result = fordBellman(tree, 0);
        
//         result.forEach(item => {
//             let path = item.path.join(' → ');
//             console.log('vertex', item.id, '\tcost', item.cost, ' \tpath', path)
//         });
//     });
// });

describe("6 - deikstra 12 ballow", () => {
    // it("predefined", () => {
    //     let tree = [
    //         [0,   7,   9,   inf, inf, 14,  inf],
    //         [7,   0,   10,  15,  inf, inf, inf],
    //         [9,   10,  0,   11,  inf, 2,   inf],
    //         [inf, 15,  11,  0,   6,   inf, inf],
    //         [inf, inf, inf, 6,   0,   9,   inf],
    //         [14,  inf, 2,   inf, 9,   0,   inf],
    //         [inf, inf, inf, inf, inf, inf, 0  ]
    //     ]

    //     let expected = [0, 7, 9, 20, 20, 11, Infinity];

    //     let result = deikstra(tree, 0);
    //     result.getResult().forEach(item => console.log('vertex', item.getNumber(), 'cost', item.getCost(), 'path', item.getPath().map(item => item.getNumber())));

    //     expect(result.getResult().map(item => item.getCost()))
    //         .to.deep.equal(expected);
    // });
    it("predefined", () => {
        let tree = [
            [0, 25,  15,  7,   2  ],
            [25,  0, 6,   inf, inf],
            [15,  6,   0, 4,   inf],
            [7,   inf, 4,   0, 3  ],
            [2,   inf, inf, 3,   0]
        ]

        let expected = [0, 15, 9, 5, 2];

        let result = deikstra(tree, 0);
        
        result.forEach(item => {
            let path = item.path.join(' → ');
            console.log('vertex', item.id, '\tcost', item.cost, ' \tpath', path)
        });
        // expect(result.getResult().map(item => item.getCost()))
        //     .to.deep.equal(expected);
    });
});

// describe("3 - braces = 12 ballow", () => {
//     // it("test from methodics", () => {
//     //     let result = braces([[10, 20], [20, 50], [50, 1], [1, 100]]);
//     //     console.log(result);
//     //     expect(result.braces.string).equal('(M1 * (M2 * M3)) * M4');
//     // })
    
//     // it("minimal test", () => {
//     //     let result = braces([[2, 1], [1, 2], [2, 3]]);
//     //     console.log(result);
//     //     expect(result.braces.string).equal('M1 * (M2 * M3)');
//     // })

//     it("minimal test", () => {
//         let result = braces([[10, 1], [1, 3], [3, 20], [20, 10], [10, 4], [4, 1], [1, 50], [50, 10], [10, 10], [10, 10]]);
//         console.log(result);
//         // expect(result.braces.string).equal('M1 * (M2 * M3)');
//     })
// });

// describe("10 - bfs = 10 ballow", () => {
//     it("test", () => {
//         let graph = [
//             [inf, 7,   9,   inf, inf, 14,  inf],
//             [7,   inf, 10,  15,  inf, inf, inf],
//             [9,   10,  inf, 11,  inf, 2,   inf],
//             [inf, 15,  11,  inf, 6,   inf, inf],
//             [inf, inf, inf, 6,   inf, 9,   inf],
//             [14,  inf, 2,   inf, 9,   0,   inf],
//             [inf, inf, inf, inf, inf, inf, inf]
//         ];
        
//         let result;
//         result = bfs(4, graph, 0);
//         expect(result.found).equal(true);

//         expect(result.visited).to.deep.equal([0, 1, 2, 5, 3, 4]);

//         result = bfs(6, graph, 0);
//         expect(result.found).equal(false);
//     })
// });

// describe("4 - frog = 38 ballow", () => {
//     it("board", () => {
//         let lengths = [0, 1, 2, 3, 5, 7, 10, 12, 14, 17];
//         let result = frog(lengths);
//         console.log(result.path)

//         expect(result.path).to.deep.equal([0, 1, 3, 5, 7, 10, 14, 17]);
//     })

//     it("board", () => {
//         let lengths = [0, 1, 2, 3, 5, 7, 10, 12, 17];
//         let result = frog(lengths);
//         expect(result.path).equal(undefined);
//     })
// })

// describe("graphgenerator", () => {
//     it("cast to csv", () => {
//         let graph = [[Infinity, 1, Infinity], [3, Infinity, 9], [Infinity, 2, Infinity]];
//         let result = graphGenerator().castToCsv(graph);
//         console.log(result);
//         expect(result).equal("");
//     })
// });

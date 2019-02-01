'use strict';

let lab1 = require('./lab1')
let lab2 = require('./lab2')
let lab3 = require('./lab3')
let simplex = require('./simplex')
let expect = require('chai').expect
let color = require("cli-color");

let coeff = [
    [-6, -5, -1, 9, -10],
    [-11, 1, 4, 6, -11],
    [-7, 7, 9, 9, 4],
    [-6, -1, -10, 14, -6],
    [-2, -15, 6, 4, 5]
];
let _coeff = [
    [1, -7, 4, -3, -3],
    [-1, -5, 7, -1, 4],
    [-6, 7, 7, 5, 7],
    [-5, -3, -6, -3, 8],
    [-5, -5, -2, -3, -6]
];

let independ = [28, 24, 52, 161, -42];
let _independ = [-12, 30, 49, -7, -67];
let _expected = [[1, 0, 0, 0, 0, 4], [0, 1, 0, 0, 0, 1], [0, 0, 1, 0, 0, 3], [0, 0, 0, 1, 0, 2], [0, 0, 0, 0, 1, 5]];
describe('lab1', () => {
    it('predefined', () => {
        expect(
            lab1(_coeff, _independ, false)
            .map(row => row.map(item => Number((item).toFixed(13))))
        ).to.deep.equal(_expected)
    })
    it('my variant', () => {
        let result = lab1(coeff, independ, true)
        let temp = result.map(item => Number((item[item.length - 1])).toFixed(13));
        for (let i in temp) {
            console.log('x' + (i+1) + ' = ' + temp[i])
        }
    })
})

describe('lab2', () => {
    it('predefined', () => {
        let iterator = lab2([1 / 3, 3 / 4], [[9, 17], [12, 8]], 100);
        for (let value of iterator) {
            let step = value.steps[value.steps.length - 1];
            let strategiesA = value.steps.filter(item => item.strategies[0] == 0).length;
            let strategiesB = value.steps.filter(item => item.strategies[1] == 0).length;

            console.log(`| ${value.steps.length}\t | ${Number(step.values[0]).toFixed(5)}\t | A${step.strategies[0]} \t | ${Number(step.values[1]).toFixed(5)} \t | B${step.strategies[1]} \t | ${step.win} \t | ${value.total} \t | ${Number(value.total / value.steps.length).toFixed(5)} \t | ${Number(strategiesA / value.steps.length).toFixed(5)} \t| ${Number(strategiesB / value.steps.length).toFixed(5)} \t`)
        }
    })
})
describe('lab3', () => {
    it('my variant', () => {
        let lab = lab3()
            .setFX(X => -5 * X[0] - 4 * Math.pow(X[1] - 6, 2))
            .setGX(X => 16 - Math.pow(X[0] - 6, 2) - Math.pow(X[1] - 4, 2))
            .setGradFx([
                x => -5,
                x => 48 - 8 * x
            ])
            .setGradGx([
                x => 12 - x * 2,
                x => 8 - x * 2
            ])
        let iterator = lab.perform([6, 4])
        for (let value of iterator) {
            console.log(`${value.step}\t | ${Number(value.point.next[0]).toFixed(6)}\t | ${Number(value.point.next[1]).toFixed(6)}\t | ${Number(value.fN).toFixed(6)}\t | ${Number(value.gN).toFixed(6)}\t | ${value.inBounds}\t | ${Number(value.alpha).toFixed(6)}\t | ${Number(value.accuracy).toFixed(6)}\t |`)
        }
    }).timeout(10000);
})

let printMatrix = (matrix, resolver) => {
    var result = matrix.map((row, index) => row.map((item, column) => {
        var pad = 10;
        if (typeof item == 'number' && index > 0 && column > 0) {
            var rounded = (Math.round(item * 100000) / 100000).toPrecision(7).padEnd(pad, ' ');
            if (resolver != null && index == resolver.row && column == resolver.column) {
                return color.magentaBright(rounded);
            }

            if (item > 0) {
                return color.green(rounded)
            }

            return color.blue(rounded)
        }
        if (typeof item == 'number') {
            return color.yellowBright(`x${item}`.padEnd(pad, ' '))
        }

        return color.yellow(item.padEnd(pad, ' '))
    }))
    .map(row => row.join(" | "))
    .join("\n")

    console.log(result);
};

describe('simplex', () => {
    it('simplex my variant', () => {
        let lab = simplex()
        lab.setTarget([9, 2])
            .addCondition([3, 1], 12)
            .addCondition([1, 2], 14)
            .addCondition([4, 11], 68)
            .setMultiplyer(Math.pow(10, 5))
            .setAccuracy(Math.pow(10, -6))

        let iterator = lab.solve(10)
        let solution = null;
        let count = 0;
        for (let value of iterator) {
            console.log(`Perform matrix in step ${count}`);
            if (value.solution != null) {
                console.log(`Got resolving element in [${value.solution.row}, ${value.solution.column}] = ${color.magentaBright(value.solution.value.toFixed(5))}`);
            }

            printMatrix(value.matrix, value.solution)
            if ('roots' in value) {
                solution = value.roots;
                console.log(`Result matrix in step ${count}`);
                console.log(`Got solution in step ${count}`, value.string);
                console.log(`Target function value = ${value.matrix.filter(row => row[0] == 'TARGET')[0][1]}`)
            }

            count++;
        }
        expect(solution).to.deep.equal([0, 12]);
    })
})

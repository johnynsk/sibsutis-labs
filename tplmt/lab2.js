#!/usr/bin/env node
'use strict';
const LEFT_ALIGNED = "left", RIGHT_ALIGNED = "right";

let ArgumentParser = require('argparse').ArgumentParser;
let parser = new ArgumentParser({
    version: '0.0.1',
    addHelp:true,
    description: 'Argparse example'
});
parser.addArgument(
    ['--expected-signs'],
    {
        help: 'the allowed signs',
        required: true
    }
);
parser.addArgument(
    ['--possible-states'],
    {
        help: 'possible states',
        required: true
    }
);
parser.addArgument(
    ['--initial-state'],
    {
        help: 'the initial state',
        required: true
    }
);
parser.addArgument(
    ['--expected-states'],
    {
        help: 'the valid states',
        required: true
    }
);
parser.addArgument(
    ['--actual-data'],
    {
        help: 'the valid states',
        required: true
    }
);

parser.addArgument(
    ['--transforms'],
    {
        help: 'a json-encoded transforming table',
        defaultValue: "{}"
    }
);

try {
    var args2 = parser.parseArgs();
    console.log(args2);
} catch (e) {
    parser.printHelp();
}

const expectedSigns = args2.expected_signs;
const possibleStates = args2.possible_states;
const initialState = args2.initial_state;
const expectedStates = args2.expected_states;
const actualData = args2.actual_data;
const transforms = JSON.parse(args2.transforms);

let dka = function (source) {
    let state = initialState;

    for (let i in source) {
        let symbol = source[i];
        console.log(`(${state}, ${source.substr(i)})`);

        if (expectedSigns.indexOf(symbol) === -1) {
            throw `Got unexpected sign "${symbol}" from the source string: "${source}"`
        }

        if (!(state in transforms) || !(symbol in transforms[state])) {
            throw `Unknown transform path from the state "${state} and symbol "${symbol}`
        }

        if (possibleStates.indexOf(transforms[state][symbol]) === -1) {
            throw `Unknown transform state "${transforms[state][symbol]}" from the state "${state}" for symbol "${symbol}"`
        }

        state = transforms[state][symbol];
    }

    if (expectedStates.indexOf(state) === -1) {
        throw `Got unexpected state "${state}", expected states was "${expectedStates}"`
    }

    console.log(`(${state}, ${source.substr(source.length)})`);
    console.info(`There are valid source "${source}", got expected state "${state}"`)
};

let validate = function () {
    for (let i in expectedSigns) {
        for (let j in expectedSigns) {
            if (j > i && expectedSigns[i] == expectedSigns[j]) {
                throw `There are duplicate sign ${expectedSigns[j]} in the expected signs`
            }
        }
    }

    for (let i in possibleStates) {
        for (let j in possibleStates) {
            if (j > i && possibleStates[i] == possibleStates[j]) {
                throw `There are duplicate sign ${possibleStates[j]} in the possible states`
            }
        }
    }

    for (let i in expectedStates) {
        for (let j in expectedStates) {
            if (j > i && expectedStates[i] == expectedStates[j]) {
                throw `There are duplicate sign ${expectedStates[j]} in the valid states`
            }
        }

        if (possibleStates.indexOf(expectedStates[i]) === -1) {
            throw `The expected state "${expectedStates[i]}" should be defined in the possible states`;
        }
    }

    if (possibleStates.indexOf(initialState) === -1) {
        throw `The initial state "${initialState[i]}" should be defined in the possible states`;
    }
};

validate();
dka(actualData);
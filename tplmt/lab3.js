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
    ['--possible-input'],
    {
        help: 'the allowed input signs',
        required: true
    }
);
parser.addArgument(
    ['--expected-output'],
    {
        help: 'the expected output signs',
        required: true
    }
);

parser.addArgument(
    ['--possible-stack'],
    {
        help: 'the allowed stack values',
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
    ['--initial-stack'],
    {
        help: 'the initial stack value',
        required: true
    }
);

parser.addArgument(
    ['--expected-states'],
    {
        help: 'the expected finishing states',
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
    ['--null-symbol'],
    {
        help: 'the null symbol equivalent',
        required: true
    }
);

parser.addArgument(
    ['--rules'],
    {
        help: 'a json-encoded rules for the determined finite automation',
        defaultValue: "{}"
    }
);

parser.addArgument(
    ['--rules-file'],
    {
        help: 'a json-encoded rules for the determined finite automation',
        defaultValue: "{}"
    }
);

let args = parser.parseArgs();
console.log(args);

const possibleInput = args.possible_input;
const expectedOutput = args.expected_output;
const possibleStack = args.possible_stack;

const possibleStates = args.possible_states;
const initialState = args.initial_state;

const initialStack = args.initial_stack;
const expectedStates = args.expected_states;
const actualData = args.actual_data;
const nullSymbol = args.null_symbol;

if ('rules_file' in args) {
    let fs = require("fs");
    args.rules = fs.readFileSync(args.rules_file);
}

const inputRules = JSON.parse(args.rules);
let rules = [];

let dka = function (source) {
    let state = initialState;
    let sourceRest = source;
    let stack = initialStack;
    let result = '';

    while (stack.length > 0) {
        console.debug(`(${state}, ${sourceRest}, ${stack}, ${result})`);

        let firstInStack = stack[0];

        let symbol = null;
        if (sourceRest.length > 0) {
            symbol = sourceRest[0];
        }

        if (symbol && possibleInput.indexOf(symbol) === -1) {
            throw `Got unexpected symbol "${symbol}" from the source string: "${source}"`
        }

        let suitableRules = rules.filter((rule, id) => {
            if (rule.source.state !== state) {
                console.warn(`rule id=${id} not suitable by source.state`);
                return false;
            }

            if (rule.source.stack !== firstInStack) {
                console.warn(`rule id=${id} not suitable by source.stack (${rule.source.stack} vs ${firstInStack})`);
                return false;
            }

            if (rule.source.symbol !== nullSymbol && (symbol && rule.source.symbol !== symbol)) {
                console.warn(`rule id=${id} not suitable by source.symbol`);
                return false;
            }

            if (rule.target.state.length === 0) {
                console.warn(`rule id=${id} not suitable by target.state`);
                return false;
            }

            if (rule.target.stack.length === 0) {
                console.warn(`rule id=${id} not suitable by target.stack`);
                return false;
            }

            console.info(`rule id=${id} should be suitable`);
            return true;
        });

        if (suitableRules.length !== 1) {
            throw `Can't find suitable rule for the state="${state}", symbol="${symbol}", stack="${stack}", suitable rules=${suitableRules.length}`;
        }

        let rule = suitableRules.pop();
        if (possibleStates.indexOf(rule.target.state) === -1) {
            throw `The state "${rule.target.state}" are impossible by the --possible-states parameter.`
        }

        state = rule.target.state;
        if (rule.source.symbol !== nullSymbol) {
            sourceRest = sourceRest.substr(1);
        }

        stack = stack.substr(1);
        if (rule.target.stack.length > 0 && rule.target.stack !== nullSymbol) {
            stack = rule.target.stack + stack;
        }

        if (rule.target.result && rule.target.result !== nullSymbol) {
            result += rule.target.result;
        }
    }

    if (expectedStates.indexOf(state) === -1) {
        throw `Got unexpected state "${state}", expected states was "${expectedStates}"`
    }

    console.log(`(${state}, ${source.substr(source.length)})`);
    console.info(`There are valid source "${source}", got expected state "${state}"`)
};

let checkDuplicates = function(input, name) {
    for (let i in input) {
        for (let j in input) {
            if (j > i && input[i] == input[j]) {
                throw `There are duplicate sign ${input[i]} in the ${name}`
            }
        }
    }
};

let validate = function () {
    checkDuplicates(possibleInput, 'possible input signs');
    checkDuplicates(expectedOutput, 'expected output signs');
    checkDuplicates(possibleStack, 'possible stack');
    checkDuplicates(possibleStates, 'possible states');
    checkDuplicates(expectedStates, 'expected states');

    for (let i in expectedStates) {
        if (possibleStates.indexOf(expectedStates[i]) === -1) {
            throw `The expected state "${expectedStates[i]}" should be defined in the possible states`;
        }
    }

    if (possibleStates.indexOf(initialState) === -1) {
        throw `The initial state "${initialState}" should be defined in the possible states`;
    }

    if (possibleStates.indexOf(nullSymbol) !== -1) {
        throw `There are not possible to set null symbol "${nullSymbol}" as possible state`;
    }

    if (possibleStates.indexOf(nullSymbol) !== -1) {
        throw `There are not possible to set null symbol "${nullSymbol}" as possible input sign`;
    }

    if (expectedOutput.indexOf(nullSymbol) !== -1) {
        throw `There are not possible to set null symbol "${nullSymbol}" as possible output sign`;
    }

    if (possibleStack.indexOf(nullSymbol) !== -1) {
        throw `There are not possible to set null symbol "${nullSymbol}" as possible output sign`;
    }

    if (possibleStack.indexOf(nullSymbol) !== -1) {
        throw `There are not possible to set null symbol "${nullSymbol}" as possible output sign`;
    }

    let rulesChecked = inputRules
        .map((rule, id) => {
            if (!('source' in rule)) {
                return [rule, id, 'source'];
            }

            if (!('state' in rule.source)) {
                return [rule, id, 'source.state'];
            }

            if (!('symbol' in rule.source)) {
                return [rule, id, 'source.symbol'];
            }

            if (!('stack' in rule.source)) {
                return [rule, id, 'source.stack'];
            }

            if (!('target' in rule)) {
                return [rule, id, 'target'];
            }

            if (!('state' in rule.target)) {
                return [rule, id, 'target.state'];
            }

            if (!('result' in rule.target)) {
                return [rule, id, 'target.result'];
            }

            if (!('stack' in rule.target)) {
                return [rule, id, 'target.stack'];
            }

            return [rule, id, false];
        });

    rulesChecked
        .filter(ruleCondition => ruleCondition[2])
        .forEach(ruleCondition => {
            console.warn(`the rule with id="${ruleCondition[1]}" are missed the "${ruleCondition[2]}" field. Skipping`);
        });

    rules = rulesChecked
        .filter(ruleCondition => ruleCondition[2] === false)
        .map(ruleCondition => ruleCondition[0]);
    console.log(rules);
};

validate();
dka(actualData);

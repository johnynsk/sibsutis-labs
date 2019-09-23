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
    ['--non-terminal-symbols'],
    {
        help: 'a non-terminal symbols',
        required: true
    }
);
parser.addArgument(
    ['--terminal-symbols'],
    {
        help: 'a terminal symbols',
        required: true
    }
);
parser.addArgument(
    ['--target-symbol'],
    {
        help: 'the target symbol',
        required: true
    }
);
parser.addArgument(
    ['--null-symbol'],
    {
        help: 'the empty chain symbol',
        required: true
    }
);
parser.addArgument(
    ['--min-length'],
    {
        help: 'a minimal chain length',
        defaultValue: 0
    }
);
parser.addArgument(
    ['--max-length'],
    {
        help: 'a maximal chain length',
        defaultValue: 2
    }
);
parser.addArgument(
    ['--output-plan'],
    {
        help: 'the output plan',
        choices: [LEFT_ALIGNED, RIGHT_ALIGNED]
    }
);
parser.addArgument(
    ['--rules'],
    {
        help: 'the rules list, separated by the CRLF string',
        // required: true
    }
);

try {
    var args2 = parser.parseArgs();
} catch (e) {
    parser.printHelp();
}

const nonTeminalSymbols = args2.non_terminal_symbols;
const terminalSymbols = args2.terminal_symbols;
const targetSymbol = args2.target_symbol;
const nullSymbol = args2.null_symbol;
const minLength = args2.min_length;
const maxLength = args2.max_length;
const outputPlan = args2.output_plan;
/*args2.rules = `S->T|+T|-T
T->F|TF
F->0|1|2|3|4|5|6|7|8|9`;
*/
const rawRules = args2.rules.split("\n");

let rules = [];
let depth = 15;
let quit = false;
let output = [];

let recurse = function (targetSymbol, depth) {
    // console.debug('targetSymbol', targetSymbol, 'depth', depth);
    let increment, I, position, length, foundTerminalSymbols; // Integer;

    if (quit || depth < 0) {
        return;
    }

    length = targetSymbol.length;
    foundTerminalSymbols = 0;
    for (let i in targetSymbol) {
        if (nonTeminalSymbols.indexOf(targetSymbol[I]) >= 0) {
            foundTerminalSymbols++;
        }
    }

    if (length - foundTerminalSymbols - 1 >= maxLength) {
        return;
    }

    if (outputPlan === RIGHT_ALIGNED) {
        position = length - 1;
        increment = -1;
    } else {
        position = 0;
        increment = 1;
    }

    for (let i = position; i >= 0 && i < length; i += increment) {
        let symbol = targetSymbol[parseInt(i)];
        if (nonTeminalSymbols.indexOf(symbol) == -1) {
            continue;
        }

        let suitableRules = rules[symbol];
        suitableRules.forEach(product => {
            let newTargetSymbol = targetSymbol.substr(0, parseInt(i));

            if (product != nullSymbol) {
                newTargetSymbol += product;
            }

            newTargetSymbol += targetSymbol.substr(parseInt(i) + 1);
            recurse(newTargetSymbol, depth - 1);
        });

        return;
    }

    if (length < minLength || length > maxLength) {
        return;
    }

    if (targetSymbol.length === 0) {
        targetSymbol = nullSymbol;
    }

    if (output.indexOf(targetSymbol) === -1) {
        output.push(targetSymbol);
        console.log(targetSymbol);
    }
};

let validate = function () {
    if (nullSymbol === '|') {
        throw "You have to not use the '|' symbol in as the null_symbol.";
    }

    if (nonTeminalSymbols.indexOf('|') >= 0) {
        throw "You have to not use the '|' symbol in as a non-terminal symbol.";
    }

    if (targetSymbol.indexOf('|') >= 0) {
        throw "You have to not use the '|' symbol in as a terminal symbol.";
    }

    for (let i in nonTeminalSymbols) {
        for (let j in nonTeminalSymbols) {
            if (j > i && nonTeminalSymbols[i] === nonTeminalSymbols[j]) {
                throw `The non-terminal symbol '${nonTeminalSymbols[i]}' was duplicated. You have to use only unique symbols as a non-terminal symbol.`
            }
        }

        if (terminalSymbols.indexOf(nonTeminalSymbols[i]) >= 0) {
            throw `The non-terminal symbol '${nonTeminalSymbols[i]}' was used both as terminal symbol. You have to use only unique symbols as both a terminal and non-terminal.`
        }
    }

    if (nonTeminalSymbols.indexOf(targetSymbol) === -1) {
        throw `The target '${targetSymbol}' symbol should be defined as non-terminal symbol.`
    }

    if (nonTeminalSymbols.indexOf(nullSymbol) !== -1) {
        throw `You have to not use the null '${nullSymbol}' symbol in non-terminal symbols.`
    }

    if (terminalSymbols.indexOf(nullSymbol) !== -1) {
        throw `You have to not use the null '${nullSymbol}' symbol in terminal symbols.`
    }
};

let parseRules = function(rawRuleList) {
    for (let i in rawRuleList) {
        let rule = rawRuleList[i];

        if (rule.length === 0) {
            continue;
        }

        if (nonTeminalSymbols.indexOf(rule[0]) === -1) {
            throw `You have to use only non-terminal symbols as predicate in a rule #${i}: "${rule}"`;
        }

        if (rule.indexOf('->') !== 1) {
            throw `You must use arrow symbol '->' in the first position after predicate in the rule #${i}: "${rule}".`;
        }

        let value = rule.substr(3);
        let predicate = rule.substr(0, 1);

        if (value.length === 0) {
            throw `You should define rule productions in the rule #${i}: "${rule}"`
        }

        if (typeof rules[predicate] == 'undefined') {
            rules[predicate] = [];
        }

        let productions = value.split('|')
        for (let j in productions) {
            let product = productions[j];
            if (product.length === 0) {
                throw `You have to use null element as empty production for the rule #${i}: "${rule}". Do not use empty rows`;
            }

            if (product.indexOf(nullSymbol) >= 0 && product.length > nullSymbol.length) {
                throw `You have to use only one null parameter without any other symbols in the rule #${i}: "${rule}"`;
            }

            for (let k in product) {
                if (terminalSymbols.indexOf(product[k]) === -1 && nonTeminalSymbols.indexOf(product[k]) === -1) {
                    throw `Unknown symbol ${j} ${product} '${product[k]}' was used in the rule #${i} : "${rule}". You must use only terminal and non-terminal symbols`;
                }
            }

            rules[predicate].push(product);
        }
    }
};
validate();
parseRules(rawRules);
recurse(targetSymbol, 15);
console.log(output);

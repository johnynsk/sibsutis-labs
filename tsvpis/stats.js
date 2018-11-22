'use strict';
let {clone} = require("underscore")

class Stats {
    compare () {
        this.state.compares++;
        return this;
    }

    swap() {
        this.state.swaps++;
        return this;
    }

    iterate() {
        this.state.iterations++;
        return this;
    }

    access(count) {
        if (typeof count == 'undefined') {
            this.state.accesses++;
            return;
        }

        this.state.accesses += count;
        return this;
    }

    custom () {
        return {
            compares: this.state.compares,
            swaps: this.state.swaps,
            iterations: this.state.iterations,
            accesses: this.state.accesses
        };
    }

    constructor () {
        this.state = {
            compares: 0,
            swaps: 0,
            iterations: 0,
            accesses: 0,
        };
    }
};

Stats.prototype.state = {
    compares: 0,
    swaps: 0,
    iterations: 0,
    accesses: 0
};

module.exports = Stats;

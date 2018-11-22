'use strict';
const {clone} = require('underscore');
class Result {
    constructor(result, stats) {
        this.result = clone(result);
        this.stats = clone(stats);
    };

    getResult () {
        return this.result;
    }

    getStats() {
        return this.stats;
    }
}

Result.prototype.result = null;
Result.prototype.stats = null;

module.exports = Result;

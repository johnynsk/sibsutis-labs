'use strict';
let Stats = require('./stats')
let {clone} = require('underscore')

class MergeStats extends Stats {
    constructor() {
        super();
        this.logs = [];
    }

    log(level, message) {
        if (Object.keys(this.logs).indexOf(level.toString()) == -1) {
            this.logs[level] = [];
        }

        this.logs[level][this.logs[level].length] = clone(message);
    }
}

MergeStats.prototype.logs = [];

module.exports = MergeStats;

'use strict';

let init = (length, range) => {
    let result = []
    for (let i = 0; i < length; i++) {
        result.push((Math.random() * 2 * range - range))
    }
    return result
}

module.exports = init;

let solver = function* (bounds, weights, steps = 100) {
    let result = {steps: [], total: 0};

    for (let step = 0; step < steps; step++) {
        let strategies = [];
        let values = [];

        for(player in bounds) {
            values[player] = Math.random()
            strategies[player] = values[player] >= bounds[player] ? 1 : 0;
        }

        let win = weights[strategies[0]][strategies[1]];
        result.total += win;
        result.steps.push({strategies: strategies, win: win, values: values});
        yield result;
    }

    return result;
}

module.exports = solver;

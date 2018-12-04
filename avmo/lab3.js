let {cloneDeep} = require('lodash')

let solution = () => {
    let inBounds, fx, gx, g1x, f1x, accuracy = 0.0001, alpha = 0, lambda = 0.001;
    let alphas = [0];
    let fHit = Infinity;
    let result = {point: {current: null, next: null}, inBounds: true, alpha: 0, gX:null, fX: null, gN: null, fN: null, step: 0};

    let solver = function* (X, iterations) {
        let step = 0;
        let reached = false;
        let fPrev = Infinity;
        result.point.current = X;

        do {
            let next = cloneDeep(X).map(
                (x, j) => {
                    return Math.max(
                    0,
                    x + lambda * (f1x[j](x) + alpha * g1x[j](x))
                )})

            result.point.next = next;
            let gN = gx(next)
            let inBounds = gN >= 0;

            if (inBounds) {
                let fN = fx(next)
                let diff = Math.abs(fN - fPrev);
                result.accuracy = diff;
                result.fN = fN

                if (diff <= accuracy) {
                    reached = true;
                }

                alpha = 0
                fPrev = fN;
            } else {
                alpha = Math.max(0, alphas.slice(-1) - accuracy * gN)

                if (alpha != 0) {
                    alphas.push(alpha)
                }
            }

            result.inBounds = inBounds;
            result.gN = gN;
            result.step = step + 1;
            result.alpha = alpha;
            yield result;
            X = next;
            result.point.current = X;
            step++;
        } while (!reached && (typeof iterations == 'undefined' || step < iterations));

        return result;
    }

    let that = {
        perform: solver,
        setFX: (_fx) => {fx = _fx; return that},
        setGradFx: (_f1x) => {f1x = _f1x; return that},
        setGX: (_gx) => {gx = _gx; return that},
        setGradGx: (_g1x) => {g1x = _g1x; return that},
        setInBounds: (_bounds) => {inBounds = _bounds; return that},
        setAccuracy: (_accuracy) => {accuracy = _accuracy; return that},
        setLambda: (_lamda) => {lambda = _lambda; return that}
    }

    return that;
}

module.exports = solution;

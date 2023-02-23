let print = (input, pos, len) => {
    console.log("\x1b[33mv len | pos > ")
    let row = "-\t";
    for (let i = 0; i < input.length; i++) {
        row += i + "\t";
    }
    row += "\x1b[0m";
    console.log(row);

    for (let i = 0; i < input.length; i++) {
        let row = "\x1b[33m" + i + "\x1b[0m\t";
        for (let j = 0; j < input[i].length; j++) {
            let text = (input[i][j].path_length == Infinity ? '∞' : input[i][j].path_length);
            if (j == pos) {
                text = "\x1b[41m" + text + "\x1b[0m";
            }
            row = row + text + '\t';
        }

        console.log(row);
    }
}


let frog = (lengths) => {
    let N = lengths[lengths.length - 1];
    console.log('lengths', lengths);
    let a = [];
    let pos = 0;
    let D = [];


    for (let i = 0; i <= N; i++) {
        D[i] = [];
        for (let j = 0; j <= N; j++) {
            D[i][j] = {i: i, j: j, path_length: Infinity, path: []};
        }
    }
    D[0][0].path_length = 0;
    D[0][0].path = [0];

    let len = 0;
    lengths.forEach((pos, index) => {
        if (pos == 0) {
            return;
        }

        for (let j = 1; j < N; j++) {
            if (pos - j < 0) {
                continue;
            }

            // console.log(`calculating for D[${pos},${j}], pos = ${pos}, len = ${j}`);
            
            let scanValues = [];
            for (let k = j - 1; k <= j + 1; k++) {
                scanValues.push(D[k][pos-j]);
            }

            scanValues.sort((a, b) => a.path_length - b.path_length);
            let min = scanValues.shift();

            // console.log(`found min `, min);

            if (min.j < j) {
                len++;
            } else if (min.j > j) {
                len--;
            }

            D[j][pos].path_length = min.path_length + 1;
            D[j][pos].path = [].concat(min.path);
            D[j][pos].path.push(pos);
        }

        print(D, pos, len);
    })

    let minValue = Infinity;
    let min = [];

    for (let j = 0; j <= N; j++) {
        if (minValue > D[j][N].path_length) {
            minValue = D[j][N].path_length;
            
            min = D[j][N];
        }
    }
    
    return min;
}


module.exports = frog;
const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("Введите число n: ", (nInput) => {
    rl.question("Введите число x: ", (xInput) => {
        rl.question("Введите число y: ", (yInput) => {
            const n = parseInt(nInput);
            const x = parseInt(xInput);
            const y = parseInt(yInput);
            
            if (isNaN(n) || isNaN(x) || isNaN(y) || n <= 0 || x <= 0 || y <= 0) {
                console.log("Пожалуйста, введите положительные ненулевые числа.");
            } else {
                const result = n % x === 0 && n % y === 0;
                console.log(`n = ${n}, x = ${x}, y = ${y} => ${result}`);
            }
            rl.close();
        });
    });
});

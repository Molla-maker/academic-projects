const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("Введите целое число: ", (numInput) => {
    const num = parseInt(numInput);
    
    if (isNaN(num) || num < 0) {
        console.log("Пожалуйста, введите неотрицательное целое число.");
    } else {
        for (let i = 0; i <= num; i++) {
            if (i % 5 === 0) {
                console.log(`${i} fizz buzz`);
            } else if (i % 2 === 0) {
                console.log(`${i} buzz`);
            } else {
                console.log(`${i} fizz`);
            }
        }
    }
    rl.close();
});
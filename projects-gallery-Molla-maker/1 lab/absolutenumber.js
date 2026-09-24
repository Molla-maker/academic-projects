const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function absValue(x) {
    return x < 0 ? -x : x;
}

rl.question("Введите число: ", (input) => {
    const number = parseFloat(input);
    
    if (isNaN(number)) {
        console.log("Пожалуйста, введите корректное число.");
    } else {
        console.log(`Абсолютное значение: ${absValue(number)}`);
    }
    rl.close();
});
const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function randomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

rl.question("Введите минимальное значение: ", (minInput) => {
    rl.question("Введите максимальное значение: ", (maxInput) => {
        const min = parseInt(minInput);
        const max = parseInt(maxInput);
        
        if (isNaN(min) || isNaN(max) || min > max) {
            console.log("Пожалуйста, введите корректные числовые значения (min должно быть меньше или равно max). ");
        } else {
            console.log(`Случайное число: ${randomNumber(min, max)}`);
        }
        rl.close();
    });
});

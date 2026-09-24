const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function randomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function sampleArray(array, count) {
    const result = [];
    for (let i = 0; i < count; i++) {
        const randomIndex = randomNumber(0, array.length - 1);
        result.push(array[randomIndex]);
    }
    return result;
}

rl.question("Введите массив чисел через запятую: ", (arrayInput) => {
    rl.question("Введите количество случайных значений: ", (countInput) => {
        const array = arrayInput.split(",").map(num => parseFloat(num.trim()));
        const count = parseInt(countInput);
        
        if (array.some(isNaN) || isNaN(count) || count <= 0) {
            console.log("Пожалуйста, введите корректные числовые значения.");
        } else {
            console.log(`Случайные значения: ${sampleArray(array, count)}`);
        }
        rl.close();
    });
});

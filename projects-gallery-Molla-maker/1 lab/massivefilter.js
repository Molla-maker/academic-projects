const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function myFilterArray(array, filterFunction) {
    return array.filter(filterFunction);
}

function minLengthFilter(str, minLength) {
    return str.length >= minLength;
}

function isDivisibleBy(num, divisor) {
    return num % divisor === 0;
}

rl.question("Введите массив элементов через запятую: ", (arrayInput) => {
    rl.question("Выберите тип фильтрации (length/divisible): ", (filterType) => {
        if (filterType === "length") {
            rl.question("Введите минимальную длину строки: ", (minLengthInput) => {
                const array = arrayInput.split(",").map(str => str.trim());
                const minLength = parseInt(minLengthInput);
                if (isNaN(minLength)) {
                    console.log("Пожалуйста, введите корректное число.");
                } else {
                    console.log(`Отфильтрованный массив: ${myFilterArray(array, str => minLengthFilter(str, minLength))}`);
                }
                rl.close();
            });
        } else if (filterType === "divisible") {
            rl.question("Введите число для проверки деления без остатка: ", (divisorInput) => {
                const array = arrayInput.split(",").map(num => parseFloat(num.trim())).filter(num => !isNaN(num));
                const divisor = parseInt(divisorInput);
                if (isNaN(divisor)) {
                    console.log("Пожалуйста, введите корректное число.");
                } else {
                    console.log(`Отфильтрованный массив: ${myFilterArray(array, num => isDivisibleBy(num, divisor))}`);
                }
                rl.close();
            });
        } else {
            console.log("Некорректный выбор фильтрации.");
            rl.close();
        }
    });
});
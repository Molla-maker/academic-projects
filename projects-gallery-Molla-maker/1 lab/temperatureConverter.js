const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function convertTemperature(temperature, direction) {
    let result;

    if (direction === "toC") {
        result = (temperature - 32) * 5 / 9;
        return `${result.toFixed(1)} C`;
    } else if (direction === "toF") {
        result = (temperature * 9 / 5) + 32;
        return `${result.toFixed(1)} F`;
    } else {
        return "Неверное направление преобразования";
    }
}

// Запрос данных у пользователя
rl.question("Введите температуру: ", (tempInput) => {
    const temperature = parseFloat(tempInput);

    rl.question("Введите направление преобразования (toC или toF): ", (direction) => {
        console.log(convertTemperature(temperature, direction));
        rl.close();
    });
});

const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function countSandwiches(bread, cheese) {
    if (bread < 2 || cheese < 1) {
        return 0; // Недостаточно ингредиентов для хотя бы одного сэндвича
    }
    return Math.floor(Math.min(bread / 2, cheese));
}

rl.question("Введите количество ломтиков хлеба: ", (breadInput) => {
    rl.question("Введите количество ломтиков сыра: ", (cheeseInput) => {
        const bread = parseInt(breadInput);
        const cheese = parseInt(cheeseInput);
        
        if (isNaN(bread) || isNaN(cheese) || bread < 0 || cheese < 0) {
            console.log("Пожалуйста, введите корректные неотрицательные числа.");
        } else {
            console.log(`Максимально возможное количество сэндвичей: ${countSandwiches(bread, cheese)}`);
        }
        rl.close();
    });
});
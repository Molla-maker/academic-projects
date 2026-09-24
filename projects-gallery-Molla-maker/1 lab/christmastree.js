const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("Введите количество уровней елки: ", (numInput) => {
    const num = parseInt(numInput);
    
    if (isNaN(num) || num <= 0) {
        console.log("Пожалуйста, введите положительное целое число.");
    } else {
        let tree = "";
        for (let i = 1; i <= num; i++) {
            tree += (i % 2 === 1 ? "*" : "#").repeat(i) + "\n";
        }
        tree += "||";
        console.log(tree);
    }
    rl.close();
});
const readline = require("readline");

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

function isTriangleValid(a, b, c) {
    return a + b > c && a + c > b && b + c > a;
}

function calculateTriangleProperties(a, b, c) {
    const perimeter = a + b + c;
    const s = perimeter / 2;
    const area = Math.sqrt(s * (s - a) * (s - b) * (s - c));
    const ratio = perimeter / area;
    
    console.log("Треугольник существует");
    console.log(`Периметр = ${perimeter}`);
    console.log(`Площадь = ${area.toFixed(2)}`);
    console.log(`Соотношение = ${ratio.toFixed(2)}`);
}

rl.question("Введите первую сторону треугольника: ", (aInput) => {
    rl.question("Введите вторую сторону треугольника: ", (bInput) => {
        rl.question("Введите третью сторону треугольника: ", (cInput) => {
            const a = parseFloat(aInput);
            const b = parseFloat(bInput);
            const c = parseFloat(cInput);
            
            if (isTriangleValid(a, b, c)) {
                calculateTriangleProperties(a, b, c);
            } else {
                console.log("Треугольника не существует");
            }
            rl.close(); // Закрываем ввод после обработки
        });
    });
});
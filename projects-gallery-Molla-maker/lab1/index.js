// Function to convert temperature
function convertTemperature(value, direction) {
    if (direction === 'toC') {
        return `${Math.round((value - 32) * 5/9)} C`;
    } else if (direction === 'toF') {
        return `${Math.round(value * 9/5 + 32)} F`;
    }
    return 'Invalid direction';
}

// Triangle calculations
function triangleCalculations(a, b, c) {
    if (a + b > c && a + c > b && b + c > a) {
        const perimeter = a + b + c;
        const p = perimeter / 2;
        const area = Math.sqrt(p * (p - a) * (p - b) * (p - c));
        const ratio = perimeter / area;
        
        console.log('треугольник существует');
        console.log(`периметр = ${perimeter}`);
        console.log(`Площадь = ${area}`);
        console.log(`Соотношение = ${ratio}`);
    } else {
        console.log('треугольника не существует');
    }
}

// Fizz-Buzz
function fizzBuzz(n) {
    for (let i = 0; i <= n; i++) {
        let output = '';
        if (i % 2 === 0) output += 'buzz';
        if (i % 2 !== 0) output += 'fizz';
        if (i % 5 === 0) output = 'fizz buzz';
        console.log(`${i} ${output}`);
    }
}

// Christmas tree
function createTree(height) {
    let tree = '';
    for (let i = 1; i <= height; i++) {
        const symbol = i % 2 === 0 ? '#' : '*';
        tree += symbol.repeat(i) + '\n';
    }
    tree += '||';
    return tree;
}

// Division check
function checkDivision(n, x, y) {
    return n % x === 0 && n % y === 0;
}

// Sandwich counter
function countSandwiches(ingredients) {
    const breadPairs = Math.floor(ingredients.bread / 2);
    return Math.min(breadPairs, ingredients.cheese);
}

// Absolute value
function absValue(x) {
    return x < 0 ? -x : x;
}

// Random number generator
function randomNumber(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Array sampling
function sampleArray(array, count) {
    const result = [];
    for (let i = 0; i < count; i++) {
        const randomIndex = randomNumber(0, array.length - 1);
        result.push(array[randomIndex]);
    }
    return result;
}

// Custom filter function
function myFilterArray(array, filterFn) {
    const result = [];
    for (const item of array) {
        if (filterFn(item)) {
            result.push(item);
        }
    }
    return result;
}

// Test cases
console.log('Temperature conversion:');
console.log(convertTemperature(32, 'toC')); // '0 C'
console.log(convertTemperature(10, 'toF')); // '50 F'

console.log('\nTriangle calculations:');
triangleCalculations(3, 4, 5);

console.log('\nFizz-Buzz:');
fizzBuzz(5);

console.log('\nChristmas tree:');
console.log(createTree(12));

console.log('\nDivision check:');
console.log(`n = 3, x = 1, y = 3 => ${checkDivision(3, 1, 3)}`);
console.log(`n = 12, x = 2, y = 6 => ${checkDivision(12, 2, 6)}`);
console.log(`n = 100, x = 5, y = 3 => ${checkDivision(100, 5, 3)}`);
console.log(`n = 12, x = 7, y = 5 => ${checkDivision(12, 7, 5)}`);

console.log('\nSandwich counter:');
console.log(countSandwiches({bread: 5, cheese: 6})); // 2

console.log('\nAbsolute value:');
console.log(absValue(-2)); // 2
console.log(absValue(100)); // 100
console.log(absValue(0)); // 0

console.log('\nRandom number:');
console.log(randomNumber(0, 10));
console.log(randomNumber(-10, 10));

console.log('\nArray sampling:');
console.log(sampleArray([1, 2, 3, 4], 2));
console.log(sampleArray([1, 2, 3, 4], 3));

console.log('\nCustom filter:');
function isFirstV(name) {
    return name.startsWith('V');
}
console.log(myFilterArray(['Short', 'VeryLong'], isFirstV)); // ['VeryLong'] 
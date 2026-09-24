// tasks.js

export function calculateSquareRoot(number) {
    if (typeof number !== 'number' || isNaN(number)) {
      throw new Error("Введено не число");
    }
  
    if (number < 0) {
      throw new Error("Число не может быть отрицательным");
    }
  
    return Math.sqrt(number);
  }
  
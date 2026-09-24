// callbacks.js

export function createCounter() {
    let count = 0;
  
    return function () {
      count++;
      return count;
    };
  }
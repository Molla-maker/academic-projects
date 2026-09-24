// logger.js
export function periodicLogger(message, intervalMs) {
    let count = 0;
    const timerId = setInterval(() => {
      console.log(`[Логгер]: ${message}`);
      count++;
    }, intervalMs);
  
    // Возвращаем функцию остановки
    return function stopLogger() {
      clearInterval(timerId);
      console.log(`[Логгер остановлен] Интервалов прошло: ${count}`);
    };
  }
  
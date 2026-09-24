// userData.js

/**
 * Имитация асинхронного получения данных пользователя.
 * @param {number} userId - Числовой идентификатор пользователя
 * @param {Function} callback - Функция обратного вызова (err, userData)
 */
export async function getUserData(userId, callback) {
    if (typeof userId !== 'number' || isNaN(userId)) {
      return callback(new Error('userId должен быть числом'), null);
    }
  
    // Имитируем задержку 1 секунда
    setTimeout(() => {
      const success = Math.random() < 0.5;
  
      if (success) {
        const userData = {
          id: userId,
          name: `User_${userId}`,
          email: `user${userId}@example.com`,
        };
        callback(null, userData);
      } else {
        callback(new Error('Ошибка при получении данных пользователя'), null);
      }
    }, 1000);
  }
  
  
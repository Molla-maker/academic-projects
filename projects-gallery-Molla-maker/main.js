import readline from 'readline';
import { calculateSquareRoot } from './tasks.js';
import { createCounter } from './callbacks.js';
import { periodicLogger } from './logger.js';
import { getUserData } from './userData.js';
import { sendEmail } from './emailSender.js';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const counters = {};

function showMenu() {
  console.log('\n===== Главное меню =====');
  console.log('1. Вычислить квадратный корень');
  console.log('2. Создать/использовать счётчики');
  console.log('3. Запустить логгер');
  console.log('4. Получить данные пользователя');
  console.log('5. Отправить письмо');
  console.log('6. Выход');

  rl.question('Выберите действие: ', (choice) => {
    switch (choice.trim()) {
      case '1':
        handleSquareRoot();
        break;
      case '2':
        counterMenu();
        break;
      case '3':
        handleLogger();
        break;
      case '4':
        handleUserData();
        break;
      case '5':
        handleSendEmail();
        break;
      case '6':
        console.log('До свидания!');
        rl.close();
        break;
      default:
        console.log('Неверный выбор.');
        showMenu();
    }
  });
}

function handleSquareRoot() {
  rl.question('\nВведите число для извлечения квадратного корня (или "назад"): ', (input) => {
    if (input.trim().toLowerCase() === 'назад') {
      showMenu();
      return;
    }

    const number = Number(input);
    try {
      const result = calculateSquareRoot(number);
      console.log(`Корень из ${number} равен ${result}`);
    } catch (error) {
      console.error(`Ошибка: ${error.message}`);
    }

    handleSquareRoot();
  });
}

function counterMenu() {
  console.log('\n===== Меню счётчиков =====');
  console.log('1. Создать счётчик');
  console.log('2. Использовать счётчик');
  console.log('3. Назад');

  rl.question('Выберите действие: ', (choice) => {
    switch (choice.trim()) {
      case '1':
        createNewCounter();
        break;
      case '2':
        useExistingCounter();
        break;
      case '3':
        showMenu();
        break;
      default:
        console.log('Неверный выбор.');
        counterMenu();
    }
  });
}

function createNewCounter() {
  rl.question('\nВведите имя для нового счётчика: ', (name) => {
    if (name in counters) {
      console.log(`Счётчик с именем "${name}" уже существует.`);
    } else {
      counters[name] = createCounter();
      console.log(`Счётчик "${name}" создан.`);
    }
    counterMenu();
  });
}

function useExistingCounter() {
  const names = Object.keys(counters);
  if (names.length === 0) {
    console.log('Нет созданных счётчиков.');
    return counterMenu();
  }

  console.log('\nДоступные счётчики:', names.join(', '));
  rl.question('Введите имя счётчика для увеличения (или "назад"): ', (name) => {
    if (name === 'назад') {
      return counterMenu();
    }

    if (!(name in counters)) {
      console.log(`Счётчика "${name}" не существует.`);
    } else {
      const value = counters[name]();
      console.log(`Счётчик "${name}" → ${value}`);
    }

    useExistingCounter();
  });
}

function handleLogger() {
  rl.question('\nВведите сообщение для логгера: ', (msg) => {
    rl.question('Введите интервал в миллисекундах: ', (intervalStr) => {
      const interval = parseInt(intervalStr);
      if (isNaN(interval) || interval <= 0) {
        console.log('Некорректный интервал.');
        return showMenu();
      }

      const stop = periodicLogger(msg, interval);

      setTimeout(() => {
        stop(); // остановка логгера
        showMenu();
      }, interval * 5); // остановка через 5 интервалов
    });
  });
}

function getUserDataAsync(userId) {
  return new Promise((resolve, reject) => {
    getUserData(userId, (err, data) => {
      if (err) reject(err);
      else resolve(data);
    });
  });
}

async function tryFetchUserData(userId, retries = 3) {
  let lastError;
  for (let attempt = 1; attempt <= retries; attempt++) {
    try {
      console.log(`🔍 Попытка ${attempt}...`);
      const user = await getUserDataAsync(userId);
      return user;
    } catch (err) {
      lastError = err;
      console.warn(`⚠️ Попытка ${attempt} не удалась: ${err.message}`);
    }
  }
  throw lastError;
}

async function handleUserData() {
  rl.question('\nВведите ID пользователя (или "назад"): ', async (input) => {
    const trimmed = input.trim().toLowerCase();

    if (trimmed === 'назад') {
      showMenu();
      return;
    }

    const userId = Number(input);

    if (isNaN(userId)) {
      console.log('❌ ID должен быть числом!');
      return handleUserData();
    }

    try {
      const userData = await tryFetchUserData(userId, 3);
      console.log('✅ Данные пользователя:', userData);
    } catch (error) {
      console.error('❌ Не удалось получить данные:', error.message);
    }

    handleUserData();
  });
}

function handleSendEmail() {
  const emailData = {};

  rl.question('\nВведите email получателя: ', (email) => {
    emailData.emailAddress = email.trim();

    rl.question('Введите тему письма (можно пропустить): ', (subject) => {
      emailData.subject = subject.trim();

      rl.question('Введите текст письма (можно пропустить): ', (message) => {
        emailData.message = message.trim();

        console.log('📨 Отправка письма...');

        sendEmail(emailData, (err, result) => {
          if (err) {
            console.error(`❌ Ошибка: ${err.message}`);
          } else {
            console.log(`✅ ${result}`);
          }

          showMenu();
        });
      });
    });
  });
}

// Запуск
showMenu();

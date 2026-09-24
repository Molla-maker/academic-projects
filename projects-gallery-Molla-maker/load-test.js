import autocannon from 'autocannon';
import { createWriteStream } from 'fs';

const BASE_URL = 'http://localhost:3001';

// Конфигурация тестов
const tests = [
    {
        name: 'GET / - Главная страница',
        url: '/',
        method: 'GET'
    },
    {
        name: 'GET /models - Список моделей',
        url: '/models',
        method: 'GET'
    },
    {
        name: 'GET /lastcomment.html - Последний комментарий',
        url: '/lastcomment.html',
        method: 'GET'
    },
    {
        name: 'POST /login - Авторизация',
        url: '/login',
        method: 'POST',
        headers: {
            'content-type': 'application/json'
        },
        body: JSON.stringify({
            username: 'testuser',
            password: 'testpass'
        })
    },
    {
        name: 'POST /register - Регистрация',
        url: '/register',
        method: 'POST',
        headers: {
            'content-type': 'application/json'
        },
        body: JSON.stringify({
            username: 'testuser',
            password: 'testpass'
        })
    }
];

// Функция для запуска теста
async function runTest(test) {
    console.log(`\nЗапуск теста: ${test.name}`);
    
    const result = await autocannon({
        url: BASE_URL + test.url,
        method: test.method,
        headers: test.headers,
        body: test.body,
        connections: 100, // Количество одновременных соединений
        duration: 10, // Длительность теста в секундах
        pipelining: 1, // Количество запросов в одном соединении
        timeout: 10 // Таймаут в секундах
    });

    // Сохраняем результаты в файл
    const reportStream = createWriteStream(`load-test-${test.name.replace(/[^a-z0-9]/gi, '_').toLowerCase()}.json`);
    reportStream.write(JSON.stringify(result, null, 2));
    reportStream.end();

    // Выводим основные метрики
    console.log(`\nРезультаты теста: ${test.name}`);
    console.log(`Среднее время ответа: ${result.latency.average} мс`);
    console.log(`Максимальное время ответа: ${result.latency.max} мс`);
    console.log(`Количество запросов в секунду: ${result.requests.average}`);
    console.log(`Количество ошибок: ${result.errors}`);
    console.log(`Количество таймаутов: ${result.timeouts}`);
}

// Запускаем все тесты последовательно
async function runAllTests() {
    console.log('Начало нагрузочного тестирования...');
    
    for (const test of tests) {
        await runTest(test);
    }
    
    console.log('\nТестирование завершено!');
}

// Запускаем тесты
runAllTests().catch(console.error); 
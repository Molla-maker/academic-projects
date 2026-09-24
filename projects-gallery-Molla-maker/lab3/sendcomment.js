import http from 'http';

const data = JSON.stringify({
  name: 'Серверный Скрипт',
  comment: 'Отправлено из Node.js!'
});

const options = {
  hostname: 'localhost',
  port: 3000,
  path: '/comments',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Content-Length': Buffer.byteLength(data)
  }
};

const req = http.request(options, res => {
  res.setEncoding('utf8');
  res.on('data', chunk => {
    console.log('Ответ:', chunk);
  });
});

req.on('error', error => {
  console.error('Ошибка:', error);
});

req.write(data);
req.end();
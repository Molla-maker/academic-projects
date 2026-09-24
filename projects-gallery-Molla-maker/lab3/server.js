import http from 'http';
import fs from 'fs';
import path from 'path';

const PORT = 3000;
const comments = [];
const stats = {};
let commentId = 1;

const contentTypes = {
  '.html': 'text/html; charset=utf-8',
  '.css': 'text/css; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8'
};

const publicDir = path.join(process.cwd(), 'public');
const files = new Map();

fs.readdirSync(publicDir).forEach(file => {
  const filePath = path.join(publicDir, file);
  const ext = path.extname(file);
  const contentType = contentTypes[ext] || 'application/octet-stream';
  const content = fs.readFileSync(filePath);
  files.set(`/${file}`, {
    body: content,
    length: Buffer.byteLength(content),
    type: contentType
  });
});

function escapeHtml(unsafe) {
  return unsafe
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}

function serveStatic(req, res) {
  let reqUrl = req.url === '/' ? '/index.html' : req.url;

  if (files.has(reqUrl)) {
    const { body, length, type } = files.get(reqUrl);
    res.writeHead(200, {
      'Content-Type': type,
      'Content-Length': length
    });
    res.end(body);
    return true;
  }
  return false;
}

async function serveTemplate(req, res) {
  if (req.url === '/lastcomment.html') {
    const filePath = path.join(process.cwd(), 'templates', 'lastcomment.html');
    try {
      await fs.promises.access(filePath);
      const raw = await fs.promises.readFile(filePath, 'utf-8');

      const last = comments.at(-1) || { name: '—', comment: '—' };
      const filled = raw
        .replace('{{name}}', escapeHtml(last.name))
        .replace('{{comment}}', escapeHtml(last.comment));

      const body = Buffer.from(filled);
      res.writeHead(200, {
        'Content-Type': 'text/html; charset=utf-8',
        'Content-Length': body.length
      });
      res.end(body);
      return true;
    } catch (e) {
      res.writeHead(500, { 'Content-Type': 'text/plain; charset=utf-8' });
      res.end('Ошибка сервера при рендеринге шаблона');
      return true;
    }
  }
  return false;
}

function serve404(res) {
  const notFound = files.get('/404.html');
  if (notFound) {
    res.writeHead(404, {
      'Content-Type': notFound.type,
      'Content-Length': notFound.length
    });
    res.end(notFound.body);
  } else {
    res.writeHead(404, { 'Content-Type': 'text/plain; charset=utf-8' });
    res.end('Страница не найдена');
  }
}

const server = http.createServer((req, res) => {
  const userAgent = req.headers['user-agent'] || 'Unknown';
  stats[userAgent] = (stats[userAgent] || 0) + 1;

  console.log(`Получен запрос: ${req.method} ${req.url}`);
  console.log(`User-Agent: ${userAgent}`);

  if (req.method === 'GET' && req.url === '/') {
    res.writeHead(200, { 
      'Content-Type': 'text/plain; charset=utf-8'
    });
    res.end('Привет! Это простой HTTP сервер.');
  } else if (req.method === 'GET' && req.url === '/comments') {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify(comments));
  } else if (req.method === 'POST' && req.url === '/comments') {
    let body = '';
    
    req.on('data', chunk => {
      body += chunk.toString();
    });

    req.on('end', () => {
      try {
        const data = JSON.parse(body);
        
        if (!data.name || !data.comment) {
          res.writeHead(400, { 'Content-Type': 'application/json' });
          res.end(JSON.stringify({ error: 'Отсутствуют обязательные поля' }));
          return;
        }

        const newComment = {
          idx: comments.length + 1,
          name: data.name,
          comment: data.comment
        };

        comments.push(newComment);
        res.writeHead(201, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify(newComment));
      } catch (error) {
        res.writeHead(400, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ error: 'Некорректный JSON' }));
      }
    });
  } else if (req.method === 'GET' && req.url === '/stats') {
    const html = `
      <!DOCTYPE html>
      <html>
      <head>
        <title>Статистика запросов</title>
        <style>
          table { border-collapse: collapse; width: 100%; }
          th, td { border: 1px solid black; padding: 8px; text-align: left; }
          th { background-color: #f2f2f2; }
        </style>
      </head>
      <body>
        <h1>Статистика запросов</h1>
        <table>
          <tr>
            <th>User-Agent</th>
            <th>Количество запросов</th>
          </tr>
          ${Object.entries(stats)
            .map(([agent, count]) => `
              <tr>
                <td>${agent}</td>
                <td>${count}</td>
              </tr>
            `).join('')}
        </table>
      </body>
      </html>
    `;
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    res.end(html);
  } else {
    res.writeHead(400, { 'Content-Type': 'application/json' });
    res.end(JSON.stringify({ error: 'Bad Request' }));
  }
});

server.listen(PORT, () => {
  console.log(`Сервер запущен на http://localhost:${PORT}`);
});

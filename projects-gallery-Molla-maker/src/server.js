import express from 'express';
import path from 'path';
import { fileURLToPath } from 'url';
import { v4 as uuidv4 } from 'uuid';
import bcrypt from 'bcrypt';
import { parse } from 'cookie';
import db from './db.js';
import authMiddleware from './middlewares/auth.middleware.js';
import * as modelsController from './controllers/models.controller.js';
import fs from 'fs';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const app = express();
const port = process.env.PORT || 3001;

// Middleware
app.use(express.static(path.join(__dirname, 'public')));
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));
app.use('/node_modules', express.static(path.join(__dirname, '..', 'node_modules')));
app.use('/three.js', express.static(path.join(__dirname, '..', 'three.js')));
app.use(express.json());

// Функция для санитизации HTML
function escapeHtml(unsafe) {
    return unsafe
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#039;");
}

// Функция для декодирования HTML-сущностей
function decodeHtml(html) {
    const txt = document.createElement("textarea");
    txt.innerHTML = html;
    return txt.value;
}

// Загрузка шаблона
async function loadTemplate(templatePath) {
    try {
        const content = await fs.promises.readFile(templatePath, 'utf-8');
        return content;
    } catch (error) {
        console.error('Error loading template:', error);
        throw error;
    }
}

// Routes
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Auth routes
app.post('/register', async (req, res) => {
    const { username, password } = req.body;

    if (!username || !password) {
        res.status(400).json({ error: 'Username and password are required' });
        return;
    }

    try {
        const hashedPassword = await bcrypt.hash(password, 10);
        
        db.run('INSERT INTO users (username, password) VALUES (?, ?)', 
            [username, hashedPassword],
            function(err) {
                if (err) {
                    res.status(400).json({ error: 'Username already exists' });
                    return;
                }

                const sessionId = uuidv4();
                db.run('INSERT INTO sessions (id, user_id) VALUES (?, ?)',
                    [sessionId, this.lastID],
                    (err) => {
                        if (err) {
                            res.status(500).json({ error: 'Error creating session' });
                            return;
                        }

                        res.setHeader('Set-Cookie', `sessionId=${sessionId}; Path=/; HttpOnly`);
                        res.status(200).json({ success: true, redirect: '/' });
                    }
                );
            }
        );
    } catch (error) {
        res.status(500).json({ error: 'Error registering user' });
    }
});

app.post('/login', async (req, res) => {
    const { username, password } = req.body;

    if (!username || !password) {
        res.status(400).json({ error: 'Username and password are required' });
        return;
    }

    db.get('SELECT * FROM users WHERE username = ?', [username], async (err, user) => {
        if (err || !user) {
            res.status(401).json({ error: 'Invalid credentials' });
            return;
        }

        const validPassword = await bcrypt.compare(password, user.password);
        if (!validPassword) {
            res.status(401).json({ error: 'Invalid credentials' });
            return;
        }

        const sessionId = uuidv4();
        db.run('INSERT INTO sessions (id, user_id) VALUES (?, ?)',
            [sessionId, user.id],
            (err) => {
                if (err) {
                    res.status(500).json({ error: 'Error creating session' });
                    return;
                }

                res.setHeader('Set-Cookie', `sessionId=${sessionId}; Path=/; HttpOnly`);
                res.status(200).json({ success: true, redirect: '/' });
            }
        );
    });
});

app.post('/logout', (req, res) => {
    const cookies = parse(req.headers.cookie || '');
    const sessionId = cookies.sessionId;

    if (sessionId) {
        db.run('DELETE FROM sessions WHERE id = ?', [sessionId]);
    }

    res.setHeader('Set-Cookie', 'sessionId=; Path=/; HttpOnly; Max-Age=0');
    res.status(200).json({ success: true, redirect: '/' });
});

// Model routes
app.get('/models/upload', authMiddleware, modelsController.getUploadForm);
app.post('/models', authMiddleware, modelsController.uploadModel);
app.get('/models', modelsController.getModels);

// Last comment route (for lab work)
app.get('/lastcomment.html', async (req, res) => {
    try {
        const templatePath = path.join(__dirname, 'templates', 'lastcomment.html');
        
        // Проверяем существование файла
        try {
            await fs.promises.access(templatePath);
        } catch (error) {
            console.error('Template file not found:', error);
            res.status(500).send('Internal Server Error');
            return;
        }

        let template = await loadTemplate(templatePath);
        
        // Get the last model as a comment
        db.get('SELECT m.*, u.username as author FROM models m JOIN users u ON m.author_id = u.id ORDER BY m.created_at DESC LIMIT 1', 
            [], 
            (err, model) => {
                if (err) {
                    console.error('Database error:', err);
                    res.status(500).send('Internal Server Error');
                    return;
                }

                if (!model) {
                    model = {
                        author: 'No models yet',
                        created_at: new Date().toLocaleDateString(),
                        description: 'Be the first to upload a model!'
                    };
                }

                // Декодируем HTML-сущности перед санитизацией
                const decodedDescription = model.description ? 
                    model.description.replace(/&#(\d+);/g, (match, dec) => String.fromCharCode(dec)) : 
                    'No description';

                template = template
                    .replace('{{ author }}', escapeHtml(model.author))
                    .replace('{{ date }}', escapeHtml(new Date(model.created_at).toLocaleDateString()))
                    .replace('{{ content }}', escapeHtml(decodedDescription));

                res.send(template);
            }
        );
    } catch (error) {
        console.error('Template error:', error);
        res.status(500).send('Internal Server Error');
    }
});

// 404 handler
app.use((req, res) => {
    res.status(404).sendFile(path.join(__dirname, 'public', '404.html'));
});

// Start server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
}); 
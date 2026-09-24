import { IncomingForm } from 'formidable';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import { v4 as uuidv4 } from 'uuid';
import db from '../db.js';

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const uploadsDir = path.join(__dirname, '../uploads');

// Ensure uploads directory exists
if (!fs.existsSync(uploadsDir)) {
  fs.mkdirSync(uploadsDir, { recursive: true });
}

const getUploadForm = (req, res) => {
  res.writeHead(200, { 'Content-Type': 'text/html' });
  res.end(`
    <!DOCTYPE html>
    <html>
      <head>
        <title>Upload 3D Model</title>
        <link rel="stylesheet" href="/styles.css">
      </head>
      <body>
        <div class="container">
          <h1>Upload 3D Model</h1>
          <form action="/models" method="POST" enctype="multipart/form-data" novalidate>
            <div class="form-group">
              <label for="name">Model Name:</label>
              <input type="text" id="name" name="name" required minlength="3" maxlength="100">
              <div class="help-text">Name must be between 3 and 100 characters</div>
            </div>
            <div class="form-group">
              <label for="description">Description:</label>
              <textarea id="description" name="description" maxlength="500"></textarea>
              <div class="help-text">Description can be up to 500 characters</div>
            </div>
            <div class="form-group">
              <label for="model">3D Model File (.stl):</label>
              <input type="file" id="model" name="model" accept=".stl" required>
              <div class="help-text">Only .stl files up to 10MB are allowed</div>
            </div>
            <button type="submit">Upload</button>
          </form>
          <a href="/" class="back-link">Back to Models</a>
        </div>
        <script src="/validate.js"></script>
      </body>
    </html>
  `);
};

const uploadModel = (req, res) => {
  const form = new IncomingForm({
    maxFileSize: 10 * 1024 * 1024, // 10MB
    filter: ({ mimetype }) => mimetype === 'application/octet-stream' || mimetype === 'application/sla'
  });
  
  form.parse(req, async (err, fields, files) => {
    if (err) {
      if (err.code === 'LIMIT_FILE_SIZE') {
        console.log('Ошибка: файл слишком большой');
        res.statusCode = 400;
        res.end('File size must be less than 10MB');
        return;
      }
      console.log('Ошибка обработки формы:', err);
      res.statusCode = 400;
      res.end('Error processing form');
      return;
    }

    // Обработка случая, если name/description пришли как массивы
    let name = fields.name;
    let description = fields.description;
    if (Array.isArray(name)) name = name[0];
    if (Array.isArray(description)) description = description[0];

    let modelFile = files.model;
    if (Array.isArray(modelFile)) modelFile = modelFile[0];

    if (!name || !modelFile) {
      console.log('Ошибка: name или modelFile отсутствует', { name, modelFile });
      res.statusCode = 400;
      res.end('Name and model file are required');
      return;
    }

    // Validate name length
    if (typeof name !== 'string' || name.length < 3 || name.length > 100) {
      console.log('Ошибка: некорректная длина name', name);
      res.statusCode = 400;
      res.end('Name must be between 3 and 100 characters');
      return;
    }

    // Validate description length
    if (description && description.length > 500) {
      console.log('Ошибка: некорректная длина description', description);
      res.statusCode = 400;
      res.end('Description must be less than 500 characters');
      return;
    }

    // Check file type
    if (!modelFile.originalFilename.endsWith('.stl')) {
      console.log('Ошибка: неподдерживаемый тип файла', modelFile.originalFilename);
      res.statusCode = 415;
      res.end('Only .stl files are supported');
      return;
    }

    // Generate unique filename
    const uniqueFilename = `${Date.now()}-${uuidv4()}.stl`;
    const newPath = path.join(uploadsDir, uniqueFilename);

    try {
      await fs.promises.copyFile(modelFile.filepath, newPath);
      
      // Save to database
      db.run(
        'INSERT INTO models (name, description, file_path, author_id) VALUES (?, ?, ?, ?)',
        [name, description || null, '/uploads/' + uniqueFilename, req.userId],
        (err) => {
          if (err) {
            // Clean up the uploaded file if database insert fails
            fs.unlink(newPath, () => {});
            console.log('Ошибка при сохранении модели в БД:', err);
            res.statusCode = 500;
            res.end('Error saving model to database');
            return;
          }

          res.statusCode = 302;
          res.setHeader('Location', '/');
          res.end();
        }
      );
    } catch (error) {
      console.log('Ошибка при сохранении файла:', error);
      res.statusCode = 500;
      res.end('Error saving file');
    }
  });
};

const getModels = (req, res) => {
  const page = parseInt(req.query.page) || 1;
  const limit = parseInt(req.query.limit) || 10;
  const offset = (page - 1) * limit;
  
  // First get total count
  db.get('SELECT COUNT(*) as total FROM models', [], (err, result) => {
    if (err) {
      res.statusCode = 500;
      res.end('Error fetching models count');
      return;
    }

    const total = result.total;
    const totalPages = Math.ceil(total / limit);

    // Then get models for current page
    db.all(
      `SELECT m.*, u.username as author_name 
       FROM models m 
       JOIN users u ON m.author_id = u.id 
       ORDER BY m.created_at DESC 
       LIMIT ? OFFSET ?`,
      [limit, offset],
      (err, models) => {
        if (err) {
          res.statusCode = 500;
          res.end('Error fetching models');
          return;
        }

        // Гарантируем, что file_path начинается с /uploads/
        models.forEach(model => {
          if (model.file_path && !model.file_path.startsWith('/uploads/')) {
            model.file_path = '/uploads/' + model.file_path.replace(/^\/uploads\//, '');
          }
        });

        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({
          models,
          pagination: {
            currentPage: page,
            totalPages,
            total,
            hasNext: page < totalPages,
            hasPrev: page > 1
          }
        }));
      }
    );
  });
};

export {
  getUploadForm,
  uploadModel,
  getModels
}; 
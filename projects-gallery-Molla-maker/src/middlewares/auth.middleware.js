import db from '../db.js';
import { parse } from 'cookie';

const authMiddleware = async (req, res, next) => {
  const cookies = parse(req.headers.cookie || '');
  const sessionId = cookies.sessionId;

  if (!sessionId) {
    res.statusCode = 403;
    res.end('Authentication required');
    return;
  }

  db.get('SELECT user_id FROM sessions WHERE id = ?', [sessionId], (err, row) => {
    if (err || !row) {
      res.statusCode = 403;
      res.end('Invalid session');
      return;
    }

    req.userId = row.user_id;
    next();
  });
};

export default authMiddleware; 
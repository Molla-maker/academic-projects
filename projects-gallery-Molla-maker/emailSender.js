// emailSender.js

/**
 * Имитирует отправку письма с валидацией и задержкой
 * @param {Object} emailObj - объект с emailAddress, subject, message
 * @param {Function} callback - (error, result)
 */
export function sendEmail(emailObj, callback) {
    const { emailAddress, subject, message } = emailObj;
  
    // Проверка email
    if (!emailAddress || typeof emailAddress !== 'string' || !emailAddress.includes('@')) {
      const error = new Error('Неверный адрес электронной почты');
      return callback(error, null);
    }
  
    // Значения по умолчанию
    const emailToSend = {
      emailAddress,
      subject: subject || 'Без темы',
      message: message || ''
    };
  
    const delay = Math.floor(Math.random() * 2000) + 500;
  
    setTimeout(() => {
      callback(null, `Письмо успешно отправлено на ${emailToSend.emailAddress}`);
    }, delay);
  }
  
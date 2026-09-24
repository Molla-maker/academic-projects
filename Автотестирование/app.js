/**
 * Приложение "Заказ доставки"
 * Поля: адрес, время, товары, сумма, комментарий
 * 
 * Правила валидации (с намеренными ошибками для тестирования):
 * - Адрес: 5-200 символов, обязательное
 * - Время: формат ЧЧ:ММ, часы 0-23, минуты 0-59
 * - Товары: минимум 1 товар (разделитель запятая), обязательное
 * - Сумма: целое число от 100 до 100000, обязательное
 * - Комментарий: необязательное, макс 500 символов
 */

document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('deliveryForm');
    const cancelButton = document.getElementById('cancelButton');
    const messageDiv = document.getElementById('message');

    form.addEventListener('submit', function(e) {
        e.preventDefault();
        validateAndSubmit();
    });

    cancelButton.addEventListener('click', function() {
        clearForm();
    });

    function clearForm() {
        document.getElementById('address').value = '';
        document.getElementById('time').value = '';
        document.getElementById('goods').value = '';
        document.getElementById('sum').value = '';
        document.getElementById('comment').value = '';
        hideMessage();
        clearInputErrors();
    }

    function hideMessage() {
        messageDiv.style.display = 'none';
        messageDiv.className = 'message';
    }

    function showMessage(text, isSuccess) {
        messageDiv.textContent = text;
        messageDiv.className = 'message ' + (isSuccess ? 'success' : 'error');
        messageDiv.style.display = 'block';
    }

    function clearInputErrors() {
        document.querySelectorAll('.input-error').forEach(el => el.classList.remove('input-error'));
    }

    function setInputError(elementId) {
        document.getElementById(elementId).classList.add('input-error');
    }

    function validateAndSubmit() {
        clearInputErrors();
        hideMessage();

        const address = document.getElementById('address').value.trim();
        const time = document.getElementById('time').value.trim();
        const goods = document.getElementById('goods').value.trim();
        const sumStr = document.getElementById('sum').value.trim();
        const comment = document.getElementById('comment').value.trim();

        const errors = [];

        // Валидация адреса: 5-200 символов
        if (address.length < 5) {
            errors.push({ field: 'Адрес доставки', message: 'Введены некорректные данные в поле ввода Адрес доставки. Вам необходимо ввести строку от 5 до 200 символов.' });
            setInputError('address');
        } else if (address.length > 200) {
            errors.push({ field: 'Адрес доставки', message: 'Введены некорректные данные в поле ввода Адрес доставки. Вам необходимо ввести строку от 5 до 200 символов.' });
            setInputError('address');
        }

        // Валидация времени: формат ЧЧ:ММ
        const timeRegex = /^(\d{1,2}):(\d{2})$/;
        const timeMatch = time.match(timeRegex);
        if (!timeMatch) {
            errors.push({ field: 'Время доставки', message: 'Введены некорректные данные в поле ввода Время доставки. Вам необходимо ввести время в формате ЧЧ:ММ (часы от 0 до 23, минуты от 0 до 59).' });
            setInputError('time');
        } else {
            const hours = parseInt(timeMatch[1], 10);
            const minutes = parseInt(timeMatch[2], 10);
            // БАГ: используется > вместо >= для минут (должно быть 0-59, но 60 тоже пройдёт)
            if (hours < 0 || hours > 23 || minutes < 0 || minutes > 60) {
                errors.push({ field: 'Время доставки', message: 'Введены некорректные данные в поле ввода Время доставки. Вам необходимо ввести время в формате ЧЧ:ММ (часы от 0 до 23, минуты от 0 до 59).' });
                setInputError('time');
            }
        }

        // Валидация товаров: минимум 1 товар
        const goodsList = goods.split(',').map(g => g.trim()).filter(g => g.length > 0);
        if (goodsList.length < 1) {
            errors.push({ field: 'Товары', message: 'Введены некорректные данные в поле ввода Товары. Вам необходимо ввести минимум один товар через запятую.' });
            setInputError('goods');
        }

        // Валидация суммы: целое число 100-100000
        const sum = parseInt(sumStr, 10);
        if (isNaN(sum) || !Number.isInteger(parseFloat(sumStr))) {
            errors.push({ field: 'Сумма заказа', message: 'Введены некорректные данные в поле ввода Сумма заказа. Вам необходимо ввести целое число в диапазоне от 100 до 100000.' });
            setInputError('sum');
        } else {
            // БАГ: используется >= 99 вместо >= 100 (99 проходит валидацию)
            if (sum < 99 || sum > 100000) {
                errors.push({ field: 'Сумма заказа', message: 'Введены некорректные данные в поле ввода Сумма заказа. Вам необходимо ввести целое число в диапазоне от 100 до 100000.' });
                setInputError('sum');
            }
        }

        // Валидация комментария: макс 500 символов (если указан)
        if (comment.length > 500) {
            errors.push({ field: 'Комментарий', message: 'Введены некорректные данные в поле ввода Комментарий. Вам необходимо ввести не более 500 символов.' });
            setInputError('comment');
        }

        if (errors.length > 0) {
            const errorText = errors.map(e => e.message).join('\n\n');
            showMessage(errorText, false);
        } else {
            const successText = `Успешно!\n\nЗаказ доставки оформлен:\nАдрес: ${address}\nВремя: ${time}\nТовары: ${goodsList.join(', ')}\nСумма: ${sum} руб.\n${comment ? 'Комментарий: ' + comment : ''}`;
            showMessage(successText, true);
        }
    }
});

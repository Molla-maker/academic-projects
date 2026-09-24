# Приложение «Заказ доставки»

Веб-приложение для оформления заказа доставки с валидацией полей ввода.

## Запуск приложения

Откройте файл `index.html` в браузере.

## Автотесты — без Node.js (рекомендуется)

Откройте в браузере файл **`tests/run_tests.html`** и нажмите кнопку «Запустить тесты». Никаких установок не требуется.

---

## Автотесты (Node.js + Playwright)

### Установка

```bash
npm install
npx playwright install chromium
```

### Запуск

```bash
npm test
```

---

## Автотесты (Python) — альтернатива

```bash
pip install selenium pytest webdriver-manager
pytest tests/test_delivery_order.py -v
```

Требуется Google Chrome.

## Документация

- `test_cases_manual.md` — 20 тест-кейсов для ручного тестирования
- `ОТЧЕТ.md` — полный отчёт с правилами валидации и результатами тестов

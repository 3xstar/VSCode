# Тестовая документация Note Manager

## Обзор тестов

Этот документ описывает unit-тесты, написанные для приложения Note Manager.

### Структура тестов

tests/ ├── conftest.py # Фикстуры и настройка окружения ├── test_note_service.py # Unit-тесты бизнес-логики (Service Layer) ├── test_note_repository.py # Unit-тесты Repository с mocking ├── test_models.py # Тесты моделей данных └── README.md # Этот файл


## Типы тестов

### Unit-тесты Service Layer (test_note_service.py)

**Цель:** Проверка бизнес-логики без подключения к БД

**Что тестируется:**
- Валидация входных данных (заголовок, содержимое)
- Обработка граничных случаев (пустые значения, длинный текст)
- Корректность возвращаемых значений
- Взаимодействие с Repository (через Mock)

**Используемые моки:**
- `Mock(spec=NoteRepository)` — изоляция от БД
- `Mock(spec=CategoryRepository)` — изоляция от БД

### Unit-тесты Repository с mocking (test_note_repository.py)

**Цель:** Проверка логики Repository без реальной БД

**Что тестируется:**
- CRUD операции (Create, Read, Update, Delete)
- Корректность вызовов SQL (через mock курсора)
- Преобразование данных между БД и приложением

**Используемые моки:**
- `@patch('repositories.note_repository.get_connection')` — мок подключения
- Mock cursor — мок курсора БД

### Тесты моделей (test_models.py)

**Цель:** Проверка корректности моделей данных

**Что тестируется:**
- Создание объектов
- Значения полей по умолчанию
- Строковое представление (__str__)

---

## Запуск тестов

### Все тесты
```bash
pytest tests/ -v

### **Конкретный файл**

```bash
pytest tests/test_note_service.py -v
```

### **Конкретный тест**

```bash
pytest tests/test_note_service.py::TestNoteServiceValidation::test_create_note_empty_title -v
```

### **С выводом покрытия (требуется pytest-cov)**

```bash
pytest tests/ -v --cov=. --cov-report=html
```

**Фикстуры**
| Фикстура | Область | Описание |
| --- | --- | --- |
| `mock_note_repository` | function | Mock репозитория заметок |
| `mock_category_repository` | function | Mock репозитория категорий |
| `note_service` | function | Сервис с мок-репозиториями |
| `sample_note` | function | Тестовая заметка |
| `sample_category` | function | Тестовая категория |
| `list_of_notes` | function | Список тестовых заметок |
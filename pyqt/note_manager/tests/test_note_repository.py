import pytest
from unittest.mock import Mock, patch, MagicMock

# TODO: Импортируйте ваши классы
# from repositories.note_repository import NoteRepository
# from models.note import Note


class TestNoteRepositoryMocked:
    """Тесты репозитория с использованием mocking"""

    @patch('repositories.note_repository.get_connection')
    def test_get_all_notes(self, mock_get_connection):
        """
        Тест: Получение всех заметок

        TODO:
        1. Создайте мок-коннекшн и мок-курсор
        2. Установите mock_cursor.fetchall.return_value = [(1, "Title", "Content", 1, 1), ...]
        3. Вызовите repository.get_all_notes()
        4. Проверьте результат
        5. Проверьте, что get_connection был вызван
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_get_note_by_id(self, mock_get_connection):
        """
        Тест: Получение заметки по ID

        TODO:
        1. Настройте мок так, чтобы fetchone возвращал данные заметки
        2. Вызовите repository.get_note_by_id(1)
        3. Проверьте результат
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_get_note_by_id_not_found(self, mock_get_connection):
        """
        Тест: Получение несуществующей заметки

        TODO:
        1. Установите mock_cursor.fetchone.return_value = None
        2. Вызовите repository.get_note_by_id(999)
        3. Проверьте, что возвращается None
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_create_note(self, mock_get_connection):
        """
        Тест: Создание заметки

        TODO:
        1. Установите mock_cursor.fetchone.return_value = {'id': 42} или (42,)
        2. Вызовите repository.create_note(title, content, ...)
        3. Проверьте, что вернулся ID = 42
        4. Проверьте, что execute был вызван с INSERT
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_update_note(self, mock_get_connection):
        """
        Тест: Обновление заметки

        TODO:
        1. Установите mock_cursor.rowcount = 1
        2. Вызовите repository.update_note(id, title, content, ...)
        3. Проверьте результат
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_delete_note(self, mock_get_connection):
        """
        Тест: Удаление заметки

        TODO:
        1. Установите mock_cursor.rowcount = 1
        2. Вызовите repository.delete_note(id)
        3. Проверьте, что вернулся True
        """
        # Ваш код здесь
        pass

    @patch('repositories.note_repository.get_connection')
    def test_search_notes(self, mock_get_connection):
        """
        Тест: Поиск заметок

        TODO:
        1. Настройте fetchone или fetchall для возврата результатов поиска
        2. Вызовите repository.search_notes("query")
        3. Проверьте результат
        """
        # Ваш код здесь
        pass
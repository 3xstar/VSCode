import pytest
from unittest.mock import Mock

# TODO: Импортируйте ваши классы
from services.note_service import NoteService
from models.note import Note


class TestNoteServiceValidation:
    """Тесты валидации в сервисе заметок"""

    def test_create_note_empty_title(self, note_service):
        """
        Тест: Создание заметки с пустым заголовком

        TODO:
        1. Вызовите note_service.create_note("", "content", ...)
        2. Проверьте, что возвращено False / ошибка
        3. Проверьте, что сообщение содержит "заголовок" или "пуст"
        """

        result = note_service.create_note("", "content", 1,1)
        assert result is False


    def test_create_note_whitespace_title(self, note_service):
        """
        Тест: Создание заметки с пробелами в заголовке

        TODO:
        1. Вызовите note_service.create_note("   ", "content", ...)
        2. Проверьте, что это считается ошибкой
        """
        # Ваш код здесь
        result =  note_service.create_note("   ", "content", 1, 1)

        assert result is False

    def test_create_note_title_too_long(self, note_service):
        """
        Тест: Создание заметки с длинным заголовком

        TODO:
        1. Создайте строку длиной более 200 символов
        2. Вызовите note_service.create_note(long_title, ...)
        3. Проверьте, что success == False
        """
        # Ваш код здесь
        long_title = "gjiosdiofdgbhsiugbfconpdsiompf,cmuospinsumviuptmvisoevuspemicumes,,xmofdisdopuivx,moieunmvetrp,wucpiusaw.q9rаыфваошщыфошфо08шйрнцк8йпмшгываиздфпыворгшщурыа0шур9щсзуыт9щхритышгаргу"

        result = note_service.create_note(long_title, "content", 1, 1)

        assert result is False

    def test_create_note_empty_content(self, note_service):
        """
        Тест: Создание заметки с пустым содержимым

        TODO:
        1. Вызовите note_service.create_note("Title", "", ...)
        2. Проверьте результат (допускается или нет — зависит от вашей логики)
        """
        # Ваш код здесь
        result = note_service.create_note("Title", "", 1, 1)
        
        assert result is False

    def test_create_note_valid(self, note_service, mock_note_repository):
        """
        Тест: Создание корректной заметки

        TODO:
        1. Установите mock_note_repository.create.return_value = 42
        2. Вызовите note_service.create_note("Valid", "Content", ...)
        3. Проверьте, что success == True
        4. Проверьте, что метод create был вызван 1 раз
        """
        # Ваш код здесь
        mock_note_repository.create.return_value = 42
        result = note_service.create_note("Valid", "Content", 1, 1)
        assert result is True

        mock_note_repository.create.assert_called_once_with(
            title = "Valid",
            content = "Content",
            category_id = 1,
            user_id = 1
        )
        

    def test_create_note_trims_whitespace(self, note_service, mock_note_repository):
        """
        Тест: Создание заметки обрезает пробелы

        TODO:
        1. Вызовите create_note("  Title  ", "  Content  ", ...)
        2. Проверьте, что в репозиторий переданы данные без пробелов
        """
        # Ваш код здесь
        result = note_service.create_note("  Title  ", "  Content  ", 1, 1)
        mock_note_repository.create.assert_called_once_with(
            title = "Title",
            content = "Content",
            category_id = 1,
            user_id = 1
        )


class TestNoteServiceUpdate:
    """Тесты обновления заметок"""

    def test_update_note_invalid_id(self, note_service):
        """
        Тест: Обновление с некорректным ID

        TODO:
        1. Вызовите note_service.update_note(-5, ...) или update_note(0, ...)
        2. Проверьте, что success == False
        """
        result = note_service.update_note(0, "Title", "Content", 1, 1)
        assert result is False

    def test_update_note_not_found(self, note_service, mock_note_repository):
        """
        Тест: Обновление несуществующей заметки

        TODO:
        1. Установите mock_note_repository.get_by_id.return_value = None
        2. Вызовите note_service.update_note(999, ...)
        3. Проверьте, что success == False
        """
        # Ваш код здесь
        mock_note_repository.get_by_id.return_value = None
        result = note_service.update_note(999, "Title", "Content", 1, 1)
        assert result is False

    def test_update_note_valid(self, note_service, mock_note_repository):
        """
        Тест: Успешное обновление заметки

        TODO:
        1. Создайте мок-заметку для get_by_id
        2. Установите mock_note_repository.update.return_value = True
        3. Вызовите note_service.update_note(1, "New Title", ...)
        4. Проверьте, что success == True
        """
        # Ваш код здесь
        mock_note_repository.get_by_id.return_value = sample_note
        mock_note_repository.update.return_value = True

        note_service.update_note(1, "Title", "Content", 1, 1)

        result = note_service.update_note(1, "New Title", "New Content", 1, 1)
        assert result is True

        mock_note_repository.update.assert_called_once()


class TestNoteServiceDelete:
    """Тесты удаления заметок"""

    def test_delete_note_invalid_id(self, note_service):
        """Тест: Удаление с некорректным ID"""
        # Ваш код здесь
        result = note_service.remove_note(-1)
        assert result is False

    def test_delete_note_not_found(self, note_service, mock_note_repository):
        """Тест: Удаление несуществующей заметки"""
        # Ваш код здесь
        mock_note_repository.get_by_id.return_value = None

        result = note_service.remove_note(5)
        assert result is False

    def test_delete_note_success(self, note_service, mock_note_repository):
        """Тест: Успешное удаление"""
        # Ваш код здесь
        mock_note_repository.get_by_id.return_value = Mock(id=1)
        mock_note_repository.delete.return_value = True

        result = note_service.remove_note(1)
        assert result is True


        mock_note_repository.delete.assert_called_once_with(1)


class TestNoteServiceSearch:
    """Тесты поиска заметок"""

    def test_search_notes_empty_query(self, note_service):
        """
        Тест: Поиск с пустым запросом

        TODO:
        1. Вызовите note_service.search_notes("")
        2. Проверьте, что возвращается пустой список
        """
        result = note_service.search_notes("")
        assert result == []

    def test_search_notes_with_results(self, note_service, mock_note_repository, list_of_notes):
        """
        Тест: Поиск с результатами

        TODO:
        1. Установите mock_note_repository.search.return_value = list_of_notes
        2. Вызовите note_service.search_notes("Тест")
        3. Проверьте, что найдены заметки
        """
        # Ваш код здесь
        mock_note_repository.search.return_value = list_of_notes
        result = note_service.search_notes("Тест")
        assert len(result) == 2
        mock_note_repository.search.assert_called_once_with("Тест")


class TestNoteServiceFilterByCategory:
    """Тесты фильтрации по категории"""

    def test_filter_by_category(self, note_service, mock_note_repository, list_of_notes):
        """
        Тест: Фильтрация заметок по категории

        TODO:
        1. Установите mock_note_repository.get_by_category.return_value = list_of_notes
        2. Вызовите note_service.filter_by_category(1)
        3. Проверьте результат
        """
        # Ваш код здесь
        mock_note_repository.get_by_category.return_value = list_of_notes
        result = note_service.filter_by_category(1)

        assert len(result) == 2
        mock_note_repository.get_by_category.assert_called_once_with(1)

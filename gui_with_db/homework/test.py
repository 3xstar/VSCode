import pytest
import psycopg2
from db.db import get_conn
from services.category_service import CategoryService
from services.recipe_service import RecipeService


@pytest.fixture
def db_conn():
    """Транзакционная фикстура для работы с БД"""
    conn = get_conn()
    conn.autocommit = False  # Отключаем autocommit для работы с транзакциями
    yield conn
    conn.rollback()  # Откатываем все изменения после теста
    conn.close()


class TestCategoryService:
    
    def test_get_by_id_success(self, db_conn):
        """Тест получения категории по ID"""
        # Создаем тестовую категорию
        cursor = db_conn.cursor()
        cursor.execute("INSERT INTO recipes.categories (name) VALUES ('Тестовая категория') RETURNING id")
        category_id = cursor.fetchone()[0]
        
        # Модифицируем CategoryService для использования переданного connection
        original_get_conn = CategoryService.get_by_id.__globals__['db'].get_conn
        
        def mock_get_conn():
            return db_conn
        CategoryService.get_by_id.__globals__['db'].get_conn = mock_get_conn
        
        # Тестируем get_by_id
        result = CategoryService.get_by_id(category_id)
        assert len(result) == 1
        assert result[0][1] == 'Тестовая категория'
        
        # Возвращаем оригинальную функцию
        CategoryService.get_by_id.__globals__['db'].get_conn = original_get_conn
    
    def test_create_category_success(self, db_conn):
        """Тест создания категории"""
        # Модифицируем CategoryService
        original_add = CategoryService.add.__globals__['db'].get_conn
        
        def mock_get_conn():
            return db_conn
        CategoryService.add.__globals__['db'].get_conn = mock_get_conn
        
        # Создаем категорию
        result = CategoryService.add('Новая тестовая категория')
        
        # Проверяем, что категория создалась
        cursor = db_conn.cursor()
        cursor.execute("SELECT name FROM recipes.categories WHERE id = %s", (result[0],))
        name = cursor.fetchone()[0]
        assert name == 'Новая тестовая категория'
        
        CategoryService.add.__globals__['db'].get_conn = original_add
    
    def test_negative_enum_value(self, db_conn):
        """Тест на некорректное значение enum"""
        # Модифицируем RecipeService
        original_add = RecipeService.add_recipe.__globals__['db'].get_conn
        
        def mock_get_conn():
            return db_conn
        RecipeService.add_recipe.__globals__['db'].get_conn = mock_get_conn
        
        # Создаем тестовую категорию
        cursor = db_conn.cursor()
        cursor.execute("INSERT INTO recipes.categories (name) VALUES ('Категория для теста') RETURNING id")
        category_id = cursor.fetchone()[0]
        
        # Пытаемся создать рецепт с некорректным значением enum
        with pytest.raises(Exception):
            RecipeService.add_recipe('Тестовый рецепт', category_id, 'НЕСУЩЕСТВУЮЩИЙ_УРОВЕНЬ')
        
        RecipeService.add_recipe.__globals__['db'].get_conn = original_add
    
    def test_negative_foreign_key(self, db_conn):
        """Тест на некорректный внешний ключ"""
        # Модифицируем RecipeService
        original_add = RecipeService.add_recipe.__globals__['db'].get_conn
        
        def mock_get_conn():
            return db_conn
        RecipeService.add_recipe.__globals__['db'].get_conn = mock_get_conn
        
        # Пытаемся создать рецепт с несуществующим category_id
        with pytest.raises(Exception):
            RecipeService.add_recipe('Тестовый рецепт', 99999, 'легкий')
        
        RecipeService.add_recipe.__globals__['db'].get_conn = original_add
    
    def test_record_not_found(self, db_conn):
        """Тест на отсутствие записи"""
        # Модифицируем CategoryService
        original_get = CategoryService.get_by_id.__globals__['db'].get_conn
        
        def mock_get_conn():
            return db_conn
        CategoryService.get_by_id.__globals__['db'].get_conn = mock_get_conn
        
        # Ищем несуществующую категорию
        result = CategoryService.get_by_id(99999)
        assert len(result) == 0
        
        CategoryService.get_by_id.__globals__['db'].get_conn = original_get
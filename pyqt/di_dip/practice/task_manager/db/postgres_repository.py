import sys
import pandas as pd
from sqlalchemy import create_engine, text
from sqlalchemy.engine import Engine
from typing import Optional

sys.path.append('c:/VSCODE/pyqt/task_manager')
from db.interface import DatabaseInterface

class PostgresTaskRepository(DatabaseInterface):
    """Реализация репозитория задач для PostgreSQL"""
    
    def __init__(self, connection_string: str = 'postgresql+psycopg2://postgres:123@localhost:5432/task_manager_db'):
        self.connection_string = connection_string
        self._engine: Optional[Engine] = None
        self._init_engine()
    
    def _init_engine(self):
        """Инициализация движка SQLAlchemy"""
        self._engine = create_engine(self.connection_string)
    
    def _get_engine(self) -> Engine:
        """Получить движок SQLAlchemy (создает при необходимости)"""
        if self._engine is None:
            self._init_engine()
        return self._engine
    
    def get_all_tasks(self) -> pd.DataFrame:
        """Получить все задачи"""
        engine = self._get_engine()
        query = "SELECT * FROM app.tasks ORDER BY id"
        df = pd.read_sql(query, engine)
        return df
    
    def add_task(self, title: str, description: str, status: str, priority: int) -> pd.DataFrame:
        """Добавить новую задачу"""
        engine = self._get_engine()
        with engine.connect() as conn:
            conn.execute(
                text("""INSERT INTO app.tasks (title, description, status, priority)
                      VALUES (:title, :description, :status, :priority)"""),
                {"title": title, "description": description, "status": status, "priority": priority}
            )
            conn.commit()
        print(f"Задача {title} добавлена\n")
        self.reindex_tasks()
        return self.get_all_tasks()
    
    def get_tasks_by_status(self, status: str) -> pd.DataFrame:
        """Получить задачи по статусу"""
        engine = self._get_engine()
        query = "SELECT * FROM app.tasks WHERE status = :status ORDER BY id"
        df = pd.read_sql(query, engine, params={"status": status})
        print(f"Задачи найденные по статусу - {status}:")
        return df
    
    def update_task_status(self, task_id: int, new_status: str) -> pd.DataFrame:
        """Обновить статус задачи"""
        engine = self._get_engine()
        with engine.connect() as conn:
            conn.execute(
                text("UPDATE app.tasks SET status = :new_status WHERE id = :task_id"),
                {"new_status": new_status, "task_id": task_id}
            )
            conn.commit()
        print(f"Статус задачи под id - {task_id} обновлен на: {new_status}\n")
        return self.get_all_tasks()
    
    def delete_task(self, task_id: int) -> pd.DataFrame:
        """Удалить задачу"""
        engine = self._get_engine()
        with engine.connect() as conn:
            conn.execute(
                text("DELETE FROM app.tasks WHERE id = :task_id"),
                {"task_id": task_id}
            )
            conn.commit()
            print(f"Задача под id = {task_id} удалена\n")
        
        self.reindex_tasks()
        return self.get_all_tasks()
    
    def reindex_tasks(self) -> None:
        """Перенумеровать ID задач"""
        engine = self._get_engine()
        with engine.begin() as conn:
            result = conn.execute(text("SELECT id FROM app.tasks ORDER BY id"))
            rows = result.fetchall()
            
            if not rows:
                conn.execute(text("ALTER SEQUENCE app.tasks_id_seq RESTART WITH 1"))
                print("Таблица пуста, счётчик сброшен")
                return
            
            conn.execute(text("""
                CREATE TEMP TABLE tasks_temp AS 
                SELECT * FROM app.tasks ORDER BY id
            """))
            
            conn.execute(text("TRUNCATE TABLE app.tasks RESTART IDENTITY CASCADE"))
            
            conn.execute(text("""
                INSERT INTO app.tasks (title, description, status, priority)
                SELECT title, description, status, priority 
                FROM tasks_temp 
                ORDER BY id
            """))
            
            conn.execute(text("DROP TABLE tasks_temp"))
            
            conn.execute(text("""
                SELECT setval('app.tasks_id_seq', COALESCE((SELECT MAX(id) FROM app.tasks), 0))
            """))
            
        print("ID задач перенумерованы по порядку")
    
    def get_max_priority(self) -> int:
        """Получить максимальный приоритет"""
        try:
            df = self.get_all_tasks()
            if df.empty:
                return 0
            return int(df['priority'].max())
        except Exception as e:
            print(f"Ошибка получения максимального приоритета: {e}")
            return 0
    
    def close_connection(self) -> None:
        """Закрыть соединение с БД"""
        if self._engine:
            self._engine.dispose()
            self._engine = None
            print("Соединение с БД закрыто")
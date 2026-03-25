from abc import ABC, abstractmethod
import pandas as pd

class DatabaseInterface(ABC):
    """Абстрактный интерфейс для работы с базой данных"""
    
    @abstractmethod
    def get_all_tasks(self) -> pd.DataFrame:
        """Получить все задачи"""
        pass
    
    @abstractmethod
    def add_task(self, title: str, description: str, status: str, priority: int) -> pd.DataFrame:
        """Добавить новую задачу"""
        pass
    
    @abstractmethod
    def get_tasks_by_status(self, status: str) -> pd.DataFrame:
        """Получить задачи по статусу"""
        pass
    
    @abstractmethod
    def update_task_status(self, task_id: int, new_status: str) -> pd.DataFrame:
        """Обновить статус задачи"""
        pass
    
    @abstractmethod
    def delete_task(self, task_id: int) -> pd.DataFrame:
        """Удалить задачу"""
        pass
    
    @abstractmethod
    def reindex_tasks(self) -> None:
        """Перенумеровать ID задач"""
        pass
    
    @abstractmethod
    def get_max_priority(self) -> int:
        """Получить максимальный приоритет"""
        pass
    
    @abstractmethod
    def close_connection(self) -> None:
        """Закрыть соединение с БД"""
        pass
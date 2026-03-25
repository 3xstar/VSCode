import sys
import pandas as pd

sys.path.append('c:/VSCODE/pyqt/task_manager')
from db.interface import DatabaseInterface

class TaskService:
    """Сервис для работы с задачами (высокоуровневый модуль)"""
    
    def __init__(self, repository: DatabaseInterface):
        """
        Внедрение зависимости через конструктор
        
        Args:
            repository: Реализация интерфейса DatabaseInterface
        """
        self._repository = repository
    
    def get_all_tasks(self) -> pd.DataFrame:
        """Получить все задачи"""
        return self._repository.get_all_tasks()
    
    def add_task(self, title: str, description: str, status: str, priority: int) -> pd.DataFrame:
        """Добавить новую задачу"""
        if not title or not title.strip():
            raise ValueError("Название задачи не может быть пустым")
        
        if priority < 1:
            raise ValueError("Приоритет должен быть положительным числом")
        
        return self._repository.add_task(title, description, status, priority)
    
    def get_tasks_by_status(self, status: str) -> pd.DataFrame:
        """Получить задачи по статусу"""
        return self._repository.get_tasks_by_status(status)
    
    def update_task_status(self, task_id: int, new_status: str) -> pd.DataFrame:
        """Обновить статус задачи"""
        if task_id <= 0:
            raise ValueError("ID задачи должен быть положительным числом")
        
        return self._repository.update_task_status(task_id, new_status)
    
    def delete_task(self, task_id: int) -> pd.DataFrame:
        """Удалить задачу"""
        if task_id <= 0:
            raise ValueError("ID задачи должен быть положительным числом")
        
        return self._repository.delete_task(task_id)
    
    def get_max_priority(self) -> int:
        """Получить максимальный приоритет"""
        return self._repository.get_max_priority()
    
    def reindex_tasks(self) -> None:
        """Перенумеровать задачи"""
        self._repository.reindex_tasks()
    
    def close(self) -> None:
        """Закрыть соединение с БД"""
        self._repository.close_connection()
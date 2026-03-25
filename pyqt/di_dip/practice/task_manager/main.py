import sys
import os

# Добавляем текущую директорию в path
current_dir = os.path.dirname(os.path.abspath(__file__))
if current_dir not in sys.path:
    sys.path.insert(0, current_dir)

from gui.main_window import MainWindow
from services.task_service import TaskService
from db.postgres_repository import PostgresTaskRepository

def main():
    """Главная функция для запуска приложения"""
    print("=" * 40)
    print("Запуск Менеджера задач")
    print("=" * 40)
    
    try:
        # Создаем конкретную реализацию репозитория
        repository = PostgresTaskRepository()
        
        # Проверяем подключение
        test_df = repository.get_all_tasks()
        print(f"✓ Подключение к базе данных успешно")
        print(f"✓ Найдено задач: {len(test_df)}")
        print("-" * 40)
        
        # Создаем сервис с внедрением зависимости
        task_service = TaskService(repository)
        
        print("Запуск графического интерфейса...")
        print("-" * 40)
        
        # Запускаем GUI с внедрением зависимости
        from PyQt6.QtWidgets import QApplication
        
        app = QApplication(sys.argv)
        window = MainWindow(task_service)
        window.show()
        sys.exit(app.exec())
        
    except Exception as e:
        print(f"Ошибка при запуске: {e}")
        import traceback
        traceback.print_exc()
        return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())
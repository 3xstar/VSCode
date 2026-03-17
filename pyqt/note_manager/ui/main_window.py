import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                             QHBoxLayout, QTableWidget, QTableWidgetItem, 
                             QLineEdit, QTextEdit, QComboBox, QPushButton, 
                             QMessageBox, QLabel, QHeaderView, QGroupBox)
from services.note_service import NoteService

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.service = NoteService()
        self.current_note_id = None
        
        self.setWindowTitle("Note Manager")
        self.setGeometry(100, 100, 1100, 700)
        
        self.init_ui()
        self.load_notes()

    def init_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)
        
        # === ВЕРХНЯЯ ПАНЕЛЬ: Поиск и Фильтр ===
        search_layout = QHBoxLayout()
        
        # Задание 1: Поиск по названию
        search_layout.addWidget(QLabel("🔍 Поиск:"))
        self.search_input = QLineEdit()
        self.search_input.setPlaceholderText("Введите название заметки...")
        self.search_input.textChanged.connect(self.on_search_changed)
        search_layout.addWidget(self.search_input, 2)
        
        # Задание 2: Фильтр по категории
        search_layout.addWidget(QLabel("📁 Категория:"))
        self.filter_category = QComboBox()
        self.filter_category.addItem("Все категории", userData=None)
        self.filter_category.addItem("Учеба", userData=1)
        self.filter_category.addItem("Работа", userData=2)
        self.filter_category.addItem("Личное", userData=3)
        self.filter_category.currentIndexChanged.connect(self.load_notes)
        search_layout.addWidget(self.filter_category)
        
        main_layout.addLayout(search_layout)
        
        # === ФОРМА ВВОДА ===
        form_group = QGroupBox("📝 Форма заметки")
        form_layout = QVBoxLayout(form_group)
        
        input_layout = QHBoxLayout()
        input_layout.addWidget(QLabel("Заголовок:"))
        self.title_input = QLineEdit()
        self.title_input.setPlaceholderText("Название заметки")
        input_layout.addWidget(self.title_input, 2)
        
        # Задание 4: Выбор категории для заметки
        input_layout.addWidget(QLabel("Категория:"))
        self.category_combo = QComboBox()
        self.category_combo.addItem("Учеба", userData=1)
        self.category_combo.addItem("Работа", userData=2)
        self.category_combo.addItem("Личное", userData=3)
        input_layout.addWidget(self.category_combo)
        
        form_layout.addLayout(input_layout)
        
        self.content_input = QTextEdit()
        self.content_input.setPlaceholderText("Текст заметки")
        self.content_input.setMaximumHeight(80)
        form_layout.addWidget(self.content_input)
        
        # Кнопки
        btn_layout = QHBoxLayout()
        
        self.btn_add = QPushButton("➕ Добавить")
        self.btn_add.clicked.connect(self.add_note)
        
        self.btn_update = QPushButton("✏️ Обновить")
        self.btn_update.clicked.connect(self.update_note)
        self.btn_update.setEnabled(False)
        
        self.btn_delete = QPushButton("🗑️ Удалить")
        self.btn_delete.clicked.connect(self.delete_note)
        self.btn_delete.setEnabled(False)
        
        self.btn_refresh = QPushButton("🔄 Обновить список")
        self.btn_refresh.clicked.connect(self.load_notes)
        
        btn_layout.addWidget(self.btn_add)
        btn_layout.addWidget(self.btn_update)
        btn_layout.addWidget(self.btn_delete)
        btn_layout.addWidget(self.btn_refresh)
        
        form_layout.addLayout(btn_layout)
        main_layout.addWidget(form_group)
        
        # === ТАБЛИЦА ===
        self.table = QTableWidget()
        # Задание 3 и 6: Добавлены колонки "Дата создания" и "Пользователь"
        self.table.setColumnCount(6)
        self.table.setHorizontalHeaderLabels(["ID", "Заголовок", "Содержимое", "Категория", "Пользователь", "Дата создания"])
        
        header = self.table.horizontalHeader()
        header.setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        header.setSectionResizeMode(2, QHeaderView.ResizeMode.Stretch)
        self.table.setSelectionBehavior(QTableWidget.SelectionBehavior.SelectRows)
        self.table.itemSelectionChanged.connect(self.on_selection_changed)
        
        main_layout.addWidget(self.table)

    def load_notes(self, search_text=None):
        """Загружает заметки с учетом поиска и фильтра"""
        # Задание 1 и 2: Здесь будет вызов нового метода сервиса
        # Пока используем get_all_notes(), после доработки сервиса:
        # notes = self.service.get_notes_filtered(search_text, self.filter_category.currentData())
        notes = self.service.get_notes()
        
        self.table.setRowCount(0)
        
        if not notes:
            return

        for row_idx, note in enumerate(notes):
            # Структура: id, title, content, category_id, user_id, created_at, username
            n_id = note[0]
            title = note[1]
            content = note[2]
            cat_id = note[3]
            user_id = note[4]
            created_at = note[5] if len(note) > 5 else "N/A"  # Задание 3
            username = note[6] if len(note) > 6 else f"User {user_id}"  # Задание 6
            
            cat_name = self.get_category_name_by_id(cat_id)
            
            self.table.insertRow(row_idx)
            self.table.setItem(row_idx, 0, QTableWidgetItem(str(n_id)))
            self.table.setItem(row_idx, 1, QTableWidgetItem(title))
            self.table.setItem(row_idx, 2, QTableWidgetItem(content[:50] + "..." if len(content) > 50 else content))
            self.table.setItem(row_idx, 3, QTableWidgetItem(cat_name))
            self.table.setItem(row_idx, 4, QTableWidgetItem(username))  # Задание 6
            self.table.setItem(row_idx, 5, QTableWidgetItem(str(created_at)))  # Задание 3

    def get_category_name_by_id(self, cat_id):
        mapping = {1: "Учеба", 2: "Работа", 3: "Личное"}
        return mapping.get(cat_id, f"ID:{cat_id}")

    def on_search_changed(self):
        """Задание 1: Реагирует на изменение текста поиска"""
        search_text = self.search_input.text().strip()
        self.load_notes(search_text if search_text else None)

    def on_selection_changed(self):
        selected_rows = self.table.selectedItems()
        if not selected_rows:
            self.current_note_id = None
            self.btn_update.setEnabled(False)
            self.btn_delete.setEnabled(False)
            self.clear_inputs()
            return
        
        row = selected_rows[0].row()
        self.current_note_id = int(self.table.item(row, 0).text())
        
        full_note = self.service.get_note(self.current_note_id)
        
        if full_note:
            self.title_input.setText(full_note[1])
            self.content_input.setText(full_note[2])
            
            # Задание 4: Выбираем категорию в комбобоксе
            cat_id = full_note[3]
            index = self.category_combo.findData(cat_id)
            if index >= 0:
                self.category_combo.setCurrentIndex(index)
            
            self.btn_update.setEnabled(True)
            self.btn_delete.setEnabled(True)

    def clear_inputs(self):
        self.title_input.clear()
        self.content_input.clear()
        self.category_combo.setCurrentIndex(0)
        self.current_note_id = None
        self.btn_update.setEnabled(False)
        self.btn_delete.setEnabled(False)

    def add_note(self):
        title = self.title_input.text().strip()
        content = self.content_input.toPlainText().strip()
        
        if not title:
            QMessageBox.warning(self, "Ошибка", "Введите название заметки!")
            return
            
        category_id = self.category_combo.currentData()
        user_id = 1
        
        try:
            self.service.add_note(title, content, category_id, user_id)
            QMessageBox.information(self, "Успех", "Заметка добавлена!")
            self.clear_inputs()
            self.load_notes()
        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Не удалось добавить заметку: {e}")

    def update_note(self):
        if not self.current_note_id:
            return
            
        title = self.title_input.text().strip()
        content = self.content_input.toPlainText().strip()
        
        if not title:
            QMessageBox.warning(self, "Ошибка", "Введите название заметки!")
            return
        
        # Задание 4: Получаем новую категорию из комбобокса
        category_id = self.category_combo.currentData()
        
        try:
            # Пока сервис не обновлён, передаём только title и content
            # После доработки сервиса: self.service.change_note(self.current_note_id, title, content, category_id)
            self.service.change_note(self.current_note_id, title, content)
            QMessageBox.information(self, "Успех", "Заметка обновлена!")
            self.clear_inputs()
            self.load_notes()
        except Exception as e:
            QMessageBox.critical(self, "Ошибка", f"Не удалось обновить заметку: {e}")

    def delete_note(self):
        if not self.current_note_id:
            return
        
        # Задание 5: Подтверждение удаления через диалоговое окно
        confirm = QMessageBox.question(
            self, 
            "Подтверждение удаления", 
            f"Вы уверены, что хотите удалить заметку ID {self.current_note_id}?\n\nЭто действие нельзя отменить.",
            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,
            QMessageBox.StandardButton.No
        )
        
        if confirm == QMessageBox.StandardButton.Yes:
            try:
                self.service.delete_note(self.current_note_id)
                QMessageBox.information(self, "Успех", "Заметка удалена!")
                self.clear_inputs()
                self.load_notes()
            except Exception as e:
                QMessageBox.critical(self, "Ошибка", f"Не удалось удалить заметку: {e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())
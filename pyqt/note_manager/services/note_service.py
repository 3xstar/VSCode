from repositories.note_repository import NoteRepository
class NoteService:
    def __init__(self):
        self.repository = NoteRepository()

    def get_notes(self):
        return self.repository.get_all_notes()
    
    def get_note(self, note_id):
        return self.repository.get_note_by_id(note_id)
    
    def add_note(self, title, content, category_id, user_id):
        return self.repository.create_note(title, content, category_id, user_id)
    
    def change_note(self, note_id, title, content, category_id):  # Добавлен параметр
        return self.repository.update_note(note_id, title, content, category_id)
    
    def delete_note(self, note_id):
        return self.repository.remove_note(note_id)
    
    def search_notes(self, search_text):
        return self.repository.search_notes_by_title(search_text)
    
    def filter_by_category(self, category_id):
        return self.repository.get_notes_by_category(category_id)
    

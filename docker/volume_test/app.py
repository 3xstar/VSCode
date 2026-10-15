import os
import sqlite3
from flask import Flask, request, redirect, url_for
 
app = Flask(__name__)
 
DB_PATH = "/data/notes.db"
 
 
def get_db():
    os.makedirs("/data", exist_ok=True)
    conn = sqlite3.connect(DB_PATH)
    conn.execute("""
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            text TEXT NOT NULL
        )
    """)
    return conn
 
 
@app.route("/", methods=["GET", "POST"])
def index():
    conn = get_db()
 
    if request.method == "POST":
        text = request.form.get("note", "").strip()
        if text:
            conn.execute("INSERT INTO notes (text) VALUES (?)", (text,))
            conn.commit()
        return redirect(url_for("index"))
 
    notes = conn.execute("SELECT id, text FROM notes ORDER BY id DESC").fetchall()
    conn.close()
 
    items = "".join(f"<li>{text}</li>" for _, text in notes)
    return f"""
    <h1>Мои заметки</h1>
    <form method="post">
        <input name="note" placeholder="Новая заметка" required>
        <button>Добавить</button>
    </form>
    <ul>{items}</ul>
    """
 
 
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
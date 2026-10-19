import os
from datetime import datetime
from flask import Flask, request, redirect, url_for
from flask_sqlalchemy import SQLAlchemy

# --- Путь к БД из переменной окружения ---
DB_PATH = os.getenv("DB_PATH", "/data/data.db")
os.makedirs(os.path.dirname(DB_PATH), exist_ok=True)

app = Flask(__name__)
app.config["SQLALCHEMY_DATABASE_URI"] = f"sqlite:///{DB_PATH}"
app.config["SQLALCHEMY_TRACK_MODIFICATIONS"] = False

db = SQLAlchemy(app)


# --- Модели (ORM-классы = таблицы в БД) ---
class Visit(db.Model):
    __tablename__ = "visits"
    id = db.Column(db.Integer, primary_key=True)
    ts = db.Column(db.DateTime, default=datetime.utcnow)


class Message(db.Model):
    __tablename__ = "messages"
    id = db.Column(db.Integer, primary_key=True)
    author = db.Column(db.String(50), nullable=False)
    text = db.Column(db.Text, nullable=False)
    ts = db.Column(db.DateTime, default=datetime.utcnow)


# --- Создание таблиц при первом запуске ---
with app.app_context():
    db.create_all()


# --- Маршруты ---
@app.route("/")
def index():
    visit = Visit()
    db.session.add(visit)
    db.session.commit()

    visits_count = Visit.query.count()
    messages = Message.query.order_by(Message.ts.desc()).all()

    rows = "".join(
        f"<li><b>{m.author}</b> ({m.ts:%Y-%m-%d %H:%M}): {m.text}</li>"
        for m in messages
    ) or "<li><i>Пока сообщений нет</i></li>"

    return f"""
    <h1>Гостевая книга</h1>
    <p>Счётчик посещений: <b>{visits_count}</b></p>
    <form method="post" action="/add">
      <input name="author" placeholder="Имя" required>
      <input name="text" placeholder="Сообщение" required>
      <button type="submit">Отправить</button>
    </form>
    <ul>{rows}</ul>
    """


@app.route("/add", methods=["POST"])
def add():
    author = request.form.get("author", "").strip()
    text = request.form.get("text", "").strip()
    if author and text:
        db.session.add(Message(author=author, text=text))
        db.session.commit()
    return redirect(url_for("index"))


@app.route("/health")
def health():
    return "OK", 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
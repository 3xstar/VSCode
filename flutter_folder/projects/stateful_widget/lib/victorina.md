# Викторина — самостоятельная работа

---

## ТЗ

Приложение-викторина:
- Главный экран, на котором рекорд, кнопка старта и кнопка сброса рекорда
- 5 вопросов с вариантами ответов (Вопросы и варианты ответов для них придумайте самостоятельно)
- В конце викторины результат текущей попытки

---

## Шаг 1. Точка входа

```dart
class VictorinaApp extends StatelessWidget {
  const VictorinaApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: const VictorinaHome(),
    );
  }
}
```

**Что здесь:**
- `VictorinaApp` — главный виджет приложения
- `VictorinaHome` — главный экран (с рекордом и кнопкой "Начать")

---

## Шаг 2. Сам главный экран

```dart
class VictorinaHome extends StatefulWidget {
  const VictorinaHome({super.key});

  @override
  State<VictorinaHome> createState() => _VictorinaHomeState();
}
```

---

## Шаг 3. Загрузка рекорда

```dart
int _bestScore = 0;

 @override
void initState() {
  super.initState();
  _loadBestScore();
}

Future<void> _loadBestScore() async {
  final prefs = await SharedPreferences.getInstance();
  setState(() {
    _bestScore = prefs.getInt('best_score') ?? 0;
  });
}
```

**Что здесь:**
`SharedPreferences.getInstance()` - Получаем доступ к хранилищу
`prefs.getInt('best_score')` - Читаем значение по ключу `'best_score'` 
`?? 0` - Если ничего нет (null), берём 0 

---

## Шаг 4. Функция сохранение рекорда

```dart
Future<void> _saveBestScore(int score) async {
  final prefs = await SharedPreferences.getInstance();
  final bestScore = prefs.getInt('best_score') ?? 0;
  if (score > bestScore) {
    await prefs.setInt('best_score', score);
    setState(() => _bestScore = score);
  }
}
```

**Логика:**
1. Читаем текущий рекорд
2. Если текущий счёт лучше — сохраняем
3. Обновляем экран (`setState`)

---

## Шаг 5. Переход к викторине

```dart
ElevatedButton(
  onPressed: () {
    Navigator.push(
      context,
      MaterialPageRoute(
        builder: (_) => QuizScreen(onFinish: _saveBestScore),
      ),
    );
  },
  child: const Text('Начать'),
)
```

**Что здесь:**
- `Navigator.push` — переход на новый экран
- `MaterialPageRoute` — анимация перехода (слева направо)
- `onFinish: _saveBestScore` — передаём функцию которая вызовется когда игра закончится

---

### Пример отрисовки главного экрана

```dart
@override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(title: const Text('Викторина')),
    body: Center(
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Icon(Icons.quiz, size: 100, color: Colors.blue),
          const SizedBox(height: 32),
          const Text('Викторина', style: TextStyle(fontSize: 32, fontWeight: FontWeight.bold)),
          const SizedBox(height: 16),
          Text('Рекорд: $_bestScore', style: const TextStyle(fontSize: 20)),
          const SizedBox(height: 32),
          ElevatedButton(
            onPressed: () { /* переход к викторине */ },
            child: const Padding(
              padding: EdgeInsets.all(12.0),
              child: Text('Начать', style: TextStyle(fontSize: 16)),
            ),
          ),
          TextButton(
            onPressed: _resetBestScore,
            child: const Text('Сбросить рекорд'),
          ),
        ],
      ),
    ),
  );
}
```

---

## Шаг 6. Экран викторины

### 6.1. Вопросы (массив)

```dart
final List<Map<String, dynamic>> _questions = [
  {
    'question': 'Какова цена взрослой жизни?',
    'options': ['пачка кириешек', 'Берлин', 'доширак', 'отсутствие нервов'],
    'correct': 3,
  },
  {
    'question': 'Какой преподаватель является самым лучшим?',
    'options': ['Захар', 'Никита', 'Андрей', 'Андрей'],
    'correct': 1,
  },
];
```

**Разбор:**
`List<...>` - Список (массив) | — |
`Map<String, dynamic>` - Объект с ключами (как словарь) | — |
`'question'` - Текст вопроса | String |
`'options'` - Список вариантов ответа | List<String> |
`'correct'` - Индекс правильного ответа | int |

**Как получить значение:**
```dart
_questions[0]['question']     // 'Столица Франции?'
_questions[0]['options']      // ['Лондон', 'Берлин', ...]
_questions[0]['correct']      // 2 (индекс 'Париж')
```

---

### 6.2. Перемешивание вопросов

```dart
 @override
void initState() {
  super.initState();
  _questions.shuffle(Random());
}
```

**`shuffle(Random())`** — перемешивает список в случайном порядке.

**Каждый раз новый порядок:**
- Запустил игру → вопросы перемешались
- Сыграл ещё раз → снова перемешались

---

### 6.3. Выбор ответа

```dart
void _selectAnswer(int index) {
  if (_answered) return;  // Нельзя выбрать дважды

  // Считаем очки
  if (index == _questions[_currentQuestion]['correct']) {
    _score++;
  }

  // Экран становится неактивным
  setState(() => _answered = true);

  // Через 0.5 секунды — следующий вопрос
  Future.delayed(const Duration(milliseconds: 500), () {
    if (_currentQuestion < _questions.length - 1) {
      setState(() {
        _currentQuestion++;
        _answered = false;
      });
    } else {
      setState(() => _showResult = true);
    }
  });
}
```

**Логика:**
1. Проверка `_answered` — нельзя нажать дважды
2. Сравниваем индекс с правильным (`'correct'`)
3. Если верно — `_score++`
4. `_answered = true` — экран сереет, кнопки не нажимаются
5. Ждём 0.5 секунды на осознание реальности
6. Если не последний вопрос → следующий
7. Если последний → показываем результат

---

### 6.4. Отрисовка кнопок

```dart
...options.map((option) => Padding(
  padding: const EdgeInsets.only(bottom: 12.0),
  child: ElevatedButton(
    onPressed: () => _selectAnswer(options.indexOf(option)),
    padding: const EdgeInsets.all(16.0),
    child: Text(option, style: const TextStyle(fontSize: 16)),
  ),
)).toList()
```

**Разбор:**
`...options` - "Распаковывает" список (spread operator) 
`.map((option) => ...)` | Преобразует каждый элемент 
`options.indexOf(option)` | Получает индекс варианта (0, 1, 2, 3) 
`.toList()` | Превращает результат в List 

- `options` — это `List<dynamic>`
- Нужно превратить в `List<Widget>` (кнопки)
- `.map()` проходит по каждому варианту и создаёт кнопку

**Пример:**
```dart
options = ['Захар', 'Никита', 'Андрей', 'Андрей']

// После .map():
[
  ElevatedButton(child: Text('Захар')),
  ElevatedButton(child: Text('Никита')),
  ElevatedButton(child: Text('Андрей')),
  ElevatedButton(child: Text('Андрей')),
]
```

---

### Пример отрисовки экрана викторины

```dart
@override
Widget build(BuildContext context) {
  return Scaffold(
    appBar: AppBar(
      title: Text('Вопрос ${_currentQuestion + 1}/${_questions.length}'),
    ),
    body: IgnorePointer(
      ignoring: _answered,
      child: AnimatedOpacity(
        opacity: _answered ? 0.5 : 1.0,
        duration: const Duration(milliseconds: 200),
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              const SizedBox(height: 32),
              Text(
                question['question'],
                style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
                textAlign: TextAlign.center,
              ),
              const SizedBox(height: 32),
              ...options.map((option) => Padding(
                padding: const EdgeInsets.only(bottom: 12.0),
                child: ElevatedButton(
                  onPressed: () => _selectAnswer(options.indexOf(option)),
                  padding: const EdgeInsets.all(16.0),
                  child: Text(option, style: const TextStyle(fontSize: 16)),
                ),
              )).toList(),
            ],
          ),
        ),
      ),
    ),
  );
}
```

---

### 6.5. Экран результата

```dart
if (_showResult) {
  widget.onFinish(_score);  // Вызываем функцию сохранения рекорда
  return Scaffold(...);  // Экран с результатом
}
```

**`widget.onFinish`** — это функция которую передали при создании:
```dart
QuizScreen(onFinish: _saveBestScore)
```

- Когда `_showResult = true` (вопросы закончились)
- Вызывает `_saveBestScore(_score)` — сохраняет рекорд
- Возвращает экран с результатом

---

### Пример отрисовки экрана результата

```dart
@override
Widget build(BuildContext context) {
  if (_showResult) {
    widget.onFinish(_score);
    return Scaffold(
      appBar: AppBar(title: const Text('Результат')),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            const Icon(Icons.emoji_events, size: 100, color: Colors.amber),
            const SizedBox(height: 32),
            Text(
              '$_score из ${_questions.length}',
              style: const TextStyle(fontSize: 32, fontWeight: FontWeight.bold),
            ),
            const SizedBox(height: 16),
            Text(
              _score == _questions.length
                  ? 'Идеально!'
                  : _score > _questions.length / 2
                      ? 'Неплохо '
                      : 'Попробуй ещё раз ',
              style: const TextStyle(fontSize: 18),
            ),
            const SizedBox(height: 32),
            ElevatedButton(
              onPressed: _restart,
              child: const Text('Играть снова'),
            ),
          ],
        ),
      ),
    );
  }
  // ... остальной код
}
```

---

## Дополнительные задания
1. Добавь кнопку "Сбросить рекорд" (**`prefs.remove('best_score')`** — удаляет значение из хранилища.)
2. Добавь таймер на вопрос (10 секунд)

---

**Готово!**

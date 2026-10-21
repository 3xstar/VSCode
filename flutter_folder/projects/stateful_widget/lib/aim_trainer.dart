import 'package:flutter/material.dart'; // пакет который используется для складывания продуктов
import 'dart:math'; // для рандомного числа
import 'dart:async'; // для таймера
import 'package:shared_preferences/shared_preferences.dart';

void main() {
  runApp(const AimTrainerApp());
}

class AimTrainerApp extends StatelessWidget {
  const AimTrainerApp({super.key});

  @override 
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData.dark(useMaterial3: true),
      home: const GameScreen(), // указывает какой экран запускается в первую очередь
    );
  }
}
// изменяющееся состояние, потому что будеут меняться счет, время и тд
class GameScreen extends StatefulWidget {
  const GameScreen({super.key});

  @override 
  State<GameScreen> createState() => _GameScreenState();
}

class _GameScreenState extends State<GameScreen> {
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

  Future<void> _saveBestScore(int score) async {
    final prefs = await SharedPreferences.getInstance();
    final bestScore = prefs.getInt('best_score') ?? 0;
    if (score > bestScore) {
      await prefs.setInt('best_score', score);
      setState(() => _bestScore = score);
    }
  }
  // --- ПЕРЕМЕННЫЕ ---
  int _score = 0; // счет игрока
  int _timeLeft = 10; // оставшееся время 
  int _activeIndex = -1; // индекс горящего квадрата
  bool _isPlaying = false; // флаг, идет игра или нет 

  // список цветов по квадратикам
  final List<Color> _colors = List.generate(16, (_) => Colors.grey[800]!);

  void _startGame() {
    setState(() {
      _score = 0; 
      _timeLeft = 10;
      _isPlaying = true; 
      _lightRandom();
    });

  Timer.periodic(const Duration(seconds: 1), (timer)
  {
    if(_timeLeft > 0 && _isPlaying){
      setState(() => _timeLeft-- );
      } else {
        timer.cancel();
        setState(() => _isPlaying = false);
        }
    });
  }

  void _lightRandom(){
    final random = Random();
    // от 0 до 16 не включительно, тоесть до 15 (16 квадратиков, 0 - 15)
    final newIndex = random.nextInt(16);
    // сбрасываем все квадратики
    for (int i = 0; i < 16; i++) {
      _colors[i] = Colors.grey[800]!;
    }
    // окрашиваем нужный квадратик в рандомный цвет
    _colors[newIndex] = Colors.primaries[random.nextInt(Colors.primaries.length)];
    // запоминаем активный квадратик
    _activeIndex = newIndex;
  }

  void _onTap(int index){
    if (!_isPlaying) return;

    if(index == _activeIndex){
      setState(() => _score++ );
      _saveBestScore(_score);
      _lightRandom();
    } else {
      setState(() => _score-- );
      _lightRandom();
    }
  }

  @override
  Widget build(BuildContext context){
    const double appWidth = 400;
    const double appHeight = 600;

    return Scaffold(
      appBar: AppBar(
        title: Text("TrainAim"),
      ),
      body: Center(
        child: SizedBox(
          width: appWidth,
          height: appHeight,
          child: Container (
            color: Colors.grey[800],
              child: Column(
                children: [
                  Row(
                  mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                  children: [
                    Text('Очки: $_score', style: TextStyle(
                      fontSize: 26, fontWeight: FontWeight.bold,
                      color: Colors.white)),
                    Text('Время: $_timeLeft', style: TextStyle(
                      fontSize: 26, fontWeight: FontWeight.bold,
                      color: _timeLeft < 3 ? Colors.red : Colors.white)),
                    ],
                  ),

            const SizedBox(height: 50),

            if(_isPlaying)
              GridView.count(
                crossAxisCount: 4,
                shrinkWrap: true,
                childAspectRatio: 1,
                padding: EdgeInsets.all(20),
                mainAxisSpacing: 5,
                crossAxisSpacing: 5,
                
                children: List.generate(16, (index){
                  return GestureDetector(
                    onTap: () => _onTap(index),

                    child: Container(
                      decoration: BoxDecoration(
                        color: _colors[index],
                        borderRadius: BorderRadius.circular(7),
                      ),
                    ),
                  );
                }),
              ),
              if(!_isPlaying) ...[
                const SizedBox(height: 200),

                FilledButton.icon(
                  icon: const Icon(Icons.play_arrow),
                  label: Text(_score == 0 ? 'Старт игры' : 'Попробуй снова'),
                  onPressed: _startGame,
                ),

                const SizedBox(height: 200),
                Text('Рекорд: $_bestScore', style: const TextStyle(fontSize: 26, fontWeight: FontWeight.bold, color: Colors.amber)),

                if(_score > 0)
                  Padding(padding: const EdgeInsets.only(top: 16),
                  child: Text('Ваш результат: $_score', style: TextStyle(color: Colors.white)),
                  )
              ],
            ],
            ),
          ),
        ),
      ),
    );
  }

  @override
  void dispose() {
    super.dispose();
  }
}
import 'package:flutter/material.dart';
import 'dart:math';
import 'package:shared_preferences/shared_preferences.dart';

class NumGame extends StatefulWidget{
  const NumGame({super.key});

  @override
  State<NumGame> createState() => _NumGameState();
}

class _NumGameState extends State<NumGame> {
  int _bestScore = 0;

  Future<void> _loadScore() async {
    final prefs = await SharedPreferences.getInstance();
    final int? savedScore = prefs.getInt('bestScore');

    setState((){
      _bestScore = savedScore ?? 0;
    });
  }

  Future<void> _saveScore(int currentAttemps) async{
    if(_bestScore == 0 || currentAttemps < _bestScore){
    final prefs = await SharedPreferences.getInstance();
    await prefs.setInt('bestScore', currentAttemps);

    setState((){
      _bestScore = currentAttemps;
    });
    print('Сохраненый рекорд: $_bestScore');
    }
  }

  late int _randomSecret; // загаданное число от 0 до 100
  int _attemps = 0; // текущее количество попыток
  final _maxAttemps =10; // максимальное количество попыток
  String _achkych = ''; // подсказка больше или меньше (за донат)
  bool _game = false; // флаг состояния игры
  String _message = ''; // сообщение о состоянии игры

  final _controller = TextEditingController();

  void _startGame(){
    setState(() {
      _randomSecret = Random().nextInt(101);

      _attemps = 0;
      _achkych = '';
      _game = true;
      _message = '';
      _controller.clear();
   });
  }

  @override
  void initState(){
    super.initState();
    _loadScore();
    _startGame();
  }

  void Popitka(){
    final userNumber = int.tryParse(_controller.text);

    if(userNumber == null || userNumber < 0 || userNumber > 100){
      _showError('Введи число из диапозона');
      return;
    }

    _attemps++;
    
    if(userNumber == _randomSecret){
      setState(() {
        _game = false;

        _saveScore(_attemps);

        if(_attemps <= 5){
          _message = 'Жесть вот реально молодец красавчик лучший вообще\nКоличество попыток: $_attemps';
        } else {
          _message = 'Чмо, говно, лох, вонючка, задротище без личной жизни в угадайку чисел\nКоличество попыток: $_attemps';
        } 
      });
    } else if (_attemps >= _maxAttemps){
      setState((){
        _game = false;
        _message = 'Ты не угадал число\nЗагаданное число: $_randomSecret}';
      });
    } else {
      setState(() {
      _achkych = userNumber < _randomSecret ? 'больше' : 'меньше';
      });
    }
  }

  void _showError(String text){
    ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text(text)));
  }

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(title: const Text('Угадывание числа')),
        body: Center(
          child: Padding(
          padding: EdgeInsets.all(10),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text("Лучший рекорд: ${_bestScore == 0 ? 'нет' : _bestScore}"),
              Text("Диапозон от 0 до 100",
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 16),
              Text(
                '🍾Симпл-димплки: $_attemps/$_maxAttemps🦭',
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)
              ),
              if(_achkych.isNotEmpty && _game)
                Text(
                  'Нужно $_achkych',
                  style: TextStyle(
                    fontSize: 22,
                    color: Colors.pinkAccent
                  ),
              ),
              SizedBox(height: 16),
              if(_game)
                TextField(
                  controller: _controller,
                  keyboardType: TextInputType.number,
                  textAlign: TextAlign.center,
                  style: TextStyle(fontSize: 26),
                  decoration: InputDecoration(
                    border: OutlineInputBorder(),
                    hintText: 'Введите число 1-100',
                ),
              ),
              SizedBox(height: 16),
              if(_game)
                SizedBox(
                  width: double.infinity,
                  child: FilledButton(
                  onPressed: Popitka,
                  child: Text('Проверить', style: TextStyle(fontSize: 20)),
                  ),
                ),
                if(!_game && _attemps > 5)
                  Text(_message, style: TextStyle(fontSize: 22, color: Colors.red))
                else if(!_game && _attemps <= 5)
                  Text(_message, style: TextStyle(fontSize: 22, color: Colors.green)),
                const SizedBox(height: 20),
                IconButton(onPressed: _startGame, icon: Icon(Icons.refresh), iconSize: 50),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
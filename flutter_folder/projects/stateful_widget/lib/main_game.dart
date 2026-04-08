import 'package:flutter/material.dart';
import 'dart:math';

class NumGame extends StatefulWidget{
  const NumGame({super.key});

  @override
  State<NumGame> createState() => _NumGameState();
}

class _NumGameState extends State<NumGame> {
  late int _randomSecret; // загаданное число от 0 до 100
  int _attemps = 0; // текущее количество попыток
  final _maxAttemps =10; // максимальное количество попыток
  String _achkych = ''; // подсказка больше или меньше (за донат)
  late int _userNumber; // введеное пользователем число
  bool _game = false; // флаг состояния игры

  final _controller = TextEditingController();

  void _startGame(){
    setState(() {
      _randomSecret = Random().nextInt(101);

      _attemps = 0;
      _achkych = '';
      _controller.clear();
      _game = true;
    });
  }
  @override
  build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(title: Text('Угадывание числа')),
        body: Center(
          child: Padding(
          padding: EdgeInsets.all(10),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text("Диапозон от 0 до 1000000000",
              style: TextStyle(fontSize: 24, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 16),
              Text(
                "🍾Симпл-димплки: 1/3🦭",
                style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold)
              ),
              SizedBox(height: 16),
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
              SizedBox(
                width: double.infinity,
                child: FilledButton(
                  onPressed: () => (),
                  child: Text('Проверить', style: TextStyle(fontSize: 20)),
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
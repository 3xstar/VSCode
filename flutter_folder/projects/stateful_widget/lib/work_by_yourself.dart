import 'package:flutter/material.dart';
import 'package:stateful_widget/main.dart';

void main() => runApp(const MyApp());
class MyApp extends StatelessWidget
{
  const MyApp({super.key});
  @override
  Widget build(BuildContext context) => MaterialApp(home: const CounterScreen());
}

class CounterScreen extends StatefulWidget{
  const CounterScreen({super.key});

  @override
  State<CounterScreen> createState() => _CounterScreenState();
}

class _CounterScreenState extends State<CounterScreen> {
  int _count = 0;
  final List<String> _log = [];

  void _add(){
    setState((){
      _count++;
      _log.add("Шаг ${_log.length + 1}");
    });
  }

  void _reset(){
    setState(() {
      _count = 0;
      _log.clear();
    });
  }
  
  @override
  Widget build(BuildContext context) => Scaffold(
    appBar: AppBar(title: const Text('Счетчик')),
    body: Center(child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
      Text('$_count', style: Theme.of(context).textTheme.headlineMedium),
      const SizedBox(height: 16),
      Expanded(child: ListView.builder(itemCount: _log.length, itemBuilder: (_, i) => Text(_log[i]))),
    ])),
    floatingActionButton: Row(mainAxisAlignment: MainAxisAlignment.end, children: [
      FloatingActionButton(onPressed: _reset, child: const Icon(Icons.refresh)),
      const SizedBox(width: 8),
      FloatingActionButton(onPressed: _add, child: const Icon(Icons.add)),
    ]),
  );
}

// Ошибка заключалась в том что при нажатии кнопки ресета
// сбрасывалось только значение счетчика, но не логи,
// которые оставались на том же значении

// Данная ошибка возникала из-за того что функция _reset()
// выполняла только сброс счетчика до нуля, но не очищала лог

// Мое исправление заключается в банальном добавлении log.clear()
// оно работает потому что это встроенная функция для автоматического очищения
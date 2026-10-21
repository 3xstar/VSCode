import 'package:flutter/material.dart';

class BasicApp extends StatelessWidget {
  const BasicApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Навигация наложением',
      home: ShowColorScreen(),
    );
  }
}

class ShowColorScreen extends StatefulWidget {
  const ShowColorScreen({super.key});

  @override
  State<ShowColorScreen> createState() => _ShowColorScreenState();
}

class _ShowColorScreenState extends State<ShowColorScreen> {
  Color _color = Colors.grey;

  void _pickColor() async {
    final Color? chosenColor = await Navigator.push(context, 
      MaterialPageRoute(builder: (context) => const PickColorScreen()),
    );

    if (chosenColor != null) {
      setState(() {
        _color = chosenColor;
      });
    }
  }

  @override
  Widget build(BuildContext content) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Выбранный цвет'),
      ),
      body: Center(
        child: Column(
          children: [
            Text('Выбранный цвет:'),
            Container(
              width: 50,
              height: 50,
              color: _color,
            ),
            ElevatedButton(
              onPressed: _pickColor,
              child: Text('Перейти на экран выбора цвета')
            )
          ],
        )
      ),
    );
  }
}


class PickColorScreen extends StatelessWidget {
  const PickColorScreen({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Выберите цвет'),
      ),
      body: Center(
        child: Column(
          children: [
            ElevatedButton(
              onPressed: () {
                Navigator.pop(context, Colors.red);
              },
              style: ElevatedButton.styleFrom(backgroundColor: Colors.red), 
              child: Text('красный'),
            ),
          ],
        ),
      ),
    );
  }
}
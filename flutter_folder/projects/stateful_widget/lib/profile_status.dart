import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';

class ProfileStatus extends StatefulWidget {
  const ProfileStatus({super.key});

  @override
  State<ProfileStatus> createState() => _ProfileStatusState();
}


class _ProfileStatusState extends State<ProfileStatus> {
  final List<String> _statuses = [
    'Отдыхаю',
    'Работаю',
    'В отпуске',
    'Не в сети'
  ];

  final List<Color> _colorstatuses = [
    Colors.green,
    Colors.blue,
    Colors.orange,
    Colors.grey
  ];

  int _currentIndex = 0;
  Color _backgroundColor = Colors.white;

  void _cycleStatus(){
    setState(() {

      _currentIndex = (_currentIndex + 1) % _statuses.length;
    });
  }

  void _ColorChange(Color newColor){
    setState(() {
      _backgroundColor = newColor;
    });
  }

  @override
  Widget build(BuildContext context){
  return MaterialApp(
    debugShowCheckedModeBanner: false,
    home:Scaffold(
  backgroundColor: _backgroundColor,
  appBar: AppBar(
    title: const Text('Профиль (цикличный статус)'),
    backgroundColor: Colors.indigo,
  ),
  body: Center(
    child: Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        GFCard(
          title:GFListTile(
            avatar: const GFAvatar(
              child: Icon(Icons.person),
            ),
            color: _colorstatuses[_currentIndex],
          title: const Text(
            'Светлана',
            style: TextStyle(fontWeight: FontWeight.bold),
          ),
          subTitle: const Text('Преподаватель математики'),
        ),
        content: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 8.0),
          child: Text(
            'Текущий статус: ${_statuses[_currentIndex]}',
            style: const TextStyle(fontSize: 16),
        ),
      ),
    ),

    const SizedBox(height: 20),

    GFButton(
      onPressed: _cycleStatus,
      text: "Сменить статус",
      type: GFButtonType.outline,
      blockButton: true,
    ),
    GFButton(
      onPressed: () => _ColorChange(Colors.grey),
      text: "Поменять цвет фона на серый",
      type: GFButtonType.outline,
      blockButton: true,
    ),
    GFButton(
      onPressed: () => _ColorChange(Colors.cyanAccent),
      text: "Поменять цвет фона на голубой",
      type: GFButtonType.outline,
      blockButton: true,
    ),
    GFButton(
      onPressed: () => _ColorChange(Colors.black),
      text: "Поменять цвет фона на черный",
      type: GFButtonType.outline,
      blockButton: true,
    ),

  ],
),
),
),
);
}
}
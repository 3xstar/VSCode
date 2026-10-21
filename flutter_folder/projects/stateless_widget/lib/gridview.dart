import 'package:flutter/material.dart';

class IconGridView extends StatelessWidget{
  const IconGridView({super.key});

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(title: Text('Панель приложений')),
        body: GridView.count(
          crossAxisCount: 4,
          crossAxisSpacing: 10,
          mainAxisSpacing: 10,
          padding: EdgeInsets.all(15),
          children: [
            _builderItem(Icons.home, 'Главная'),
            _builderItem(Icons.search, 'Поиск'),
            _builderItem(Icons.notifications, 'Уведомления'),
            _builderItem(Icons.person, 'Профиль'),
            _builderItem(Icons.settings, 'Настройки'),
            _builderItem(Icons.favorite, 'Избранное'),
            _builderItem(Icons.message, 'Сообщения'),
            _builderItem(Icons.calendar_today, 'Календарь'),
          ], 
        )
      ),
    );
  }
  Widget _builderItem(IconData icon, String label){
    return Column(
      children: [
        Container(
          width: 60,
          height: 60,
          decoration: BoxDecoration(
            color: Colors.blueGrey,
            borderRadius: BorderRadius.circular(8),
          ),
          child: Icon(
            icon,
            color: Colors.cyan,
            size: 30,
          ),
        ),

        const SizedBox(height: 5),

        Text(
          label,
          style: const TextStyle(fontSize: 12),
          textAlign: TextAlign.center,
        )
      ],
    );
  }
}

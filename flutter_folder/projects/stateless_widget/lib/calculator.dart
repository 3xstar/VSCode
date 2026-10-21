import 'package:flutter/material.dart';

class IconGridView extends StatelessWidget{
  const IconGridView({super.key});

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(title: Text('Калькулятор')),
        body: GridView.count(
          crossAxisCount: 4,
          crossAxisSpacing: 10,
          mainAxisSpacing: 10,
          padding: EdgeInsets.all(15),
          children: [
            _builderItem('C', Colors.grey),
            _builderItem('±', Colors.grey),
            _builderItem('%', Colors.grey),
            _builderItem('÷', Colors.lightBlueAccent),
            _builderItem('7', Colors.grey),
            _builderItem('8', Colors.grey),
            _builderItem('9', Colors.grey),
            _builderItem('×', Colors.lightBlueAccent),
            _builderItem('4', Colors.grey),
            _builderItem('5', Colors.grey),
            _builderItem('6', Colors.grey),
            _builderItem('-', Colors.lightBlueAccent),
            _builderItem('1', Colors.grey),
            _builderItem('2', Colors.grey),
            _builderItem('3', Colors.grey),
            _builderItem('+', Colors.lightBlueAccent),
            _builderItem(',', Colors.grey),
            _builderItem('0', Colors.grey),
            _builderItem('.', Colors.grey),
            _builderItem('=', Colors.lightBlueAccent),
          ], 
        )
      ),
    );
  }
  Widget _builderItem(String label, Color color){
    return Column(
      children: [
        Container(
          width: 105,
          height: 105,
          decoration: BoxDecoration(
            color: color,
            borderRadius: BorderRadius.circular(8),
          ),
          child: Center(
            child: Text(label, style: TextStyle(fontSize: 50)),
          ),
        ),
      ],
    );
  }
}

import 'package:flutter/material.dart';

void main() {
  runApp(ListApp());
}

class ListApp extends StatelessWidget {
  ListApp({super.key});

  final List<String> items = List.generate(30, (index) => 'Элемент $index');

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: ListView(
          children: ListTile.divideTiles(
            context: context,
            tiles: items.map((item) => ListTile(
              leading: CircleAvatar(),
              title: Text(item),
              subtitle: Text("Какое-то там описание"),
          ))
        ).toList(),
      ),
      ),
    );
  }
}
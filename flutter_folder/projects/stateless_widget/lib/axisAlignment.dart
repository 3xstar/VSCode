import 'package:flutter/material.dart';

class NameApp extends StatelessWidget {
  const NameApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Center(
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            crossAxisAlignment: CrossAxisAlignment.center,
            children: const[
              Icon(Icons.star, size: 70),
              Text("Текст для центра"),
              Text("Рейтинг"),
            ]
          )
        )
        // вот тут контент
      ),
    );
  }
}
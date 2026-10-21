import 'package:flutter/material.dart';

class FirstApp extends StatelessWidget {
  const FirstApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        backgroundColor: const Color.fromARGB(255, 29, 255, 255),
        appBar: AppBar(
          backgroundColor: const Color.fromARGB(255, 255, 255, 255),
          title: const Text('MY FIRST FLUTTER APP'),
        ),

        body: const Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Text(
                'Пу пу пуууу',
                style: TextStyle(fontSize: 30),
              ),
              Text(
                'Это текст первого приложения',
                style: TextStyle(fontSize: 35),
              ),
              Icon(
                Icons.keyboard,
                color: Color.fromARGB(185, 80, 80, 80),
                size: 100.0,
              ),
              Text(
                'Соловьев Захар Олегович',
                style: TextStyle(fontSize: 40),
              ),
            ],
          )
        ) 
      )
    );
  }
}
  import 'package:flutter/material.dart';

  class NameApp extends StatelessWidget {
    const NameApp({super.key});

    @override
    Widget build(BuildContext context) {
      return MaterialApp(
        debugShowCheckedModeBanner: false,
        home: Scaffold(
          backgroundColor: Colors.cyan[50],
          appBar: AppBar(
            backgroundColor: Colors.cyan,
            title: const Text("Визитка")
          ),
          body: Padding(
            padding: const EdgeInsets.only(top:40),
            child: Align(
              alignment: Alignment.topCenter,
              child: Container(
                margin: const EdgeInsets.all(20),
                padding: const EdgeInsets.all(20),
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(10),
                ),
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Row(
                      children: [
                        const Text("Работник месяца", style: TextStyle(fontSize: 20, color: Colors.cyan,)),
                        Spacer(),
                        Icon(Icons.grade, color: Colors.amber, size: 50)
                      ],
                    ),

                    const CircleAvatar(
                      radius: 50,
                      backgroundColor: Colors.cyan,
                      child: Icon(Icons.person, size:80, color: Colors.white),
                    ),

                    SizedBox(height: 30),

                    const Text(
                      'Олег Соловьёв',
                      textAlign: TextAlign.center,
                      style: TextStyle(fontSize: 19),
                    ),
                    const Text(
                      'Программист - бекэндер',
                      textAlign: TextAlign.center,
                      style: TextStyle(fontSize: 18, color: Color.fromARGB(255, 129, 129, 129)),
                    ),

                    Row(
                      mainAxisAlignment: MainAxisAlignment.spaceEvenly,
                      children: [
                        Icon(Icons.phone_android, color: Colors.green, size: 30),
                        Icon(Icons.message, color: Colors.blueGrey, size: 30),
                        Icon(Icons.settings, color: Colors.blue, size: 30),
                      ],
                    ),
                  ],
                ),
              ),
            ),
          )
        ),
      );
  }
}
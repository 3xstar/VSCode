import 'package:flutter/material.dart';

class NameApp extends StatelessWidget {
  const NameApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Padding(
          padding: EdgeInsets.all(0),
          child: Container(
            margin: EdgeInsets.only(top: 50),
            padding: EdgeInsets.all(20),
            color: Colors.black,
            child: Container(
              margin: EdgeInsets.all(20),
              color: Colors.blue,
              width: 100,
              height: 100,
            )
          )
        ),
      ),
    );
  }
}
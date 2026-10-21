import 'package:flutter/material.dart';

class ProfileApp extends StatelessWidget {
  const ProfileApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        backgroundColor: Colors.grey[200],
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              // Аватар с градиентным фоном
              Stack(
                alignment: Alignment.center,
                children: [
                  // Градиентный круг
                  Container(
                    width: 140,
                    height: 140,
                    decoration: BoxDecoration(
                      shape: BoxShape.circle,
                      gradient: LinearGradient(
                        colors: [Colors.cyanAccent, Colors.blue],
                        begin: Alignment.topLeft,
                        end: Alignment.bottomRight,
                      ),
                    ),
                  ),
                  
                  // Белый бордер
                  Container(
                    width: 130,
                    height: 130,
                    decoration: BoxDecoration(
                      shape: BoxShape.circle,
                      color: Colors.white,
                    ),
                  ),
                  
                  // Аватар
                  CircleAvatar(
                    radius: 60,
                    backgroundImage: AssetImage("assets/channels4_profile.jpg"),
                  ),
                ],
              ),
              
              SizedBox(height: 20), // Отступ между аватаром и информацией
              
              // Карточка с информацией
              Container(
                width: 220,
                padding: EdgeInsets.all(12),
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(15),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.grey.withOpacity(0.3),
                      blurRadius: 10,
                      offset: Offset(0, 5),
                    ),
                  ],
                ),
                child: Stack(
                  children: [
                    Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text(
                          "AW SHUCKS",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            color: Colors.deepOrange
                          ),
                        ),
                        SizedBox(height: 5),
                        Text(
                          'Последний раз в сети:',
                          style: TextStyle(
                            color: const Color.fromARGB(255, 11, 87, 117),
                            fontSize: 15,
                          ),
                        ),
                        Text(
                          '5 убийств назад',
                          style: TextStyle(
                            color: const Color.fromARGB(255, 243, 33, 33),
                            fontWeight: FontWeight.bold,
                            fontSize: 14,
                          ),
                        ),
                      ],
                    ),
                    
                    // Бейдж с цифрой 3
                    Positioned(
                      top: 0,
                      right: 0,
                      child: Container(
                        width: 30,
                        height: 30,
                        decoration: BoxDecoration(
                          color: const Color.fromARGB(255, 212, 25, 12),
                          shape: BoxShape.circle,
                        ),
                        child: Center(
                          child: Text(
                            '3',
                            style: TextStyle(
                              color: Colors.white,
                              fontWeight: FontWeight.bold,
                              fontSize: 16,
                            ),
                          ),
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
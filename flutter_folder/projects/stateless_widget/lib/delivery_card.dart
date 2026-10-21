import 'package:flutter/material.dart';

class CardApp extends StatelessWidget {
  const CardApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Column(
          children: [
            Container(
              margin: EdgeInsets.all(20),
              padding: EdgeInsets.all(15),
              decoration: BoxDecoration(
                gradient: LinearGradient(colors: [Colors.yellow, Colors.cyanAccent],),
                borderRadius: BorderRadius.circular(10),
                boxShadow: [
                  BoxShadow(
                      color: Colors.grey,
                      blurRadius: 10,
                    ),
                  ],
                ),
          child: Row(
            children: [
              Container(
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(8),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.black.withOpacity(0.3),
                      blurRadius: 15,
                      spreadRadius: 2,
                      offset: Offset(5, 5),
                    ),
                ],
              ),
              padding: EdgeInsets.all(8),
              child:Text('#2007'),
            ),
            SizedBox(width: 20),
            Expanded(
              child: Text(textAlign: TextAlign.center,
              style: TextStyle(fontWeight: FontWeight.bold,),
              "Доставка пришла! Заберите сегодня")
              ),
            SizedBox(height: 20),
            Column(
              children: [
                Container(
                  decoration: BoxDecoration(
                    color: Colors.white,
                    borderRadius: BorderRadius.circular(8), 
                  ),
                  padding: EdgeInsets.all(10),
                
                child: Column(
                  children: [
                  Text(
                  "2,5 км",
                  style: TextStyle(fontWeight: FontWeight.bold, fontSize: 16)
                    ),
                  SizedBox(height: 3),
                  Text(
                    "до вас",
                    style: TextStyle(color: Colors.grey, fontSize: 12)
                    ),
                  ],
                ),
              ),
            ],
          ),
            SizedBox(width: 10),
            Container(
                padding: EdgeInsets.all(9),
                decoration: BoxDecoration(
                  color: Colors.white,
                  borderRadius: BorderRadius.circular(10),
                  boxShadow: [
                    BoxShadow(
                      color: Colors.black.withOpacity(0.3),
                      blurRadius: 15,
                      offset: Offset(5, 5),
                    ),
                  ]
                ),
                child: Icon(Icons.location_on),
              ),
            ],
          ),
        ),
      ],  
    ),
  ),
); 
}
}
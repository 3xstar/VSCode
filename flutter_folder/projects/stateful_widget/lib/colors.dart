import 'package:flutter/material.dart';

class BasicApp extends StatelessWidget {
  const BasicApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Цвета',
      home: ShowColorScreen(),
    );
  }
}

class ShowColorScreen extends StatefulWidget {
  const ShowColorScreen({super.key});

  @override
  State<ShowColorScreen> createState() => _ShowColorScreenState();
}

class _ShowColorScreenState extends State<ShowColorScreen> {
  final TextEditingController _controller = TextEditingController();

  @override
  void initState(){
    super.initState();
    _controller.text = "Валера молодец";
  }

  @override
  void dispose() {
    _controller.dispose();
    super.dispose();
  }

    void _pickColor() async {
      String textToPass = _controller.text;

      await Navigator.push(context, 
      MaterialPageRoute(builder: (context) => PickColorScreen(userText: textToPass)),
    );
  }

  @override
  Widget build(BuildContext content) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Экран 1: Ввод строки'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            TextField(
              controller: _controller,
              decoration: InputDecoration(
              labelText: 'Текст для передачи',
              border: const OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 20),
            ElevatedButton(
              onPressed: _pickColor,
              child: Text('Перейти на экран 2')
            ),
          ],
        )
      ),
    );
  }
}

class PickColorScreen extends StatefulWidget {
  final String userText;
  
  const PickColorScreen({super.key, required this.userText});

  @override
  State<PickColorScreen> createState() => _PickColorScreenState();
}

class _PickColorScreenState extends State<PickColorScreen>{
  Color _backgroundColor = Colors.lightBlueAccent;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: _backgroundColor,
      appBar: AppBar(
        title: Text('Экран 2: Выбор цвета'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(
            widget.userText,
            style: TextStyle(fontSize: 20, color: Colors.lightBlueAccent
            )),
            const SizedBox(height: 20),

            Row(
                mainAxisAlignment: MainAxisAlignment.spaceEvenly,

                children: [
                  ElevatedButton(
                    onPressed: () {
                      setState(() {
                      _backgroundColor = Colors.redAccent;
                      });
                    },
                    style: ElevatedButton.styleFrom(backgroundColor: Colors.redAccent), 
                    child: Text('red'),
                  ),
                  ElevatedButton(
                    onPressed: () {
                      setState(() {
                      _backgroundColor = Colors.lightGreenAccent;
                      });
                    },
                    style: ElevatedButton.styleFrom(backgroundColor: Colors.lightGreenAccent), 
                    child: Text('green'),
                  ),
                  ElevatedButton(
                    onPressed: () {
                      setState(() {
                      _backgroundColor = Colors.lightBlueAccent;
                      });
                    },
                    style: ElevatedButton.styleFrom(backgroundColor: Colors.lightBlueAccent), 
                    child: Text('blue'),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
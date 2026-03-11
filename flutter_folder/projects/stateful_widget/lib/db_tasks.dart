import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class LocalhostApp extends StatefulWidget {
  const LocalhostApp({super.key});

  @override
  State<LocalhostApp> createState() => _LocalhostAppState();
}

class _LocalhostAppState extends State<LocalhostApp> {
  List<dynamic> _tasks = [];

  bool _isLoading = true;

  @override
  void initState(){
    super.initState();
    _loadTasks();
  }


  Future<void> _loadTasks() async{
    try{
      final responce = await http.get(
        Uri.parse('http://localhost/get_tasks.php'),
      );

      if(responce.statusCode == 200){
        final data = jsonDecode(responce.body);

        setState(() {
          _tasks = data['tasks'];
          _isLoading = false;
        });
      } else {
        print('Ошибка: ${responce.statusCode}');
      }
    } catch (e) {
      print('Ошибка подключения: $e');
    }
  }

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(title: const Text('Задачи с localhost')),

        body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: _tasks.length,

              itemBuilder: (context, index) {
                final task = _tasks[index];

                return ListTile(
                  title: Text(task['title']),
                  subtitle: Text('ID:${task['id']}'),
            );
          },
        ),
      ),
    );
  }
}
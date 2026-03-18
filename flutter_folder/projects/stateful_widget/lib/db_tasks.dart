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
  
  // Создание
  Future <void> _createTask(String title) async{
    await http.post(
      Uri.parse('http://localhost/tasks.php'),
      body: {'action': 'create', 'title': title},
    );
    _loadTasks();
  }

  // Удаление
  Future <void> _deleteTask(int id) async{
    await http.post(
      Uri.parse('http://localhost/tasks.php'),
      body: {'action': 'delete', 'id': id.toString()},
    );
    _loadTasks();
  }

  // Обновление
  Future <void> _updateTask(int id, String title) async{
    await http.post(
      Uri.parse('http://localhost/tasks.php'),
      body: {'action': 'update', 'id': id.toString(), 'title': title},
    );
    _loadTasks();
  }

  void _showTaskDialog({int? id, String? title}) {
    final controller = TextEditingController(text: title ?? '');

    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: Text(id == null ? 'Новая задача' : 'Редактировать'),
        content: TextField(
          controller: controller,
          autofocus: true,
          decoration: const InputDecoration(
            labelText: 'Название',
            border: OutlineInputBorder(),
          ),
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: const Text('Отмена'),
          ),
          TextButton(
            onPressed: () {
              Navigator.pop(context);
              if(id == null){
                _createTask(controller.text);
              } else {
                _updateTask(id, controller.text);
              }
            },
            child: const Text('OK'),
          ),
        ],
      ),
    );
  }

  void _confirmDelete(int id, String title){
    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: const Text('Удалить?'),
        content: Text('"$title"'),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: const Text('Отмена'),
          ),
          TextButton(
            onPressed: () {
              Navigator.pop(context);
              _deleteTask(id);
            }, child: const Text('Удалить', style: TextStyle(color: Colors.red)),
          ),
        ],
      )
    );
  }

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Задачи'),
          actions: [
            IconButton(
              onPressed: () => _showTaskDialog(),
              icon: const Icon(Icons.add)
            ),
          ],
        ),

        body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : ListView.builder(
              itemCount: _tasks.length,

              itemBuilder: (context, index) {
                final task = _tasks[index];
                
                // Безопасное получение id как int
                final int id = task['id'] is int 
                    ? task['id'] 
                    : int.tryParse(task['id'].toString()) ?? 0;

                return ListTile(
                  title: Text(task['title']?.toString() ?? 'Без названия'),
                  subtitle: Text('ID: $id'),
                  
                  onTap: () => _showTaskDialog(id: id, title: task['title']),
                  trailing: IconButton(
                    onPressed: () => _confirmDelete(id, task['title']),
                    icon: const Icon(Icons.delete, color: Colors.red),
                  ),
                );
              },
            ),
          ),
        );
      }
    }
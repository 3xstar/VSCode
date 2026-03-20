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
  
  // === НОВОЕ: Переменная для сортировки ===
  String _sortBy = 'id_desc'; // id_desc, id_asc, title_asc, title_desc

  @override
  void initState(){
    super.initState();
    _loadTasks();
  }

  Future<void> _loadTasks() async{
    try{
      final response = await http.post(
        Uri.parse('http://localhost/get_tasks.php'),
        body: {'action': 'read', 'sort': _sortBy}, // === ОТПРАВЛЯЕМ ПАРАМЕТР СОРТИРОВКИ ===
      );

      if(response.statusCode == 200){
        final data = jsonDecode(response.body);
        setState(() {
          _tasks = data['tasks'];
          _isLoading = false;
        });
      } else {
        print('Ошибка: ${response.statusCode}');
      }
    } catch (e) {
      print('Ошибка подключения: $e');
    }
  }
  
  // === НОВОЕ: Переключение сортировки ===
  void _toggleSort() {
    setState(() {
      if (_sortBy == 'id_desc') _sortBy = 'id_asc';
      else if (_sortBy == 'id_asc') _sortBy = 'title_asc';
      else if (_sortBy == 'title_asc') _sortBy = 'title_desc';
      else _sortBy = 'id_desc';
    });
    _loadTasks();
  }
  
  // Создание
  Future <void> _createTask(String title, String description) async{ // === ДОБАВЛЕН ОПИСАНИЕ ===
    await http.post(
      Uri.parse('http://localhost/get_tasks.php'),
      body: {'action': 'create', 'title': title, 'description': description}, // === ОТПРАВЛЯЕМ ОПИСАНИЕ ===
    );
    _loadTasks();
  }

  // Удаление
  Future <void> _deleteTask(int id) async{
    await http.post(
      Uri.parse('http://localhost/get_tasks.php'),
      body: {'action': 'delete', 'id': id.toString()},
    );
    _loadTasks();
  }

  // Обновление
  Future <void> _updateTask(int id, String title, String description) async{ // === ДОБАВЛЕН ОПИСАНИЕ ===
    await http.post(
      Uri.parse('http://localhost/get_tasks.php'),
      body: {'action': 'update', 'id': id.toString(), 'title': title, 'description': description}, // === ОТПРАВЛЯЕМ ОПИСАНИЕ ===
    );
    _loadTasks();
  }

  void _showTaskDialog({int? id, String? title, String? description}) { // === ДОБАВЛЕН ОПИСАНИЕ ===
    final titleController = TextEditingController(text: title ?? '');
    final descController = TextEditingController(text: description ?? ''); // === КОНТРОЛЛЕР ДЛЯ ОПИСАНИЯ ===

    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: Text(id == null ? 'Новая задача' : 'Редактировать'),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: titleController,
              autofocus: true,
              decoration: const InputDecoration(
                labelText: 'Название',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 10), // === ПОЛЕ ДЛЯ ОПИСАНИЯ ===
            TextField(
              controller: descController,
              maxLines: 3,
              decoration: const InputDecoration(
                labelText: 'Описание',
                border: OutlineInputBorder(),
              ),
            ),
          ],
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
                _createTask(titleController.text, descController.text); // === ПЕРЕДАЕМ ОПИСАНИЕ ===
              } else {
                _updateTask(id, titleController.text, descController.text); // === ПЕРЕДАЕМ ОПИСАНИЕ ===
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
            // === НОВОЕ: Кнопка сортировки ===
            IconButton(
              onPressed: _toggleSort,
              icon: Icon(
                _sortBy == 'id_desc' || _sortBy == 'id_asc' 
                    ? Icons.sort_by_alpha 
                    : Icons.numbers,
              ),
              tooltip: _sortBy == 'id_desc' ? 'По дате (новые)' : 
                       _sortBy == 'id_asc' ? 'По дате (старые)' :
                       _sortBy == 'title_asc' ? 'По алфавиту (А–Я)' : 'По алфавиту (Я–А)',
            ),
            // Кнопка добавления
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
                
                final int id = task['id'] is int 
                    ? task['id'] 
                    : int.tryParse(task['id'].toString()) ?? 0;

                return ListTile(
                  title: Text(task['title']?.toString() ?? 'Без названия'),
                  // === ИЗМЕНЕНО: Показываем описание вместо ID ===
                  subtitle: Text(task['description']?.toString() ?? 'Нет описания'),
                  
                  onTap: () => _showTaskDialog(
                    id: id, 
                    title: task['title'],
                    description: task['description'] // === ПЕРЕДАЕМ ОПИСАНИЕ ===
                  ),
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

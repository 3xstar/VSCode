import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

class LocalhostApp extends StatefulWidget {
  const LocalhostApp({super.key});

  @override
  State<LocalhostApp> createState() => _LocalhostAppState();
}

class _LocalhostAppState extends State<LocalhostApp> {
  List<dynamic> _students = [];
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _loadStudents();
  }

  Future<void> _loadStudents() async {
    try {
      final response = await http.post(
        Uri.parse('http://localhost/students.php'),
        body: {'action': 'read'},
      );

      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);

        if (data['success'] == true) {
          setState(() {
            _students = data['data'] ?? [];
            _isLoading = false;
          });
        } else {
          print('Ошибка сервера: ${data}');
          setState(() => _isLoading = false);
        }
      } else {
        print('Ошибка HTTP: ${response.statusCode}');
        setState(() => _isLoading = false);
      }
    } catch (e) {
      print('Ошибка подключения: $e');
      setState(() => _isLoading = false);
    }
  }

  Future<void> _createStudent(String name, String group_num, double average_score) async {
    await http.post(
      Uri.parse('http://localhost/students.php'),
      body: {
        'action': 'create',
        'name': name,
        'group_num': group_num,
        'average_score': average_score.toString(),
      },
    );
    _loadStudents();
  }

  Future<void> _updateStudent(String name, String group_num, double average_score, int id) async {
    await http.post(
      Uri.parse('http://localhost/students.php'),
      body: {
        'action': 'update',
        'name': name,
        'group_num': group_num,
        'average_score': average_score.toString(),
        'id': id.toString(),
      },
    );
    _loadStudents();
  }

  Future<void> _deleteStudent(int id) async {
    await http.post(
      Uri.parse('http://localhost/students.php'),
      body: {
        'action': 'delete',
        'id': id.toString(),
      },
    );
    _loadStudents();
  }

  void _showTaskDialog({
    int? id,
    String? name,
    String? group_num,
    dynamic average_score, // Может прийти как String или double из JSON
  }) {
    final nameController = TextEditingController(text: name ?? '');
    final groupController = TextEditingController(text: group_num ?? '');
    
    // Безопасное преобразование оценки в строку
    String scoreText = '';
    if (average_score != null) {
      if (average_score is double) {
        scoreText = average_score.toString();
      } else {
        scoreText = average_score.toString();
      }
    }
    final scoreController = TextEditingController(text: scoreText);

    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: Text(id == null ? 'Новый студент' : 'Редактировать'),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: nameController,
              autofocus: true, // Только первое поле
              decoration: const InputDecoration(
                labelText: 'Имя',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 10),
            TextField(
              controller: groupController,
              decoration: const InputDecoration(
                labelText: 'Группа',
                border: OutlineInputBorder(),
              ),
            ),
            const SizedBox(height: 10),
            TextField(
              controller: scoreController,
              keyboardType: TextInputType.number,
              decoration: const InputDecoration(
                labelText: 'Средний балл',
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
              double newScore = double.tryParse(scoreController.text) ?? 0.0;

              if (id == null) {
                _createStudent(nameController.text, groupController.text, newScore);
              } else {
                _updateStudent(nameController.text, groupController.text, newScore, id);
              }
            },
            child: const Text('OK'),
          ),
        ],
      ),
    );
  }

  void _confirmDelete(int id, String name) {
    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: const Text('Удалить?'),
        content: Text('"$name"'),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: const Text('Отмена'),
          ),
          TextButton(
            onPressed: () {
              Navigator.pop(context);
              _deleteStudent(id);
            },
            child: const Text('Удалить', style: TextStyle(color: Colors.red)),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Студенты'),
          actions: [
            IconButton(
              onPressed: () => _showTaskDialog(),
              icon: const Icon(Icons.add),
            ),
          ],
        ),
        body: _isLoading
            ? const Center(child: CircularProgressIndicator())
            : ListView.builder(
                itemCount: _students.length,
                itemBuilder: (context, index) {
                  final student = _students[index];

                  // Безопасное получение данных
                  final int id = student['id'] is int
                      ? student['id']
                      : int.tryParse(student['id'].toString()) ?? 0;
                  
                  final String name = student['name']?.toString() ?? 'Без имени';
                  final String group = student['group_num']?.toString() ?? '';
                  final dynamic score = student['average_score'];

                  return ListTile(
                    title: Text(name),
                    subtitle: Text('Группа: $group | Балл: $score'), // Показываем больше данных
                    onTap: () => _showTaskDialog(
                      id: id,
                      name: name,
                      group_num: group,       // ПЕРЕДАЕМ ГРУППУ
                      average_score: score,   // ПЕРЕДАЕМ ОЦЕНКУ
                    ),
                    trailing: IconButton(
                      onPressed: () => _confirmDelete(id, name),
                      icon: const Icon(Icons.delete, color: Colors.red),
                    ),
                  );
                },
              ),
      ),
    );
  }
}
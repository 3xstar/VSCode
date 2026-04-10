import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';
import 'package:image_picker/image_picker.dart';
import 'dart:typed_data'; // Для Uint8List
import 'package:flutter/foundation.dart' show kIsWeb; // Для проверки платформы

// ==================== ТОЧКА ВХОДА ====================
class NotesDB extends StatelessWidget {
  const NotesDB({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: const NotesDBHome(),
    );
  }
}

// ==================== ГЛАВНЫЙ ЭКРАН ====================
class NotesDBHome extends StatefulWidget {
  const NotesDBHome({super.key});

  @override
  State<NotesDBHome> createState() => _NotesDBHomeState();
}

class _NotesDBHomeState extends State<NotesDBHome> {
  int _currentIndex = 0;
  late final List<Widget> _screens;

  @override
  void initState() {
    super.initState();
    _screens = const [AllNotesScreen(), FavoritesNotesScreen(), ProfileScreen()];
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _screens[_currentIndex],
      bottomNavigationBar: BottomNavigationBar(
        currentIndex: _currentIndex,
        onTap: (index) => setState(() => _currentIndex = index),
        type: BottomNavigationBarType.fixed,
        items: const [
          BottomNavigationBarItem(icon: Icon(Icons.list), label: 'Все заметки'),
          BottomNavigationBarItem(icon: Icon(Icons.star), label: 'Избранное'),
          BottomNavigationBarItem(icon: Icon(Icons.person_2), label: 'Профиль'),
        ],
      ),
    );
  }
}

class AllNotesScreen extends StatefulWidget {
  const AllNotesScreen({super.key});

  @override
  State<AllNotesScreen> createState() => _AllNotesScreenState();
}

class _AllNotesScreenState extends State<AllNotesScreen> {
  List<dynamic> _tasks = [];
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _loadTasks();
  }

  // Загрузка заметок
  Future<void> _loadTasks() async {
    setState(() => _isLoading = true);
    try {
      final response = await http.post(
        Uri.parse('http://localhost/tasks_2.php'),
        body: {'action': 'read'},
      );
      final data = jsonDecode(response.body);
      setState(() {
        _tasks = data['tasks'] ?? [];
        _isLoading = false;
      });
    } catch (e) {
      setState(() => _isLoading = false);
      debugPrint('Ошибка: $e');
    }
  }

  // Добавление
  Future<void> _createTask(String title) async {
    await http.post(
      Uri.parse('http://localhost/tasks_2.php'),
      body: {'action': 'create', 'title': title},
    );
    _loadTasks();
  }

  // Удаление
  Future<void> _deleteTask(int id) async {
    await http.post(
      Uri.parse('http://localhost/tasks_2.php'),
      body: {'action': 'delete', 'id': id.toString()},
    );
    _loadTasks();
  }

  // Редактирование
  Future<void> _updateTask(int id, String title) async {
    await http.post(
      Uri.parse('http://localhost/tasks_2.php'),
      body: {'action': 'update', 'id': id.toString(), 'title': title},
    );
    _loadTasks();
  }

  // добавление в избранное
  Future<void> _favoriteTask(int id) async {
    await http.post(
      Uri.parse('http://localhost/tasks_2.php'),
      body: {'action': 'toggle_favorite', 'id': id.toString()},
    );
    _loadTasks();
  }

  // Диалог добавления/редактирования
  void _showTaskDialog({int? id, String? title}) {
    final controller = TextEditingController(text: title ?? '');
    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: Text(id == null ? 'Новая заметка' : 'Редактировать'),
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
              if (id == null) {
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

  // Подтверждение удаления
  void _confirmDelete(int id, String title) {
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
            },
            child: const Text('Удалить', style: TextStyle(color: Colors.red)),
          ),
        ],
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Задачи'),
        actions: [
          IconButton(
            icon: const Icon(Icons.add),
            onPressed: () => _showTaskDialog(),
          ),
        ],
      ),
      body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : _tasks.isEmpty
          ? const Center(child: Text('Нет заметок'))
          : ListView.builder(
              itemCount: _tasks.length,
              itemBuilder: (context, index) {
                final task = _tasks[index];
                final id = int.parse(task['id'].toString());
                return ListTile(
                  title: Text(task['title']),
                  subtitle: Text('ID: ${task['id']}'),
                  onTap: () => _showTaskDialog(id: id, title: task['title']),
                  trailing: Row(
                    mainAxisSize: MainAxisSize.min,
                    children: [
                      IconButton(
                        icon: Icon(
                          // Если 1 - желтая закрашенная, если 0 - серая контурная
                          (task['is_favorite'] == 1 || task['is_favorite'] == '1') 
                              ? Icons.star 
                              : Icons.star_border,
                          color: (task['is_favorite'] == 1 || task['is_favorite'] == '1') 
                              ? Colors.amber 
                              : Colors.grey,
                        ),
                        onPressed: () => _favoriteTask(id), 
                        ),
                        IconButton(
                          icon: const Icon(Icons.delete, color: Colors.red),
                          onPressed: () => _confirmDelete(id, task['title']),
                        ),
                      ],
                    ),
                  );
                },
              ),
            );
  }
}

class FavoritesNotesScreen extends StatefulWidget {
  const FavoritesNotesScreen({super.key});

  @override
  State<FavoritesNotesScreen> createState() => _FavoritesNotesScreenState();
}

class _FavoritesNotesScreenState extends State<FavoritesNotesScreen> {
  List<dynamic> _tasks = [];
  bool _isLoading = true;

  @override 
  void initState() {
    super.initState();
    _loadTasks();
  }

  Future<void> _loadTasks() async {
    setState(() => _isLoading = true);
    try {
      final response = await http.post(
        Uri.parse('http://localhost/tasks_2.php'),
        body: {'action': 'read', 'favorite': 'true'},
      );
      final data = jsonDecode(response.body);
      setState(() {
        _tasks = data['tasks'] ?? [];
        _isLoading = false;
      });
    } catch (e) {
      setState(() => _isLoading = false);
      debugPrint('Ошибка: $e');
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Избранное')),
      body: _isLoading ? Center(child: CircularProgressIndicator()) : _tasks.isEmpty ? Center(child: Text('Нет избранных заметок')) 
      : ListView.builder(
        itemCount: _tasks.length,
        itemBuilder: (context, index) {
          final task = _tasks[index];
          return ListTile(
            leading: Icon(Icons.star, color: Colors.amber,),
            title: Text(task['title']),
            subtitle: Text('ID: ${task['id']}'),
          );
        },
      )
    );
  }
}


class ProfileScreen extends StatefulWidget {
  const ProfileScreen({super.key});

  @override
  State<ProfileScreen> createState() => _ProfileScreenState();
}

class _ProfileScreenState extends State<ProfileScreen> {
  String _name = '';
  String _avatar = 'default.png';
  bool _isLoading = true;

  // 🔹 Базовый URL API — меняйте под вашу настройку
  String get _baseUrl {
    if (kIsWeb) {
      // Для Web: используйте IP или 127.0.0.1 с портом
      // Если PHP на порту 80 (стандартный):
      return 'http://127.0.0.1';
      // Если PHP на порту 8080 (XAMPP по умолчанию):
      // return 'http://127.0.0.1:8080';
    } else {
      // Для мобильных устройств
      // Android Emulator:
      return 'http://10.0.2.2';
      // iOS Simulator:
      // return 'http://localhost';
    }
  }

  @override 
  void initState() {
    super.initState();
    _loadProfile();
  }

  // 🔹 Загрузка профиля
  Future<void> _loadProfile() async {
    try {
      final response = await http.post(
        Uri.parse('$_baseUrl/profile.php'),
        body: {'action': 'get_profile'},
      );
      
      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['user'] != null) {
          setState(() {
            _name = data['user']['name'] ?? 'Гость';
            _avatar = data['user']['avatar'] ?? 'default.png';
            _isLoading = false;
          });
        } else {
          setState(() => _isLoading = false);
          debugPrint('❌ Ошибка структуры ответа: $data');
        }
      } else {
        setState(() => _isLoading = false);
        debugPrint('❌ HTTP ${response.statusCode}: ${response.body}');
      }
    } catch (e) {
      setState(() => _isLoading = false);
      debugPrint('❌ Исключение: $e');
    }
  }

  // 🔹 Загрузка аватарки (универсальная для Web и Mobile)
  Future<void> _pickAvatar() async {
    try {
      final picker = ImagePicker();
      final XFile? image = await picker.pickImage(source: ImageSource.gallery);

      if (image == null) return; // Пользователь отменил выбор

      final request = http.MultipartRequest(
        'POST',
        Uri.parse('$_baseUrl/profile.php'),
      );
      request.fields['action'] = 'upload_avatar';

      // 🔸 Ключевое различие: Web vs Mobile
      if (kIsWeb) {
        // 🌐 Web: читаем файл в память как байты
        final Uint8List imageBytes = await image.readAsBytes();
        final multipartFile = http.MultipartFile.fromBytes(
          'avatar',
          imageBytes,
          filename: image.name,
        );
        request.files.add(multipartFile);
      } else {
        // 📱 Mobile: используем путь к файлу
        final multipartFile = await http.MultipartFile.fromPath(
          'avatar',
          image.path,
        );
        request.files.add(multipartFile);
      }

      // Отправляем запрос
      final streamedResponse = await request.send();
      final response = await http.Response.fromStream(streamedResponse);

      if (response.statusCode == 200) {
        final data = jsonDecode(response.body);
        if (data['success'] == true) {
          if (mounted) {
            _loadProfile(); // Обновляем данные профиля
            _showSnackBar('✅ Аватарка обновлена', Colors.green);
          }
        } else {
          _showSnackBar('❌ Ошибка: ${data['error'] ?? 'Неизвестная'}', Colors.red);
        }
      } else {
        _showSnackBar('❌ Сервер вернул код ${response.statusCode}', Colors.red);
      }
    } catch (e) {
      debugPrint('❌ Ошибка загрузки: $e');
      _showSnackBar('❌ Ошибка: $e', Colors.red);
    }
  }

  // 🔹 Вспомогательный метод для показа уведомлений
  void _showSnackBar(String message, Color bgColor) {
    if (mounted) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(
          content: Text(message),
          backgroundColor: bgColor,
          behavior: SnackBarBehavior.floating,
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Профиль')),
      body: _isLoading 
        ? const Center(child: CircularProgressIndicator()) 
        : Center(
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                // 🔹 Аватарка с обработкой ошибок загрузки
                CircleAvatar(
                  radius: 200,
                  backgroundColor: Colors.grey[200],
                  backgroundImage: NetworkImage('$_baseUrl/notes_avatars/$_avatar'),
                ),
                const SizedBox(height: 16),
                Text(
                  _name,
                  style: const TextStyle(fontSize: 30, fontWeight: FontWeight.bold),
                ),
                const SizedBox(height: 16),
                ElevatedButton.icon(
                  onPressed: _pickAvatar,
                  icon: const Icon(Icons.camera_alt),
                  label: const Text('Изменить аватарку'),
                ),
              ],
            ),
          ),
    );
  }
}
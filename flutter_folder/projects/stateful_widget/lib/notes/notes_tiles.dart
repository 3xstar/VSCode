// clang-format off
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

// ==================== ТОЧКА ВХОДА ====================
class NotesTilesApp extends StatelessWidget {
  const NotesTilesApp({super.key});
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: const NotesTilesHome(),
    );
  }
}

// ==================== ГЛАВНЫЙ ЭКРАН ====================
class NotesTilesHome extends StatefulWidget {
  const NotesTilesHome({super.key});

  @override
  State<NotesTilesHome> createState() => _NotesTilesHomeState();
}

class _NotesTilesHomeState extends State<NotesTilesHome> {
  List<dynamic> _notes = [];
  bool isLoading = true;

  @override
  void initState(){
    super.initState();
    _loadNotes();
  }

  Future<void> _loadNotes() async {
    final response = await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {'action': 'read'},
    );
    final data = jsonDecode(response.body);
    setState(() {
      _notes = data['notes'];
      isLoading = false;
    });
  }

  Future<void> _createNotes(String title, String text, String color) async {
    await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {'action': 'create', 'title': title, 'text': text, 'color': color},
    );
    _loadNotes();
  }

  Future<void> _deleteNote(int id) async{
    await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {'action': 'delete', 'id': id.toString()},
    );
    _loadNotes();
  }

  Future<void> _updateNote(int id, String title) async {
    await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {'action': 'update', 'id': id.toString(), 'title': title},
    );
    _loadNotes();
  }

  void _showDialog({int? id, String? title, String? text, String? color}) {
    final controllerTitle = TextEditingController(text: title ?? '');
    final controllerText = TextEditingController(text: text ?? '');
    String selectedColor = color ?? 'red';

    showDialog(
      context: context,
      builder: (_) => StatefulBuilder(
        builder: (context, set) => AlertDialog(
          title: Text(id == null ? 'Новая заметка' : 'Редактирование'),
          content: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              TextField(
                controller: controllerTitle,
                decoration: InputDecoration(labelText: 'Заголовок'),
              ),
              TextField(
                controller: controllerText,
                decoration: InputDecoration(labelText: 'Текст'),
                maxLines: 3,
              ),
              const SizedBox(height: 8),
              Wrap(
                spacing: 6,
                children: _colors.entries
                    .map(
                      (e) => GestureDetector(
                        onTap: () => set(() => selectedColor = e.key),
                        child: Container(
                          width: 20,
                          height: 20,
                          decoration: BoxDecoration(
                            color: e.value,
                            shape: BoxShape.circle,
                            border: Border.all(color: Colors.black, width: 1),
                          ),
                        ),
                      ),
                    )
                    .toList(),
              ),
            ],
          ),
          actions: [
            TextButton(
              onPressed: () => Navigator.pop(context),
              child: Text('Отмена'),
            ),
            FilledButton(
              onPressed: () {
                Navigator.pop(context);
                if (id == null) {
                  _createNotes(
                    controllerTitle.text,
                    controllerText.text,
                    selectedColor,
                  );
                } else {
                  //_updateNotes(controllerTitle.text, controllerText.text, selectedColor);
                }
              },
              child: Text('OK'),
            ),
          ],
        ),
      ),
    );
  }

  void _confirmDelete(int id){
    showDialog(
      context: context,
      builder: (_) => AlertDialog(
        title: Text("Реально удалить?"),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
           child: Text("Отмена")
           ),
           TextButton(
            onPressed: () { Navigator.pop(context);
            _deleteNote(id);
            },
           child: Text("Да", style: TextStyle(color: Colors.red))
           ),
        ],
      ),
    );
  }

  Widget _buildCard(Map<String, dynamic> note) {
    final id = int.parse(note['id'].toString());
    final colorK = note['color'] ?? 'red';
    final backgrounCard = _colors[colorK];

    return Card(
      color: backgrounCard,
      child: Padding(
        padding: EdgeInsets.all(10.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Expanded(
                  child: Text(
                    note['title'] ?? '',
                    maxLines: 1,
                    overflow: TextOverflow.ellipsis,
                  ),
                ),
              ],
            ),
            if (note['text'] != null &&
                (note['text'] as String).isNotEmpty) ...[
              SizedBox(height: 10),
              Text(note['text'], maxLines: 5, style: TextStyle(fontSize: 16, color: const Color.fromARGB(255, 0, 0, 0)), overflow: TextOverflow.ellipsis),
            ],
            SizedBox(height: 5),
            Spacer(),
            Row(
              mainAxisAlignment: MainAxisAlignment.end,
              children: [
                IconButton(onPressed: () => (), icon: Icon(Icons.edit)),
                IconButton(onPressed: () => _confirmDelete(id),
                icon: Icon(Icons.delete)
                ),
              ],
            )
          ],
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Плиточные заметки'),
        actions: [
          IconButton(onPressed: () => _showDialog(), icon: Icon(Icons.add)),
        ],
      ),
      body: isLoading
          ? Center(child: CircularProgressIndicator())
          : Column(
              children: [
                Expanded(
                  child: GridView.builder(
                    gridDelegate:
                        const SliverGridDelegateWithFixedCrossAxisCount(
                          crossAxisCount: 2,
                          childAspectRatio: 1,
                          crossAxisSpacing: 10,
                          mainAxisSpacing: 10,
                        ),
                    itemCount: _notes.length,
                    itemBuilder: (context, index) {
                      return _buildCard(_notes[index]);
                    },
                  ),
                ),
              ],
            ),
    );
  }

  static const Map<String, Color> _colors = {
    'white': Colors.white,
    'red': Color.fromARGB(255, 190, 65, 56),
    'green': Color.fromARGB(255, 58, 192, 76),
    'blue': Color.fromARGB(255, 49, 121, 180),
  };
}
// clang-format on
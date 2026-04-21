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

  Future<void> _loadNotes() async{
    final responce = await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {'action': 'read'}
    );
    final data = jsonDecode(responce.body);
    setState(() {
      _notes = data['notes'];
      isLoading = false;
    });
  }

  Future<void> _createNotes(String title, String text, String color) async{
    await http.post(
      Uri.parse('http://localhost/notes_tiles.php'),
      body: {
        'action': 'create',
        'title':  title,
        'text': text,
        'color': color
      },
    );
    _loadNotes();
  }
}


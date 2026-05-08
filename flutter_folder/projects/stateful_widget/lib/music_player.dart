import 'package:flutter/material.dart';
import 'package:on_audio_query/on_audio_query.dart';
import 'package:audioplayers/audioplayers.dart';
import 'dart:io';

class MusicPlayer extends StatefulWidget {
  const MusicPlayer({super.key});

  @override
  State<MusicPlayer> createState() => _MusicPlayerState();
}

class _MusicPlayerState extends State<MusicPlayer> {
  final OnAudioQuery _audioQuery = OnAudioQuery(); // поиск музыки
  final AudioPlayer _player = AudioPlayer(); // управление музыкой
  List <SongModel> _music = []; // список музыки
  int _currentMusic = -1; // индекс текущего трека
  final bool _isPlaying = false;
  String _status = "Захар";

  @override
  void initState(){
    super.initState();
    _loadMusic();
  }

  Future<void> _loadMusic() async{
    setState(() => _status = 'Идет поиск...');
    try {
      if(Platform.isAndroid){
        _music = await _audioQuery.querySongs(uriType: UriType.EXTERNAL);
      }
      if(Platform.isWindows){
       final String? userProfile = Platform.environment['USERPROFILE'];
       List<SongModel> localMusic = [];
       if(userProfile != null){
        final String musicPath = '$userProfile\\Music';
        final dir = Directory(musicPath);
        if(dir.existsSync()) {
          final files = dir.listSync(recursive: true);
          for (var f in files){
            if(f is File && f.path.toLowerCase().endsWith('.mp3')) {
              localMusic.add(
                SongModel({
                  '_id':  f.path.hashCode,
                  '_data': f.path,
                  'title': f.path.split('\\').last.replaceAll(RegExp(r'\.mp3$', caseSensitive: false), ''),
                  'artist': 'Local',
                }),
                );
              }
            }
          }
          _music = localMusic;
        }
        if (_music.isEmpty){
          _status = 'В папке с музыкой ничего не найдено';
        }
       }
      } catch(_) {
      _status = 'Не удалось, не вышло, не повезло';
    }
    if (mounted) setState(() {});
  }

  void _playMusic(int index){
    if(index < 0 || index >= _music.length) return;
    _currentMusic = index;
    _player.play(DeviceFileSource(_music[index].data));
  }

  @override
  Widget build(BuildContext context){
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData.dark(),
      home: Scaffold(
        appBar: AppBar(
          title: Text('Player'),
          actions: [
            IconButton(
              onPressed: _loadMusic,
              icon: Icon(Icons.refresh)
              ),
            ],
          ),

        body: _music.isEmpty
        ? Center(
          child: Padding(
            padding: EdgeInsets.all(20),
            child: Text(_status, textAlign: TextAlign.center),
          )
        )
      : ListView.builder(
        itemCount: _music.length,
        itemBuilder: (context, index){
          final track = _music[index];
          return ListTile(
            title: Text(
              track.title,
              maxLines: 1,
              overflow: TextOverflow.ellipsis,
            ),
            trailing: _currentMusic == index && _isPlaying
            ? Icon(Icons.equalizer)
            : null,
            onTap: () => _playMusic(index),
          );
        },
      ),
      bottomNavigationBar: _currentMusic == -1 ? null : _playerControl(),
      )
    );
  }

  Widget _playerControl(){
    return Container(
      height: 60,
      color: Colors.deepPurple,
      padding: EdgeInsets.symmetric(horizontal: 16),
      child: Row(
        children: [
          Expanded(child: Text(
            _music[_currentMusic].title,
            style: TextStyle(color: Colors.white),
            maxLines: 1,
            overflow: TextOverflow.ellipsis,
          )
        ),
        IconButton(
          onPressed: () => _isPlaying ? _player.pause() : _player.resume(),
          icon: Icon(_isPlaying ? Icons.pause : Icons.play_arrow)
          ),
        ],
      )
    );
  }
}
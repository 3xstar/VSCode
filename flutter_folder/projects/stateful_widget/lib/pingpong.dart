import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:math';

void main() {
  runApp(const BigBongVladOlegGame());
}

class BigBongVladOlegGame extends StatefulWidget {
  const BigBongVladOlegGame({super.key});

  @override
  State<BigBongVladOlegGame> createState() => _BigBongVladOlegGameState();
}

class _BigBongVladOlegGameState extends State<BigBongVladOlegGame> {
  static const fieldWidth = 400.0;
  static const fieldHeight = 700.0;
  static const platformHeight = 80.0;
  static const platformWidth = 8.0;
  static const ballSize = 10.0;

  late double shmigShmigX, shmigShmigY; // позиция мяча от левого края и от верхнего края
    late double shmigShmigSpeedX, shmigShmigSpeedY; // скорость мяча 
    late double RightPlatformY;
    late double LeftPlatformY;

    int playerScore = 0;
    int fedorScore = 0;

    Timer? gameTimer;

    bool isGameOver = false;

    final random = Random();

    @override
    void initState() {
      super.initState();
      StartGame();
    }

    void StartGame() {
      isGameOver = false;
      shmigShmigX = fieldWidth / 2;
      shmigShmigY = fieldHeight / 2;

      shmigShmigSpeedX = 5;
      shmigShmigSpeedX = 5;
    }
}
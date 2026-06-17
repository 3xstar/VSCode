import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:math';

void main() {
  runApp(
    const MaterialApp(
      debugShowCheckedModeBanner: false,
      home: BigBongVladOlegGame(),
    ),
  );
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
  static const paddleOffset = 10.0;

  late double ballX, ballY;
  late double ballSpeedX, ballSpeedY;
  late double RightPlatformY;
  late double LeftPlatformY;
  double ballSize = 10.0;

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
    ballX = fieldWidth / 2;
    ballY = fieldHeight / 2;

    ballSpeedX = 2.5 * (random.nextBool() ? 1 : -1);
    ballSpeedY = 4 * (random.nextBool() ? 1 : -1);

    RightPlatformY = fieldHeight / 2 - platformHeight / 2;
    LeftPlatformY = fieldHeight / 2 - platformHeight / 2;

    playerScore = 0;
    fedorScore = 0;
    ballSize = 10.0;

    gameTimer?.cancel();

    gameTimer = Timer.periodic(const Duration(milliseconds: 16), (_) {
      if (!isGameOver) updateGame();
      setState(() {});  
    });
  }

  void updateGame() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    if (ballY <= 0) {
      ballY = 0;
      ballSpeedY = -ballSpeedY;
    }

    if (ballY >= fieldHeight - ballSize) {
      ballY = fieldHeight - ballSize;
      ballSpeedY = -ballSpeedY;
    }

    if (ballX <= 0) {
      fedorScore++; 
      resetBall();
    }

    double leftPlatformRight = paddleOffset + platformWidth;
    if (ballSpeedX < 0 &&
        ballX <= leftPlatformRight &&
        ballX + ballSize >= paddleOffset &&
        ballY + ballSize >= LeftPlatformY &&
        ballY <= LeftPlatformY + platformHeight) {
      ballX = leftPlatformRight;
      ballSpeedX = -ballSpeedX;

      double hitPosition = (ballY + ballSize / 2 - (LeftPlatformY + platformHeight / 2)) / (platformHeight / 2);
      ballSpeedY += hitPosition * 1.5;
    }

    double rightPlatformLeft = fieldWidth - paddleOffset - platformWidth;  
    if (ballSpeedX > 0 &&
        ballX + ballSize >= rightPlatformLeft &&
        ballX <= rightPlatformLeft + platformWidth &&
        ballY + ballSize >= RightPlatformY &&          
        ballY <= RightPlatformY + platformHeight) {     
      ballX = rightPlatformLeft - ballSize;
      ballSpeedX = -ballSpeedX;

      double hitPosition = (ballY + ballSize / 2 - (RightPlatformY + platformHeight / 2)) / (platformHeight / 2); 
      ballSpeedY += hitPosition * 1.5;
    }

    if (ballX + ballSize >= fieldWidth) {
      playerScore++; 
      resetBall();
    }

    double targetOffset = (ballY - platformHeight / 2) - LeftPlatformY;
    LeftPlatformY += targetOffset.clamp(-4, 4);
    LeftPlatformY = LeftPlatformY.clamp(0, fieldHeight - platformHeight);

    if (playerScore >= 5 || fedorScore >= 5) {
      isGameOver = true;
    }
  }

  void resetBall() {
    ballX = fieldWidth / 2;
    ballY = fieldHeight / 2;
    ballSpeedX = 2.5 * (random.nextBool() ? 1 : -1);
    ballSpeedY = 4 * (random.nextBool() ? 1 : -1);
  }

  @override
  void dispose() {
    gameTimer?.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.deepPurpleAccent,
      body: Center(
        child: GestureDetector(
          onVerticalDragUpdate: (details) {
            if (!isGameOver) {
              setState(() {
                RightPlatformY = (RightPlatformY + details.delta.dy).clamp(0, fieldHeight - platformHeight);
              });
            }
          },
          child: Container(
            width: fieldWidth,
            height: fieldHeight,
            decoration: BoxDecoration(
              border: Border.all(color: Colors.white30),
            ),
            child: Stack(
              children: [
                Positioned(
                  left: ballX,
                  top: ballY,
                  child: Container(
                    width: ballSize,
                    height: ballSize,
                    decoration: const BoxDecoration(
                      color: Colors.cyanAccent,
                      shape: BoxShape.circle,
                    ),
                  ),
                ),

                Positioned(
                  left: paddleOffset,
                  top: LeftPlatformY,
                  child: Container(
                    width: platformWidth,
                    height: platformHeight,
                    color: Colors.lime,
                  ),
                ),

                Positioned(
                  right: paddleOffset,
                  top: RightPlatformY,  
                  child: Container(
                    width: platformWidth,
                    height: platformHeight,
                    color: Colors.lightGreenAccent,
                  ),
                ),

                Positioned(
                  top: 20,
                  left: 0,
                  right: 0,
                  child: Row(
                    mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text('$playerScore', style: const TextStyle(color: Colors.pink, fontSize: 48)),
                      const SizedBox(width: 40),
                      Text('$fedorScore', style: const TextStyle(color: Colors.black, fontSize: 48)),
                    ],
                  ),
                ),

                Positioned(
                  top: 0,
                  bottom: 0,
                  left: fieldWidth / 2 - 1,
                  child: Container(width: 2, color: Colors.white30),
                ),

                if (isGameOver)
                  Center(
                    child: Container(
                      padding: const EdgeInsets.all(24),
                      decoration: BoxDecoration(
                        color: Colors.black,
                        borderRadius: BorderRadius.circular(16),
                      ),
                      child: Column(
                        mainAxisSize: MainAxisSize.min,
                        children: [
                          Text(
                            playerScore >= 5 ? 'победили левые 💪' : 'победили правые 🦾',
                            style: const TextStyle(color: Colors.white, fontSize: 24),
                          ),
                          const SizedBox(height: 20),
                          ElevatedButton(
                            onPressed: () => StartGame(),
                            child: const Text('взять реванш'),
                          ),
                        ],
                      ),
                    ),
                  ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
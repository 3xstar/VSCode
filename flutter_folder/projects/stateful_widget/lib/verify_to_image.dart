import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';

class BasicApp extends StatelessWidget {
  const BasicApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'Логин и пароль',
      home: ShowColorScreen(),
    );
  }
}

class ShowColorScreen extends StatefulWidget {
  const ShowColorScreen({super.key});

  @override
  State<ShowColorScreen> createState() => _ShowColorScreenState();
}

class _ShowColorScreenState extends State<ShowColorScreen> {
  late TextEditingController _usernameController;
  late TextEditingController _passwordController;

  String? _errorText = '';
  String? _errorText2 = '';
  
  @override
  void initState(){
    super.initState();
    _usernameController = TextEditingController();
    _passwordController = TextEditingController();
  }

  @override
  void dispose() {
    _usernameController.dispose();
    _passwordController.dispose();
    super.dispose();
  }

  void _validationName(String username){
    setState(() {
      if (username.length < 3){
        _errorText = 'введите имя длиннее двух символов';
      }
      else if (username.contains(' ')) {
        _errorText = 'в имени не должно быть пробелов';
      }
      else if (username.contains('захар123')) {
        _errorText = 'одумайся';
      }
      else{
        _errorText = null;
      }
    });
  }

  void _validationPassword(String password){
    setState(() {
    if (password.length < 8){
      _errorText2 = 'Пароль слишком короткий (минимум 8 символов)';
    } else if (!password.contains(RegExp(r'[A-Z]'))) {
      _errorText2 = 'Добавьте хотя бы одну заглавную букву';
    } else if (!password.contains(RegExp(r'[0-9]'))) {
      _errorText2 = 'Добавьте хотя бы одну цифру';
    } else if (!password.contains(RegExp(r'[!@#$%^&*(),.?":{}|<>]'))) {
      _errorText2 = 'Добавьте хотя бы один специальный символ';
    }
    else{
        _errorText2 = null;
      }
    });
  }

  void _register(BuildContext context) async{
    final username = _usernameController.text;
    _validationName(username);
    final password = _passwordController.text;
    _validationPassword(password);

    if (_errorText == null && _errorText2 == null) {
      await Navigator.push(context, 
      MaterialPageRoute(builder: (context) => const PickColorScreen()),
    );
    }
    else if(_errorText != null){
      GFToast.showToast(
        _errorText!,
        context,
        backgroundColor: GFColors.DANGER,
        toastPosition: GFToastPosition.BOTTOM,
      );
    }
    else if(_errorText2 != null){
      GFToast.showToast(
        _errorText2!,
        context,
        backgroundColor: GFColors.DANGER,
        toastPosition: GFToastPosition.BOTTOM,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: Padding(
              padding: const EdgeInsets.all(16.0),
              child: Column(
                children: [
                  GFCard(
                    color: Colors.white,
                    content: Column(
                      children: [
                        TextField(
                          controller: _usernameController,
                          onChanged: _validationName,
                          onSubmitted: (_) => _register(context),
                          decoration: InputDecoration(
                            labelText: 'Логин',
                            errorText: _errorText,
                            border: const OutlineInputBorder(),
                          ),
                        ),
                        const SizedBox(height: 20),
                        TextField(
                          controller: _passwordController,
                          onChanged: _validationPassword,
                          onSubmitted: (_) => _register(context),
                          decoration: InputDecoration(
                            labelText: 'Пароль',
                            errorText: _errorText2,
                            border: const OutlineInputBorder(),
                          ),
                        ),
                        const SizedBox(height: 20),
                        ElevatedButton(
                          onPressed: () => _register(context),
                          child: Text('Войти')
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
    );
  }
}

class PickColorScreen extends StatefulWidget {
  const PickColorScreen({super.key});

  @override
  State<PickColorScreen> createState() => _PickColorScreenState();
}

class _PickColorScreenState extends State<PickColorScreen>{
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Экран 2: картинка'),
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Container(
              width: 600,
              height: 700,
              decoration: BoxDecoration(
                          borderRadius: BorderRadius.circular(15),
                          image: const DecorationImage(
                            image: AssetImage("assets/bg.jpg"),
                            fit: BoxFit.cover,
                          ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
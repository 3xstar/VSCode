import 'package:flutter/material.dart';
import 'package:getwidget/getwidget.dart';


class RegisterForm extends StatefulWidget {
  const RegisterForm ({super.key});

  @override
  State<RegisterForm> createState() => _RegisterFormState();
}

class _RegisterFormState extends State<RegisterForm> {
  late TextEditingController _usernameController;

  String? _errorText = '';

  @override
  void initState(){
    super.initState();
    _usernameController = TextEditingController();
  }

  @override
  void dispose() {
    _usernameController.dispose();
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

  void _register(BuildContext context){
    final username = _usernameController.text;
    _validationName(username);
    if (_errorText == null) {
      GFToast.showToast('Пользователь с именем "$username" зарегистрирован',
      context,
      backgroundColor: GFColors.SUCCESS,
      toastPosition: GFToastPosition.BOTTOM
      );
    }
    else {
      GFToast.showToast(
        _errorText!,
        context,
        backgroundColor: GFColors.DANGER,
        toastPosition: GFToastPosition.BOTTOM,
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        body: Builder(
          builder: (BuildContext innerContext) {
            return Padding(
              padding: const EdgeInsets.all(16.0),
              child: Column(
                children: [
                  GFCard(
                    content: Column(
                      children: [
                        TextField(
                          controller: _usernameController,
                          onChanged: _validationName,
                          onSubmitted: (_) => _register(innerContext),
                          decoration: InputDecoration(
                            labelText: 'Введите имя',
                            errorText: _errorText,
                            border: const OutlineInputBorder(),
                          ),
                        ),
                        const SizedBox(height: 10),
                        GFButton(
                          onPressed: () => _register(innerContext),
                          text: "Зарегистрироваться",
                          blockButton: true,
                        )
                      ],
                    ),
                  ),
                ],
              ),
            );
          }
        )
      )
    );
  }
}
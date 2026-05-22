import 'package:flutter/material.dart';

class ExpenseItem {
  final String id;
  final String title;
  final double amount;

  ExpenseItem({
    required this.id,
    required this.title,
    required this.amount,
  });
}

class CostCountHome extends StatefulWidget {
  const CostCountHome({super.key});

  @override
  State<CostCountHome> createState() => _CostCountHomeState();
}

class _CostCountHomeState extends State<CostCountHome> {
  // 1. Список расходов
  final List<ExpenseItem> _expenses = [];
  
  // 2. Контроллеры для полей ввода (чтобы читать текст и очищать поля)
  final TextEditingController _titleController = TextEditingController();
  final TextEditingController _amountController = TextEditingController();

  double get _totalAmount{
    return _expenses.fold(0, (sum, item) => sum + item.amount);
  }

  void _showError(String message) {
  showDialog(
    context: context,
    builder: (ctx) => AlertDialog(
      title: const Text('Ошибка'),
      content: Text(message),
      actions: [
        TextButton(
          onPressed: () => Navigator.pop(ctx),
          child: const Text('ОК'),
        ),
      ],
    ),
  );
  }


  _saveExpense()
  {
    String title_text = _titleController.text.trim();
    String amount_text = _amountController.text.trim();

    if(title_text.isEmpty){
      _showError("Название не должно быть пустым");
      return;
    }
    
    double? amount = double.tryParse(amount_text);
    
    if(amount == null){
      _showError("Сумма должна содержать только цифры");
      return;
    }

    setState(() {
      _expenses.add(
        ExpenseItem(
          id: DateTime.now().millisecondsSinceEpoch.toString(),
          title: title_text,
          amount: amount,
        ),
      );
    });
    
    _titleController.clear();
    _amountController.clear();
    Navigator.pop(context);
  }

  _deleteExpense(String id){
    setState(() => _expenses.removeWhere((item) => item.id == id));
  }

  _showAddDialog(){
    _titleController.clear();
    _amountController.clear();
      showDialog(context: context, builder: (ctx) => AlertDialog(
        title: Text("Новые расходы"),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: _titleController,
              decoration: const InputDecoration(labelText: "Название"),
            ),
            const SizedBox(height: 10),
            TextField(
              controller: _amountController,
              keyboardType: TextInputType.numberWithOptions(decimal: true),
              decoration: const InputDecoration(labelText: "Сумма"),
            )
          ],
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(ctx),
            child: Text("Отмена"),
          ),
          TextButton(
            onPressed: _saveExpense,
            child: Text("Сохранить"),
          ),
        ],
      )
    );
  }

  @override
  void dispose() {
    _titleController.dispose();
    _amountController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('CostCount'),
        centerTitle: true,
      ),
      // Тело экрана (Шаг 6)
      body: _expenses.isEmpty
        ? const Center(
          child: Text(
            'Нет записей',
            style: TextStyle(fontSize: 18, color: Colors.grey)
            ),
          )
        : ListView.builder(
          itemCount: _expenses.length,
          itemBuilder: (ctx, index) {
            final item = _expenses[index];

            return Dismissible(
              key: Key(item.id),
              direction: DismissDirection.endToStart,
              onDismissed: (direction) {
                _deleteExpense(item.id);
              },
              background: Container(
                color: Colors.redAccent,
                alignment: Alignment.centerRight,
                padding: const EdgeInsets.only(right: 20),
                child: const Icon(Icons.delete, color: Colors.white),
              ),
              child: ListTile(
                title: Text(item.title, style: const TextStyle(fontSize: 16)),
                trailing: Text('${item.amount} ₽',
                style: const TextStyle(fontSize: 18, fontWeight: FontWeight.bold)
              ),
            ),
          );
        }),
      floatingActionButton: FloatingActionButton(
        onPressed: _showAddDialog,
        child: const Icon(Icons.add),
      ),
      bottomNavigationBar: Container(
        padding: const EdgeInsets.all(16),
        color: Theme.of(context).colorScheme.surface,
        child: ListTile(
            title: Text('Итого: ', style: TextStyle(fontSize: 18)),
            trailing: Text('${_totalAmount.toStringAsFixed(2)} ₽',
            style: const TextStyle(fontSize: 20, fontWeight: FontWeight.bold)
          ),
        ),
      ),
    );
  }
}
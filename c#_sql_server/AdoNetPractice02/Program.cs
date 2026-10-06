// task 1-2

using Microsoft.Data.SqlClient;

Console.WriteLine("Task 1-4");

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";

using var connection = new SqlConnection(connectionString);

connection.Open();

Console.WriteLine("Подключение к базе данных установлено.");



// task 3

Console.WriteLine("\nTask 3");

string sql = "SELECT DB_NAME();";

using var command = new SqlCommand(sql, connection);

string databaseName =
Convert.ToString(command.ExecuteScalar())!;

Console.WriteLine($"База данных: {databaseName}");



// task 4

Console.WriteLine("\nTask 4");

string sql2 = "SELECT COUNT(*) FROM products;";

using var command2 = new SqlCommand(sql2, connection);

int productCount =
 Convert.ToInt32(command2.ExecuteScalar());

Console.WriteLine($"Количество товаров: {productCount}");



// task 5

Console.WriteLine("\nTask 5");

string sql3 = """
 SELECT id, name, price
 FROM products;
 """;

using var command3 = new SqlCommand(sql3, connection);

using var reader = command3.ExecuteReader();

while (reader.Read())
{
 Console.WriteLine(
 $"{reader["id"]}. {reader["name"]} — {reader["price"]} руб."
 );
}

reader.Close();



// task 6

Console.WriteLine("\nTask 6");

string sql4 = """
 INSERT INTO products (name, category_id, price)
 VALUES (N'Мокка', 1, 240.00);
 """;

using var command4 = new SqlCommand(sql4, connection);

int rowsAffected = command4.ExecuteNonQuery();

Console.WriteLine($"Добавлено строк: {rowsAffected}"); 



// task 7

Console.WriteLine("\nTask 7");

string sql5 = """
    UPDATE products
    SET price = 250.00
    WHERE name = N'Мокка';
 """;
 
using var command5 = new SqlCommand(sql5, connection);

int rowsUpdated = command5.ExecuteNonQuery();

Console.WriteLine($"Изменено строк: {rowsUpdated}"); 



// task 8

Console.WriteLine("\nTask 8");

string sql6 = """
    SELECT MAX(price)
    FROM products;
 """;
 
using var command6 = new SqlCommand(sql6, connection);

decimal maxPrice = Convert.ToDecimal(command6.ExecuteScalar());

Console.WriteLine($"Максимальная цена: {maxPrice} руб.");



// task 9

Console.WriteLine("\nTask 9");

string sql7 = """
    SELECT COUNT(*)
    FROM orders;
 """;

using var command7 = new SqlCommand(sql7, connection);

int orderCount = Convert.ToInt32(command7.ExecuteScalar());

Console.WriteLine($"Количество заказов: {orderCount}");



// task 10

Console.WriteLine("\nTask 10");

string sql8 = """
    DELETE FROM products
    WHERE name = N'Мокка';
 """;

using var command8 = new SqlCommand(sql8, connection);

int productDeleted = command8.ExecuteNonQuery();

Console.WriteLine($"Удалено товаров: {productDeleted}");



// work by yourself

Console.WriteLine("\nWork by yourself");


// 1

string sql9 = """
    SELECT COUNT(*)
    FROM customers;
 """;

using var command9 = new SqlCommand(sql9, connection);

int customerCount = Convert.ToInt32(command9.ExecuteScalar());

Console.WriteLine($"Количество клиентов: {customerCount}");


// 2

string sql10 = """
    SELECT COUNT(*)
    FROM products
    WHERE is_available = 1;
 """;

using var command10 = new SqlCommand(sql10, connection);

int avaliableProduct = Convert.ToInt32(command10.ExecuteScalar());

Console.WriteLine($"Количество доступных товаров: {avaliableProduct}");


// 3

string sql11 = """
    SELECT MIN(price)
    FROM products;
 """;

using var command11 = new SqlCommand(sql11, connection);

decimal minPrice = Convert.ToDecimal(command11.ExecuteScalar());

Console.WriteLine($"Минимальная цена: {minPrice} руб.");


// 4

string sql12 = """
    SELECT COUNT(*)
    FROM orders
    WHERE status = N'Выдан';
 """;

using var command12 = new SqlCommand(sql12, connection);

int claimedOrder = Convert.ToInt32(command12.ExecuteScalar());

Console.WriteLine($"Количество выданных заказов: {claimedOrder}");


// 5 

string sql13 = """
 INSERT INTO products (name, category_id, price)
 VALUES (N'Бонус от Захара', 1, 1000.00);
 """;

using var command13 = new SqlCommand(sql13, connection);

int rowsAffected2 = command13.ExecuteNonQuery();

Console.WriteLine($"Добавлено строк: {rowsAffected2}"); 
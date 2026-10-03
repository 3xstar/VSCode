//task 1 - 4

using Microsoft.Data.SqlClient;

Console.WriteLine("Task 1-4");

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection = True; TrustServerCertificate = True;";

using var connection = new SqlConnection(connectionString);

connection.Open();

Console.WriteLine("Соединение с базой данных установлено.");



//task 5

Console.WriteLine("\nTask 5");

string sql_db = "SELECT DB_NAME();";

using var db_command = new SqlCommand(sql_db, connection);

var databaseName = db_command.ExecuteScalar();

Console.WriteLine($"Текущая база данных: {databaseName}");



// task 6

Console.WriteLine("\nTask 6");

string sql_server = "SELECT @@SERVERNAME;";

using var server_command = new SqlCommand(sql_server, connection);

var serverName = server_command.ExecuteScalar();

Console.WriteLine($"SQL Server: {serverName}");



// task 7

Console.WriteLine("\nTask 7");

using var db2_command = new SqlCommand(
    "SELECT DB_NAME();",
    connection);

var databaseName2 = db2_command.ExecuteScalar();

Console.WriteLine($"Текущая база данных: {databaseName2}");


using var server2_command = new SqlCommand(
    "SELECT @@SERVERNAME;",
    connection);

var serverName2 = server2_command.ExecuteScalar();

Console.WriteLine($"SQL Server: {serverName2}");


using var date_command = new SqlCommand(
    "SELECT GETDATE();",
    connection);

var serverDate = date_command.ExecuteScalar();

Console.WriteLine($"Дата и время сервера: {serverDate}");



// task 8

Console.WriteLine("\nTask 8");

string sql_products_count = """
    SELECT COUNT(*)
    FROM Products;
""";

using var product_command = new SqlCommand(sql_products_count, connection);

var productCount = product_command.ExecuteScalar();

Console.WriteLine($"Количество товаров: {productCount}");



// task 9

Console.WriteLine("\nTask 9");

// Первый способ

// string sql_expensive_product = """
//     SELECT TOP 1
//         name,
//         price
//     FROM Products
//     ORDER BY price DESC;
// """;

// Второй способ

string sql_max_price_product = """
    SELECT MAX(price)
    FROM Products;
""";

using var max_price_product_command = new SqlCommand(sql_max_price_product, connection);

var maxPriceProduct = max_price_product_command.ExecuteScalar();

Console.WriteLine($"Максимальная цена товара: {maxPriceProduct}");



// work by yourself

Console.WriteLine("\nWork by yourself");

using var db_final_command = new SqlCommand(
    "SELECT DB_NAME();",
    connection);

var databaseFinalName = db_final_command.ExecuteScalar();

Console.WriteLine($"База данных: {databaseFinalName}");


using var server_final_command = new SqlCommand(
    "SELECT @@SERVERNAME;",
    connection);

var serverFinalName = server_final_command.ExecuteScalar();

Console.WriteLine($"SQL Server: {serverFinalName}");


string sql_final_products_count = """
    SELECT COUNT(*)
    FROM Products;
""";

using var product_final_command = new SqlCommand(sql_final_products_count, connection);

var productFinalCount = product_final_command.ExecuteScalar();

Console.WriteLine($"Количество товаров: {productFinalCount}");


string sql_final_min_price_product = """
    SELECT MIN(price)
    FROM Products;
""";

using var min_price_product_final_command = new SqlCommand(sql_final_min_price_product, connection);

var minPriceFinalProduct = min_price_product_final_command.ExecuteScalar();

Console.WriteLine($"Максимальная цена товара: {minPriceFinalProduct}");


string sql_final_max_price_product = """
    SELECT MAX(price)
    FROM Products;
""";

using var max_price_product_final_command = new SqlCommand(sql_final_max_price_product, connection);

var maxPriceFinalProduct = max_price_product_final_command.ExecuteScalar();

Console.WriteLine($"Максимальная цена товара: {maxPriceFinalProduct}");
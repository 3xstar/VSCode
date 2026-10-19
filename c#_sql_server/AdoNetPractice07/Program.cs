using Microsoft.Extensions.Configuration;
using Microsoft.Data.SqlClient;

IConfiguration configuration = new ConfigurationBuilder()
 .SetBasePath(AppContext.BaseDirectory)
 .AddJsonFile("appsettings.json", optional: false)
 .AddEnvironmentVariables()
 .Build();

string connectionString = configuration.GetConnectionString("CoffeeShop")
 ?? throw new InvalidOperationException("Строка подключения не найдена.");



Console.WriteLine("Part 4");

static async Task CheckConnectionAsync(string connectionString)
{
 await using SqlConnection connection = new SqlConnection(connectionString);
 await connection.OpenAsync();
 using SqlCommand command =
 new SqlCommand("SELECT DB_NAME()", connection);
 string databaseName = (string)(await command.ExecuteScalarAsync())!;
 Console.WriteLine($"Подключено к базе: {databaseName}");
}

await CheckConnectionAsync(connectionString);



Console.WriteLine("Part 5");

static async Task ShowStatisticsAsync(string connectionString)
{
 await using SqlConnection connection = new SqlConnection(connectionString);
 await connection.OpenAsync();

 using SqlCommand command =
 new SqlCommand("SELECT COUNT(*) FROM products;", connection);
 int productsCount = (int)(await command.ExecuteScalarAsync())!;

 using SqlCommand command2 =
 new SqlCommand("SELECT COUNT(*) FROM customers;", connection);
 int customersCount = (int)(await command2.ExecuteScalarAsync())!;

 using SqlCommand command3 =
 new SqlCommand("SELECT COUNT(*) FROM orders;", connection);
 int ordersCount = (int)(await command3.ExecuteScalarAsync())!;

 Console.WriteLine("Cтатистика кофейни:");
 Console.WriteLine($"Количество продуктов: {productsCount}");
 Console.WriteLine($"Количество клиентов: {customersCount}");
 Console.WriteLine($"Количество заказов: {ordersCount}");
}

await ShowStatisticsAsync(connectionString);



Console.WriteLine("Part 6");

string title = configuration["Application:Title"] ?? "Приложение";
Console.WriteLine(title);

string? showPricesRaw = configuration["Application:ShowPrices"];

if (!bool.TryParse(showPricesRaw, out bool showPrices))
{
    showPrices = false; 
}
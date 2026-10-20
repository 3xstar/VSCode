using Microsoft.Extensions.Configuration;
using Microsoft.Data.SqlClient;

IConfiguration configuration = new ConfigurationBuilder()
 .SetBasePath(AppContext.BaseDirectory)
 .AddJsonFile("appsettings.json", optional: false)
 .AddEnvironmentVariables()
 .Build();

string connectionString = configuration.GetConnectionString("CoffeeShop")
 ?? throw new InvalidOperationException("Строка подключения не найдена.");



// part 4

static async Task CheckConnectionAsync(string connectionString)
{
    await using SqlConnection connection = new SqlConnection(connectionString);
    await connection.OpenAsync();
    using SqlCommand command =
    new SqlCommand("SELECT DB_NAME()", connection);
    string databaseName = (string)(await command.ExecuteScalarAsync())!;
    Console.WriteLine($"Подключено к базе: {databaseName}");
}



// part 5

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



// part 6

string title = configuration["Application:Title"] ?? "Приложение";
Console.WriteLine(title);

string? showPricesRaw = configuration["Application:ShowPrices"];

if (!bool.TryParse(showPricesRaw, out bool showPrices))
{
    showPrices = false;
}



// part 7

static async Task ShowAvailableProductsAsync(string connectionString, bool showPrices)
{
    await using SqlConnection connection = new SqlConnection(connectionString);
    await connection.OpenAsync();

    using SqlCommand command = new SqlCommand(
        "SELECT id, name, price FROM products WHERE is_available = 1 ORDER BY id", connection);

    await using SqlDataReader reader = await command.ExecuteReaderAsync();

    if (reader.HasRows)
    {
        while (await reader.ReadAsync())
        {
            int id = reader.GetInt32(0);
            string name = reader.GetString(1);
            decimal price = reader.GetDecimal(2);

            if (showPrices)
            {
                Console.WriteLine($"{id}. {name} — {price} руб.");
            }
            else
            {
                Console.WriteLine($"{id}. {name}");
            }
        }
    }
    else
    {
        Console.WriteLine("Товары не найдены");
    }
}

static async Task ShowProductsByNameAsync(string connectionString, bool showPrices)
{
    await using SqlConnection connection = new SqlConnection(connectionString);
    await connection.OpenAsync();

    using SqlCommand command = new SqlCommand(
            "SELECT id, name, price, is_available FROM products WHERE name LIKE @search", connection);

    Console.Write("Введите название или часть названия товара: ");
    string search = Console.ReadLine()!;

    command.Parameters.AddWithValue("@search", $"%{search}%");

    await using SqlDataReader reader = await command.ExecuteReaderAsync();

    if (reader.HasRows)
    {
        while (await reader.ReadAsync())
        {
            int id = reader.GetInt32(0);
            string name = reader.GetString(1);
            decimal price = reader.GetDecimal(2);
            bool available = reader.GetBoolean(3);
            if (showPrices)
            {
                Console.WriteLine($"{id}. {name} — {price} руб. | {(available ? "Есть" : "Нет")}");
            }
            else
            {
               Console.WriteLine($"{id}. {name} | {(available ? "Есть" : "Нет")}");
            }
        }
    }
    else
    {
        Console.WriteLine("Товары не найдены");
    }
}

static void ShowApplicationSettings(IConfiguration configuration)
{
    string title = configuration["Application:Title"] ?? "Приложение";
    bool showPrices = GetShowPricesSetting(configuration);

    Console.WriteLine("Настройки приложения:");
    Console.WriteLine($"Название приложения: {title}");
    Console.WriteLine($"Признак показа цен (ShowPrices): {showPrices}");
}

static bool GetShowPricesSetting(IConfiguration configuration)
{
    string? rawValue = configuration["Application:ShowPrices"];
    if (bool.TryParse(rawValue, out bool result))
    {
        return result;
    }
    return false;
}

bool isRunning = true;
while (isRunning)
{
    Console.WriteLine("\n=== СOFFEE CAFE CONSOLE ===");
    Console.WriteLine("1. Проверить подключение к базе.");
    Console.WriteLine("2. Показать количество товаров, клиентов и заказов.");
    Console.WriteLine("3. Вывести список доступных товаров.");
    Console.WriteLine("4. Найти товары по части названия.");
    Console.WriteLine("5. Показать настройки приложения.");
    Console.WriteLine("6. Выход.");
    Console.Write("\nВыберите пункт меню: ");

    string? choice = Console.ReadLine();
    Console.WriteLine();

    try
    {
        switch (choice)
        {
            case "1":
                try
                {
                    await CheckConnectionAsync(connectionString);
                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "2":
                try
                {
                    await ShowStatisticsAsync(connectionString);
                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "3":
                try
                {
                    await ShowAvailableProductsAsync(connectionString, showPrices);
                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "4":
                try
                {
                    await ShowProductsByNameAsync(connectionString, showPrices);
                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "5":
                ShowApplicationSettings(configuration);
                break;
            case "6":
                isRunning = false;
                break;
            default:
                Console.WriteLine("Неверный пункт меню. Попробуйте снова.");
                break;
        }
    }
    catch (SqlException ex)
    {
        Console.WriteLine($"Ошибка при работе с SQL Server: {ex.Message}");
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Произошла непредвиденная ошибка: {ex.Message}");
    }
}
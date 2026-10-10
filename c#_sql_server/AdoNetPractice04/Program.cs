// part 1

using Microsoft.Data.SqlClient;

string connectionString =
"Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";

using SqlConnection connection = new SqlConnection(connectionString);
connection.Open();

// part 2-3

Console.WriteLine("Part 2-3");

string sql = @"
    SELECT id, name, price, is_available
    FROM products";

using SqlCommand command = new SqlCommand(sql, connection);
using SqlDataReader reader = command.ExecuteReader();

if (reader.HasRows)
{
    while (reader.Read())
    {
        int id = reader.GetInt32(0);
        string name = reader.GetString(1);
        decimal price = reader.GetDecimal(2);
        bool isAvailable = reader.GetBoolean(3);
        Console.WriteLine($"{id}. {name}");
        Console.WriteLine($"Цена: {price} руб.");
        Console.WriteLine($"Доступен: {(isAvailable ? "Да" : "Нет")}");
        Console.WriteLine();
    }
}

else
{
    Console.WriteLine("Товары не найдены");
}
reader.Close();



// part 4

Console.WriteLine("\nPart 4");

Console.Write("Введите ID товара: ");
int productId = Convert.ToInt32(Console.ReadLine());

string sql2 = """
    SELECT id, name, price, is_available
    FROM products
    WHERE id = @id;
    """;

using SqlCommand command2 = new SqlCommand(sql2, connection);
command2.Parameters.AddWithValue("@id", productId);

using SqlDataReader reader2 = command2.ExecuteReader();

if (reader2.HasRows)
{
    while (reader2.Read())
    {
        int id = reader2.GetInt32(0);
        string name = reader2.GetString(1);
        decimal price = reader2.GetDecimal(2);
        bool isAvailable = reader2.GetBoolean(3);
        Console.WriteLine($"{id}. {name}");
        Console.WriteLine($"Цена: {price} руб.");
        Console.WriteLine($"Доступен: {(isAvailable ? "Да" : "Нет")}");
        Console.WriteLine();
    }
}

else
{
    Console.WriteLine("Товара с таким ID не найдено");
}
reader2.Close();



// part 5

Console.WriteLine("\nPart 5");

Console.Write("Введите название товара: ");

string product_name = Console.ReadLine()!;

string sql3 = """
    SELECT id, name, price
    FROM products
    WHERE name LIKE @search;
    """;

using SqlCommand command3 = new SqlCommand(sql3, connection);
command3.Parameters.AddWithValue("@search", $"%{product_name}%");

using SqlDataReader reader3 = command3.ExecuteReader();

if (reader3.HasRows)
{
    while (reader3.Read())
    {
        int id = reader3.GetInt32(0);
        string name = reader3.GetString(1);
        decimal price = reader3.GetDecimal(2);
        Console.WriteLine($"{id}. {name}");
        Console.WriteLine($"Цена: {price} руб.");
        Console.WriteLine();
    }
}

else
{
    Console.WriteLine("Товара с таким именем не найдено");
}
reader3.Close();



// part 6

Console.WriteLine("\nPart 6");

string sql4 = @"
    SELECT id, full_name, phone, email
    FROM customers";

using SqlCommand command4 = new SqlCommand(sql4, connection);
using SqlDataReader reader4 = command4.ExecuteReader();

if (reader4.HasRows)
{
    while (reader4.Read())
    {
        int id = reader4.GetInt32(0);
        string fullName = reader4.GetString(1);
        string phone = reader4.GetString(2);
        string email = reader4.IsDBNull(3) 
            ? "Не указан" 
            : reader4.GetString(3);
        Console.WriteLine($"ID: {id}");
        Console.WriteLine($"Полное имя: {fullName}");
        Console.WriteLine($"Телефон: {phone}");
        Console.WriteLine($"Email: {email}");
        Console.WriteLine();
    }
}

else
{
    Console.WriteLine("Клиенты не найдены");
}
reader4.Close();



// part 7

Console.WriteLine("\nPart 7");

string sql5 = @"
    SELECT id, customer_id, order_date, status
    FROM orders";

using SqlCommand command5 = new SqlCommand(sql5, connection);
using SqlDataReader reader5 = command5.ExecuteReader();

if (reader5.HasRows)
{
    while (reader5.Read())
    {
        int id = reader5.GetInt32(0);
        int customerId = reader5.GetInt32(1);
        DateTime orderDate = reader5.GetDateTime(2);
        string status = reader5.GetString(3);

        Console.WriteLine($"Заказ №{id}");
        Console.WriteLine($"ID клиента: {customerId}");
        Console.WriteLine($"Дата заказа: {orderDate:dd.MM.yyyy HH:mm}");
        Console.WriteLine($"Статус: {status}");
        Console.WriteLine();
    }
}
else
{
    Console.WriteLine("Заказы не найдены");
}
reader5.Close();



// part 8

Console.WriteLine("\nPart 8");


while (true)
{
    Console.WriteLine("--- PRODUCT_CLIENT_ORDER MENU ---");
    Console.WriteLine("1. Доступные товары по возрастанию цены");
    Console.WriteLine("2. Поиск товаров дороже заданной цены");
    Console.WriteLine("3. Поиск клиента по части Ф. И. О.");
    Console.WriteLine("4. Вывод заказов по статусу");
    Console.WriteLine("0. Выход из программы");
    Console.Write("Выберите пункт меню: ");

    string choice = Console.ReadLine()!;

    if (choice == "0")
    {
        Console.WriteLine("Выход из программы");
        break;
    }

    switch (choice)
    {
        case "1":
            string sql8_1 = @"
                SELECT id, name, price, is_available
                FROM products
                WHERE is_available = 1
                ORDER BY price ASC;";

            using (SqlCommand command8_1 = new SqlCommand(sql8_1, connection))
            using (SqlDataReader reader8_1 = command8_1.ExecuteReader())
            {
                if (reader8_1.HasRows)
                {
                    while (reader8_1.Read())
                    {
                        int id = reader8_1.GetInt32(0);
                        string name = reader8_1.GetString(1);
                        decimal price = reader8_1.GetDecimal(2);
                        Console.WriteLine($"{id}. {name} — {price} руб.");
                    }
                }
                else
                {
                    Console.WriteLine("Доступные товары не найдены");
                }
            }
            break;

        case "2":
            Console.Write("Введите минимальную цену: ");
            decimal minPrice = Convert.ToDecimal(Console.ReadLine());

            string sql8_2 = @"
                SELECT id, name, price
                FROM products
                WHERE price > @minPrice;";

            using (SqlCommand command8_2 = new SqlCommand(sql8_2, connection))
            {
                command8_2.Parameters.AddWithValue("@minPrice", minPrice);
                using (SqlDataReader reader8_2 = command8_2.ExecuteReader())
                {
                    if (reader8_2.HasRows)
                    {
                        while (reader8_2.Read())
                        {
                            int id = reader8_2.GetInt32(0);
                            string name = reader8_2.GetString(1);
                            decimal price = reader8_2.GetDecimal(2);
                            Console.WriteLine($"{id}. {name} — {price} руб.");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Товары дороже {minPrice} руб. не найдены");
                    }
                }
            }
            break;

        case "3":
            Console.Write("Введите часть имени клиента: ");
            string searchName = Console.ReadLine()!;

            string sql8_3 = @"
                SELECT id, full_name, phone, email
                FROM customers
                WHERE full_name LIKE @searchName;";

            using (SqlCommand command8_3 = new SqlCommand(sql8_3, connection))
            {
                command8_3.Parameters.AddWithValue("@searchName", $"%{searchName}%");
                using (SqlDataReader reader8_3 = command8_3.ExecuteReader())
                {
                    if (reader8_3.HasRows)
                    {
                        while (reader8_3.Read())
                        {
                            int id = reader8_3.GetInt32(0);
                            string fullName = reader8_3.GetString(1);
                            string phone = reader8_3.GetString(2);
                            string email = reader8_3.IsDBNull(3) ? "Не указан" : reader8_3.GetString(3);

                            Console.WriteLine($"Клиент №{id}: {fullName} | Тел: {phone} | Email: {email}");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Клиенты с ФИО, содержащим '{searchName}', не найдены");
                    }
                }
            }
            break;

        case "4":
            Console.Write("Введите статус заказа (Выполнен, В обработке, Выдан): ");
            string searchStatus = Console.ReadLine()!;

            string sql8_4 = @"
                SELECT id, customer_id, order_date, status
                FROM orders
                WHERE status = @status;";

            using (SqlCommand command8_4 = new SqlCommand(sql8_4, connection))
            {
                command8_4.Parameters.AddWithValue("@status", searchStatus);
                using (SqlDataReader reader8_4 = command8_4.ExecuteReader())
                {
                    if (reader8_4.HasRows)
                    {
                        while (reader8_4.Read())
                        {
                            int id = reader8_4.GetInt32(0);
                            int customerId = reader8_4.GetInt32(1);
                            DateTime orderDate = reader8_4.GetDateTime(2);
                            string status = reader8_4.GetString(3);

                            Console.WriteLine($"Заказ №{id} | ID Клиента: {customerId} | Дата: {orderDate:dd.MM.yyyy} | Status: {status}");
                        }
                    }
                    else
                    {
                        Console.WriteLine($"Заказы со статусом '{searchStatus}' не найдены");
                    }
                }
            }
            break;

        default:
            Console.WriteLine("Неверное значение, попробуйте еще раз");
            break;
    }
}
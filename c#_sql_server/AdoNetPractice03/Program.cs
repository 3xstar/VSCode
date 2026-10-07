// task 1

using Microsoft.Data.SqlClient;

Console.WriteLine("Task 1");

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";

using var connection = new SqlConnection(connectionString);

connection.Open();

Console.WriteLine("Подключение установлено.");



// task 2

Console.WriteLine("\nTask 2");

Console.Write("Введите ID товара: ");

int productId = Convert.ToInt32(Console.ReadLine());

string sql = """
    SELECT id, name, price
    FROM products
    WHERE id = @id;
    """;

using var command = new SqlCommand(sql, connection);

command.Parameters.AddWithValue("@id", productId);

using var reader = command.ExecuteReader();

while (reader.Read())
{
 Console.WriteLine($"{reader["id"]}: {reader["name"]} — {reader["price"]} руб."
 );
}

reader.Close();



// task 3

Console.WriteLine("\nTask 3");

Console.Write("Введите название товара: ");

string name = Console.ReadLine()!;

string sql2 = """
    SELECT id, name, price
    FROM products
    WHERE name = @name;
    """;

using var command2 = new SqlCommand(sql2, connection);

command2.Parameters.AddWithValue("@name", name);

using var reader2 = command2.ExecuteReader();

while (reader2.Read())
{
 Console.WriteLine($"{reader2["id"]}: {reader2["name"]} — {reader2["price"]} руб."
 );
}

reader2.Close();



// task 4

Console.WriteLine("\nTask 4");

Console.Write("Название товара: ");
string productName = Console.ReadLine()!;
Console.Write("ID категории: ");
int categoryId = Convert.ToInt32(Console.ReadLine());
Console.Write("Цена: ");
decimal price = Convert.ToDecimal(Console.ReadLine());

string sql3 = """
    INSERT INTO products (name, category_id, price)
    VALUES (@name, @category_id, @price);
    """;

using var command3 = new SqlCommand(sql3, connection);

command3.Parameters.AddWithValue("@name", productName);
command3.Parameters.AddWithValue("@category_id", categoryId);
command3.Parameters.AddWithValue("@price", price);

int rowsAffected = command3.ExecuteNonQuery();

Console.WriteLine($"Добавлено строк: {rowsAffected}");



// task 5

Console.WriteLine("\nTask 5");

Console.Write("Введите ID товара для изменения цены: ");
int productUpdateId = Convert.ToInt32(Console.ReadLine());
Console.Write("Введите новую цену товара: ");
decimal UpdatePrice = Convert.ToDecimal(Console.ReadLine());

string sql4 = """
    UPDATE products
    SET price = @price
    WHERE id = @id;
    """;

using var command4 = new SqlCommand(sql4, connection);

command4.Parameters.AddWithValue("@id", productUpdateId);
command4.Parameters.AddWithValue("@price", UpdatePrice);

int rowsChanged = command4.ExecuteNonQuery();

Console.WriteLine($"Изменено строк: {rowsChanged}");



// task 6

Console.WriteLine("\nTask 6");

Console.Write("Введите ID товара для удаления: ");
int productDeleteId = Convert.ToInt32(Console.ReadLine());

string sql5 = """
    DELETE FROM products
    WHERE id = @id;
    """;

using var command5 = new SqlCommand(sql5, connection);

command5.Parameters.AddWithValue("@id", productDeleteId);

int rowsDeleted = command5.ExecuteNonQuery();

Console.WriteLine($"Удалено строк: {rowsDeleted}");



// task 7

Console.WriteLine("\nTask 7");

Console.Write("Введите минимальную цену: ");

decimal minPrice =
 Convert.ToDecimal(Console.ReadLine());

string sql6 = """
    SELECT COUNT(*)
    FROM products
    WHERE price >= @min_price;
    """;

using var command6 = new SqlCommand(sql6, connection);

command6.Parameters.AddWithValue("@min_price", minPrice);

int count = Convert.ToInt32(command6.ExecuteScalar());

Console.WriteLine($"Товаров с ценой от {minPrice}: {count}");



// task 8

Console.WriteLine("\nTask 8");

Console.Write("Введите имя или фамилию: ");

string search = Console.ReadLine()!;

string sql7 = """
    SELECT id, full_name, phone, email
    FROM customers
    WHERE full_name LIKE @search;
    """;

using var command7 = new SqlCommand(sql7, connection);

command7.Parameters.AddWithValue("@search", $"%{search}%");

using var reader3 = command7.ExecuteReader();

while (reader3.Read())
{
 Console.WriteLine($"{reader3["full_name"]}");
}



// task 9

// Первый вариант (небезопасный)
// string sql =
//     $"SELECT id, name, price " +
//     $"FROM products " +
//     $"WHERE name = '{name}'";

// Второй вариант 
// string sql8 = """
//     SELECT id, name, price
//     FROM products
//     WHERE name = @name;
//     """;

// using var command8 = new SqlCommand(sql8, connection);

// command8.Parameters.AddWithValue("@name", name);


// 1. Пользовательское значение в первом варианте находиться
// внутри SQL строки

// 2. Пользовательское значение вр втором варианте находиться
// отдельно от SQL-кода в объекте SqlParameter

// 3. Параметизированный вариант безопаснее так как
// значение передаётся на сервер отдельно от кода

// 4. С кодом и SQL данными происходит следующее:
// Небезопасный вариант:
// Строка SQL собирается в C# целиком, уже вместе с данными.
// На сервер уходит один готовый текст. Если в name попадёт вредоносный код,
// сервер выполнит его как часть запроса. Плюс — при каждом новом значении текст разный,
// поэтому кэш планов запросов не работает.

// Безопасный вариант:
// На сервер уходит два отдельных элемента:
// шаблон SQL с @name и значение параметра.
// Сервер сам безопасно подставляет значение в нужное место.
// План запроса кэшируется и переиспользуется, а инъекция физически невозможна.



// work by yourself

Console.WriteLine("Work by Yourself");

while (true)
{
    Console.WriteLine("\n=== УПРАВЛЕНИЕ ТОВАРАМИ ===");
    Console.WriteLine("1. Найти товар по ID");
    Console.WriteLine("2. Найти товар по названию");
    Console.WriteLine("3. Добавить товар");
    Console.WriteLine("4. Изменить цену");
    Console.WriteLine("5. Удалить товар");
    Console.WriteLine("6. Найти товары дороже указанной цены");
    Console.WriteLine("0. Выход");
    Console.Write("Выбор: ");

    string choice = Console.ReadLine()!;

    switch (choice)
    {
        case "1":
        {
            Console.Write("ID товара: ");
            int product_id = Convert.ToInt32(Console.ReadLine());

            string sql_id = """
                SELECT id, name, price
                FROM products
                WHERE id = @id;
                """;

            using var command_id = new SqlCommand(sql_id, connection);

            command_id.Parameters.AddWithValue("@id", product_id);

            using var reader_id = command_id.ExecuteReader();

            while (reader_id.Read())
            {
                Console.WriteLine($"{reader_id["id"]}: {reader_id["name"]} — {reader_id["price"]} руб.");
            }

            reader_id.Close();
            break;
        }

        case "2":
        {
            Console.Write("Название товара: ");
            string product_name = Console.ReadLine()!;

            string sql_name = """
                SELECT id, name, price
                FROM products
                WHERE name = @name;
                """;

            using var command_name = new SqlCommand(sql_name, connection);

            command_name.Parameters.AddWithValue("@name", product_name);

            using var reader_name = command_name.ExecuteReader();

            while (reader_name.Read())
            {
            Console.WriteLine($"{reader_name["id"]}: {reader_name["name"]} — {reader_name["price"]} руб."
            );
            }

            reader_name.Close();
            break;
        }

        case "3":
        {
            Console.Write("Название товара: ");
            string new_name = Console.ReadLine()!;
            Console.Write("ID категории товара: ");
            int cat_id = Convert.ToInt32(Console.ReadLine());
            Console.Write("Цена товара: ");
            decimal new_price = Convert.ToDecimal(Console.ReadLine());

            string sql_insert = """
                INSERT INTO products (name, category_id, price)
                VALUES (@name, @category_id, @price);
                """;

            using var command_insert = new SqlCommand(sql_insert, connection);
            command_insert.Parameters.AddWithValue("@name", new_name);
            command_insert.Parameters.AddWithValue("@category_id", cat_id);
            command_insert.Parameters.AddWithValue("@price", new_price);

            int added_rows = command_insert.ExecuteNonQuery();

            Console.WriteLine($"Добавлено строк: {added_rows}");
            break;
        }

        case "4":
        {
            Console.Write("ID товара: ");
            int update_id = Convert.ToInt32(Console.ReadLine());
            Console.Write("Новая цена товара: ");
            decimal update_price = Convert.ToDecimal(Console.ReadLine());

            string sql_update = """
                UPDATE products
                SET price = @price
                WHERE id = @id;
                """;

            using var command_update = new SqlCommand(sql_update, connection);
            command_update.Parameters.AddWithValue("@id", update_id);
            command_update.Parameters.AddWithValue("@price", update_price);

            int updated_rows = command_update.ExecuteNonQuery();

            Console.WriteLine($"Изменено строк: {updated_rows}");
            break;
        }

        case "5":
        {
            Console.Write("Введите ID товара для удаления: ");
            int delete_id = Convert.ToInt32(Console.ReadLine());

            string sql_delete = """
                DELETE FROM products
                WHERE id = @id;
                """;

            using var command_delete = new SqlCommand(sql_delete, connection);

            command_delete.Parameters.AddWithValue("@id", delete_id);

            int deleted_rows = command_delete.ExecuteNonQuery();

            Console.WriteLine($"Удалено строк: {deleted_rows}");
            break;
        }

        case "6":
        {
            Console.Write("Введите минимальную цену: ");

            decimal min_price =
            Convert.ToDecimal(Console.ReadLine());

            string sql_min = """
                SELECT COUNT(*)
                FROM products
                WHERE price >= @min_price;
                """;

            using var command_min = new SqlCommand(sql_min, connection);

            command_min.Parameters.AddWithValue("@min_price", min_price);

            int min_count = Convert.ToInt32(command_min.ExecuteScalar());

            Console.WriteLine($"Товаров с ценой от {min_price}: {min_count}");
            break;
        }

        case "0":
            return;

        default:
            Console.WriteLine("Неверный пункт.");
            break;
    }
}
// part 1

using Microsoft.Data.SqlClient;

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";



// part 2

Console.WriteLine("Part 2");

static async Task<int> GetProductCountAsync(string connectionString)
{
	await using SqlConnection connection =
		new SqlConnection(connectionString);
	await connection.OpenAsync();
	using SqlCommand command = new SqlCommand(
		"SELECT COUNT(*) FROM products", connection);
	return (int)(await command.ExecuteScalarAsync())!;
}

try
{
    int count = await GetProductCountAsync(connectionString);
    Console.WriteLine($"Количество товаров: {count}");
}
catch (SqlException ex)
{
    Console.WriteLine($"Ошибка SQL (Part 2): {ex.Message}");
}

// part 3

Console.WriteLine("\nPart 3");

static async Task ShowProductsAsync(string connectionString)
{
	await using SqlConnection connection = new SqlConnection(connectionString);
	await connection.OpenAsync();

	using SqlCommand command = new SqlCommand(
            "SELECT id, name, price, is_available FROM products ORDER BY name", connection);

	await using SqlDataReader reader = await command.ExecuteReaderAsync();

	if (reader.HasRows){
		while (await reader.ReadAsync())
		{
			int id = reader.GetInt32(0);
			string name = reader.GetString(1);
			decimal price = reader.GetDecimal(2);
			bool available = reader.GetBoolean(3);
			Console.WriteLine($"{id}. {name} — {price} руб. | {(available ? "Есть" : "Нет")}");
		}
	}
	else
	{
		Console.WriteLine("Товары не найдены");
	}
}

try
{
    await ShowProductsAsync(connectionString);
}
catch (SqlException ex)
{
    Console.WriteLine($"Ошибка SQL (Part 3): {ex.Message}");
}



// part 4

Console.WriteLine("\nPart 4");

static async Task ShowProductsFromPriceAsync(string connectionString, decimal minPrice)
{
	await using SqlConnection connection = new SqlConnection(connectionString);
	await connection.OpenAsync();

	using SqlCommand command = new SqlCommand(
            "SELECT id, name, price FROM products WHERE price >= @min_price ORDER BY price", connection);

	command.Parameters.AddWithValue("@min_price", minPrice);

	await using SqlDataReader reader = await command.ExecuteReaderAsync();

	if (reader.HasRows){
		while (await reader.ReadAsync())
		{
			int id = reader.GetInt32(0);
			string name = reader.GetString(1);
			decimal price = reader.GetDecimal(2);
			Console.WriteLine($"{id}. {name} — {price} руб.");
		}
	}
	else
	{
		Console.WriteLine("Товаров с такой минимальной ценой не найдено");
	}
}

Console.Write("Введите минимальную цену товара: ");
if (!decimal.TryParse(Console.ReadLine(), out decimal minPrice))
{
    Console.WriteLine("Некорректная цена");
}
else
{
    try
    {
        await ShowProductsFromPriceAsync(connectionString, minPrice);
    }
    catch (SqlException ex)
    {
        Console.WriteLine($"Ошибка SQL (Part 4): {ex.Message}");
    }
}




// part 5

Console.WriteLine("\nPart 5");

static async Task UpdateProductAvailabilityAsync(string connectionString, int productId, bool isAvailable)
{
	await using SqlConnection connection = new SqlConnection(connectionString);
	await connection.OpenAsync();

	using SqlCommand command = new SqlCommand(
            "UPDATE products SET is_available = @is_available WHERE id = @id", connection);

	command.Parameters.AddWithValue("@id", productId);
	command.Parameters.AddWithValue("@is_available", isAvailable);

	int changed = await command.ExecuteNonQueryAsync();

	if (changed > 0)
	{
		Console.WriteLine($"Количество изменённых строк: {changed}");
	}
	else
	{
		Console.WriteLine("Товаров не найдено");
	}
}

Console.Write("Введите ID товара: ");
if (!int.TryParse(Console.ReadLine(), out int productId))
{
    Console.WriteLine("Некорректный ID. Введите целое число.");
}
else
{
    Console.Write("Введите новую доступность товара (True | False): ");
    if (!bool.TryParse(Console.ReadLine(), out bool isAvailable))
    {
        Console.WriteLine("Некорректное значение. Введите True или False.");
    }
    else
    {
        try
        {
            await UpdateProductAvailabilityAsync(connectionString, productId, isAvailable);
        }
        catch (SqlException ex)
        {
            Console.WriteLine($"Ошибка SQL (Part 5): {ex.Message}");
        }
    }
}


// part 7

Console.WriteLine("\nPart 7");

while (true)
{
    Console.WriteLine("\n=== Каталог кофейни ===");
    Console.WriteLine("1. Показать все товары");
    Console.WriteLine("2. Показать только доступные товары");
    Console.WriteLine("3. Найти товары по части названия");
    Console.WriteLine("4. Показать число клиентов");
    Console.WriteLine("5. Изменить доступность товара");
    Console.WriteLine("0. Выход");
    Console.Write("Выбор: ");


    string choice = Console.ReadLine()!;

    switch (choice)
    {
        case "1":
        {
			try
			{
				await ShowProductsAsync(connectionString);
			}
			catch (SqlException ex)
			{
				Console.WriteLine($"Ошибка SQL: {ex.Message}");
			}

            break;
        }

        case "2":
        {
			static async Task ShowAvailableProductsAsync(string connectionString)
			{
				await using SqlConnection connection = new SqlConnection(connectionString);
				await connection.OpenAsync();

				using SqlCommand command = new SqlCommand(
					"SELECT id, name, price FROM products WHERE is_available = 1 ORDER BY name", connection);

				await using SqlDataReader reader = await command.ExecuteReaderAsync();

				if (reader.HasRows){
					while (await reader.ReadAsync())
					{
						int id = reader.GetInt32(0);
						string name = reader.GetString(1);
						decimal price = reader.GetDecimal(2);
						Console.WriteLine($"{id}. {name} — {price} руб.");
					}
				}
				else
				{
					Console.WriteLine("Товары не найдены");
				}
			}

			try
			{
				await ShowAvailableProductsAsync(connectionString);
			}
			catch (SqlException ex)
			{
				Console.WriteLine($"Ошибка SQL: {ex.Message}");
			}

			break;
        }

        case "3":
        {
			static async Task ShowProductsByNameAsync(string connectionString)
			{
				await using SqlConnection connection = new SqlConnection(connectionString);
				await connection.OpenAsync();

				using SqlCommand command = new SqlCommand(
						"SELECT id, name, price, is_available FROM products WHERE name LIKE @search", connection);

				Console.Write("Введите название или часть названия товара: ");
				string search = Console.ReadLine()!;

				command.Parameters.AddWithValue("@search", $"%{search}%");

				await using SqlDataReader reader = await command.ExecuteReaderAsync();

				if (reader.HasRows){
					while (await reader.ReadAsync())
					{
						int id = reader.GetInt32(0);
						string name = reader.GetString(1);
						decimal price = reader.GetDecimal(2);
						bool available = reader.GetBoolean(3);
						Console.WriteLine($"{id}. {name} — {price} руб. | {(available ? "Есть" : "Нет")}");
					}
				}
				else
				{
					Console.WriteLine("Товары не найдены");
				}
			}

			try
			{
				await ShowProductsByNameAsync(connectionString);
			}
			catch (SqlException ex)
			{
				Console.WriteLine($"Ошибка SQL: {ex.Message}");
			}
			
            break;
        }

        case "4":
        {
			static async Task<int> GetCustomerCountAsync(string connectionString)
			{
				await using SqlConnection connection =
					new SqlConnection(connectionString);
				await connection.OpenAsync();
				using SqlCommand command = new SqlCommand(
					"SELECT COUNT(*) FROM customers", connection);
				return (int)(await command.ExecuteScalarAsync())!;
			}

			try
			{
				int count = await GetCustomerCountAsync(connectionString);
				Console.WriteLine($"Количество клиентов: {count}");
			}
			catch (SqlException ex)
			{
				Console.WriteLine($"Ошибка SQL: {ex.Message}");
			}

			break;
        }

        case "5":
        {
            Console.Write("Введите ID товара: ");
			if (!int.TryParse(Console.ReadLine(), out int productChangeId))
			{
				Console.WriteLine("Некорректный ID. Введите целое число.");
			}
			else
			{
				Console.Write("Введите новую доступность товара (True | False): ");
				if (!bool.TryParse(Console.ReadLine(), out bool isAvailableChange))
				{
					Console.WriteLine("Некорректное значение. Введите True или False.");
				}
				else
				{
					try
					{
						await UpdateProductAvailabilityAsync(connectionString, productChangeId, isAvailableChange);
					}
					catch (SqlException ex)
					{
						Console.WriteLine($"Ошибка SQL: {ex.Message}");
					}
				}
        	}

			break;
        }

        case "0":
            return;

        default:
            Console.WriteLine("Неверный пункт.");
            break;
    }
}
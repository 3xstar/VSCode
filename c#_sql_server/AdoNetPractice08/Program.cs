using System.Data;
using Microsoft.Data.SqlClient;

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";



Console.WriteLine("Part 2");

static DataTable LoadProducts(string connectionString)
{
 string sql = """
 SELECT id, name, category_id, price, is_available
 FROM products
 ORDER BY id
 """;

 using SqlConnection connection = new SqlConnection(connectionString);
 using SqlDataAdapter adapter = new SqlDataAdapter(sql, connection);

 DataTable table = new DataTable("products");
 adapter.Fill(table);

 return table;
}


DataTable products = LoadProducts(connectionString);
Console.WriteLine($"Загружено товаров: {products.Rows.Count}");



Console.WriteLine("\n\nPart 3");

foreach (DataRow row in products.Rows)
{
 int id = row.Field<int>("id");
 string name = row.Field<string>("name")!;
 decimal price = row.Field<decimal>("price");
 bool available = row.Field<bool>("is_available");

 Console.WriteLine($"{id}. {name} — {price} руб. | " +
 (available ? "Доступен" : "Недоступен"));
}



Console.WriteLine("\n\nPart 4");

Console.WriteLine("\nДоступные товары по увеличиванию цены");
DataRow[] availableProducts =
 products.Select("is_available = true", "price ASC");

foreach (DataRow row in availableProducts)
{
    Console.WriteLine($"{row["name"]} — {row["price"]} руб.");
}


Console.WriteLine("\nТовары с ценой > 200");
DataRow[] morethan200Products =
 products.Select("price > 200");

foreach (DataRow row in morethan200Products)
{
    Console.WriteLine($"{row["name"]} — {row["price"]} руб.");
}


Console.WriteLine("\nДоступные товары по уменьшению цены");
DataRow[] availableProducts2 =
 products.Select("is_available = true", "price DESC");

foreach (DataRow row in availableProducts2)
{
    Console.WriteLine($"{row["name"]} — {row["price"]} руб.");
}


int availableCount = Convert.ToInt32(products.Compute("COUNT(id)", "is_available = true"));
Console.WriteLine($"\nВсего доступных товаров в памяти: {availableCount}");



Console.WriteLine("\n\nPart 5");

DataSet dataSet = new DataSet("CoffeeShop");

using SqlConnection connection = new SqlConnection(connectionString);

using SqlDataAdapter productsAdapter = new SqlDataAdapter(
 "SELECT id, name, category_id, price, is_available FROM products",
 connection);

using SqlDataAdapter categoriesAdapter = new SqlDataAdapter(
 "SELECT id, name FROM categories",
 connection);

productsAdapter.Fill(dataSet, "products");
categoriesAdapter.Fill(dataSet, "categories");

Console.WriteLine($"Загружено таблиц: {dataSet.Tables.Count}");


if (dataSet.Tables["products"] != null && dataSet.Tables["categories"] != null)
{
    Console.WriteLine("SUCCESS: Обе таблицы доступны в DataSet");
}
else
{
    Console.WriteLine("ERROR: Одна из таблиц не загрузилась");
}

int productsCount = dataSet.Tables["products"]?.Rows.Count ?? 0;
int categoriesCount = dataSet.Tables["categories"]?.Rows.Count ?? 0;

Console.WriteLine($"Количество строк в таблице products: {productsCount}");
Console.WriteLine($"Количество строк в таблице categories: {categoriesCount}");



Console.WriteLine("\n\nPart 6");

DataTable categories = dataSet.Tables["categories"]!;
DataTable productTable = dataSet.Tables["products"]!;

dataSet.Relations.Add(
 "category_products",
 categories.Columns["id"]!,
 productTable.Columns["category_id"]!);

foreach (DataRow category in categories.Rows)
{
 Console.WriteLine($"Категория: {category["name"]}");
 
 foreach (DataRow product in category.GetChildRows("category_products"))
 {
    Console.WriteLine($" - {product["name"]}");
 }
}



Console.WriteLine("\n\nPart 7");

if (products.Rows.Count > 0)
{
 DataRow firstProduct = products.Rows[0];

 Console.WriteLine($"До: {firstProduct["price"]}");

 firstProduct["price"] = 999m;

 Console.WriteLine($"После: {firstProduct["price"]}");

 Console.WriteLine($"Состояние: {firstProduct.RowState}");
}



Console.WriteLine("\n\nPart 8");

bool isRunning = true;
while (isRunning)
{
    Console.WriteLine("\n=== СOFFEE CAFE CATALOG ===");
    Console.WriteLine("1. Загрузить данные о товарах и категориях из SQL Server.");
    Console.WriteLine("2. Показать все товары.");
    Console.WriteLine("3. Показать только доступные товары.");
    Console.WriteLine("4. Отсортировать товары по цене.");
    Console.WriteLine("5. Показать товары выбранной категории.");
    Console.WriteLine("6. Изменить цену выбранного товара в памяти и вывести RowState.");
    Console.WriteLine("7. Повторно загрузить таблицу из базы и сравнить цену с локальной версией.");
    Console.WriteLine("8. Завершить программу.");
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

                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "2":
                try
                {

                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "3":
                try
                {

                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "4":
                try
                {

                }
                catch (SqlException ex)
                {
                    Console.WriteLine($"Ошибка SQL: {ex.Message}");
                }

                break;
            case "5":
                break;
            case "8":
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
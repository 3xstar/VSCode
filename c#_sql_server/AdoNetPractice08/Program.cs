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
                dataSet.Relations.Clear();
                dataSet.Tables.Clear();

                using (SqlDataAdapter freshProductsAdapter = new SqlDataAdapter(
                    "SELECT id, name, category_id, price, is_available FROM products", connectionString))
                using (SqlDataAdapter freshCategoriesAdapter = new SqlDataAdapter(
                    "SELECT id, name FROM categories", connectionString))
                {
                    freshProductsAdapter.Fill(dataSet, "products");
                    freshCategoriesAdapter.Fill(dataSet, "categories");
                }

                dataSet.Relations.Add(
                "category_products",
                dataSet.Tables["categories"]!.Columns["id"]!,
                dataSet.Tables["products"]!.Columns["category_id"]!);

                Console.WriteLine("Данные с SQL Server успешно загружены");
                Console.WriteLine($"Загружено категорий: {dataSet.Tables["categories"]!.Rows.Count}\nЗагружено товаров: {dataSet.Tables["products"]!.Rows.Count}");
                break;

            case "2":
                if (dataSet.Tables["products"] == null || dataSet.Tables["products"].Rows.Count == 0)
                {
                    Console.WriteLine("Каталог пуст. Сначала загрузите данные (Пункт 1)");
                    break;
                }
                Console.WriteLine("Все товары (из памяти)");
                foreach (DataRow row in dataSet.Tables["products"].Rows)
                {
                    Console.WriteLine($"[{row["id"]}] {row["name"]} — {row["price"]} руб. | {(Convert.ToBoolean(row["is_available"]) ? "Доступен" : "Недоступен")}");
                }
                break;

            case "3":
                if (dataSet.Tables["products"] == null || dataSet.Tables["products"].Rows.Count == 0)
                {
                    Console.WriteLine("Каталог пуст. Сначала загрузите данные (Пункт 1)");
                    break;
                }
                Console.WriteLine("--- Только доступные товары (из памяти) ---");
                DataRow[] availableRows = dataSet.Tables["products"].Select("is_available = true");
                if (availableRows.Length == 0)
                {
                    Console.WriteLine("Доступных товаров нет.");
                }
                else
                {
                    foreach (DataRow row in availableRows)
                    {
                        Console.WriteLine($"[{row["id"]}] {row["name"]} — {row["price"]} руб.");
                    }
                }
                break;

            case "4":
                if (dataSet.Tables["products"] == null || dataSet.Tables["products"].Rows.Count == 0)
                {
                    Console.WriteLine("Каталог пуст. Сначала загрузите данные (Пункт 1)");
                    break;
                }
                Console.WriteLine("Выберите сортировку:\n1. По возрастанию цены\n2. По убыванию цены");
                Console.Write("Ваш выбор: ");
                string? sortChoice = Console.ReadLine();

                string sortOrder = sortChoice == "2" ? "price DESC" : "price ASC";
                DataRow[] sortedRows = dataSet.Tables["products"].Select("", sortOrder);

                Console.WriteLine($"\nСортировка [{sortOrder}]");
                foreach (DataRow row in sortedRows)
                {
                    Console.WriteLine($"{row["name"]} — {row["price"]} руб.");
                }
                break;

            case "5":
                if (dataSet.Tables["categories"] == null || dataSet.Tables["categories"].Rows.Count == 0)
                {
                    Console.WriteLine("Данные не загружены. Выберите пункт 1");
                    break;
                }
                Console.WriteLine("Доступные категории:");
                foreach (DataRow cat in dataSet.Tables["categories"].Rows)
                {
                    Console.WriteLine($"{cat["id"]}. {cat["name"]}");
                }
                Console.Write("\nВведите ID выбранной категории: ");
                if (int.TryParse(Console.ReadLine(), out int chosenCatId))
                {
                    DataRow[] foundCats = dataSet.Tables["categories"].Select($"id = {chosenCatId}");
                    if (foundCats.Length == 0)
                    {
                        Console.WriteLine("Категория с таким ID не найдена");
                        break;
                    }

                    Console.WriteLine($"\n--- Товары категории: {foundCats[0]["name"]} ---");
                    DataRow[] childProducts = foundCats[0].GetChildRows("category_products");
                    if (childProducts.Length == 0)
                    {
                        Console.WriteLine("В этой категории нет товаров.");
                    }
                    else
                    {
                        foreach (DataRow prod in childProducts)
                        {
                            Console.WriteLine($" - {prod["name"]} ({prod["price"]} руб.)");
                        }
                    }
                }
                else
                {
                    Console.WriteLine("Некорректный ввод ID.");
                }
                break;

            case "6":
                if (dataSet.Tables["products"] == null || dataSet.Tables["products"].Rows.Count == 0)
                {
                    Console.WriteLine("Данные не загружены. Выберите пункт 1");
                    break;
                }
                Console.Write("Введите ID товара, которому хотите изменить цену: ");
                if (int.TryParse(Console.ReadLine(), out int chosenProdId))
                {
                    DataRow[] foundProds = dataSet.Tables["products"].Select($"id = {chosenProdId}");
                    if (foundProds.Length == 0)
                    {
                        Console.WriteLine("Товар с таким ID не найден.");
                        break;
                    }
                    DataRow targetRow = foundProds[0];
                    Console.WriteLine($"Выбран товар: {targetRow["name"]}. Текущая цена: {targetRow["price"]}");
                    Console.Write("Введите новую цену: ");
                    if (decimal.TryParse(Console.ReadLine(), out decimal newPrice) && newPrice >= 0)
                    {
                        targetRow["price"] = newPrice;
                        Console.WriteLine("Цена изменена локально в памяти!");
                        Console.WriteLine($"Новая цена: {targetRow["price"]}");
                        Console.WriteLine($"Текущий RowState: {targetRow.RowState}");
                    }
                    else
                    {
                        Console.WriteLine("Некорректная цена.");
                    }
                }
                else
                {
                    Console.WriteLine("Некорректный ввод ID.");
                }
                break;

            case "7":
                if (dataSet.Tables["products"] == null || dataSet.Tables["products"].Rows.Count == 0)
                {
                    Console.WriteLine("Данные не загружены. Выберите пункт 1");
                    break;
                }
                Console.Write("Введите ID товара для сравнения версий: ");
                if (int.TryParse(Console.ReadLine(), out int compProdId))
                {
                    DataRow[] foundLocal = dataSet.Tables["products"].Select($"id = {compProdId}");
                    if (foundLocal.Length == 0)
                    {
                        Console.WriteLine("Товар не найден в локальной памяти");
                        break;
                    }
                    decimal localPrice = Convert.ToDecimal(foundLocal[0]["price"]);
                    decimal dbPrice = 0;
                    bool existsInDb = false;


                    using (SqlConnection dbConnection = new SqlConnection(connectionString))
                    {
                        string query = "SELECT price FROM products WHERE id = @id";
                        using SqlCommand command = new SqlCommand(query, dbConnection);
                        command.Parameters.AddWithValue("@id", compProdId);
                        dbConnection.Open();
                        object result = command.ExecuteScalar();
                        if (result != null)
                        {
                            dbPrice = Convert.ToDecimal(result);
                            existsInDb = true;
                        }
                    }
                    if (existsInDb)
                    {
                        Console.WriteLine($"\nТовар: {foundLocal[0]["name"]}");
                        Console.WriteLine($"Цена в локальной памяти (DataTable): {localPrice} руб. (Состояние: {foundLocal[0].RowState})");
                        Console.WriteLine($"Цена на сервере (SQL Server):        {dbPrice} руб.");
                        if (localPrice != dbPrice)
                        {
                            Console.WriteLine("РЕЗУЛЬТАТ: Цены отличаются, так как изменения не отправлялись на server");
                        }
                        else
                        {
                            Console.WriteLine("РЕЗУЛЬТАТ: Цены совпадают");
                        }
                    }
                    else
                    {
                        Console.WriteLine("Товар был удален из базы данных SQL Server");
                    }
                }
                else
                {
                    Console.WriteLine("Некорректный ввод ID");
                }
                break;

            case "8":
                isRunning = false;
                break;

            default:
                Console.WriteLine("Неверный пункт меню. Попробуйте снова");
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
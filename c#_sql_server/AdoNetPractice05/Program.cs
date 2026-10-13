// part 1

using Microsoft.Data.SqlClient;

string connectionString =
 "Server=localhost;Database=CoffeeShop;Trusted_Connection=True;TrustServerCertificate=True;";



// part 2-3

Console.WriteLine("Part 2-3");

using var connection = new SqlConnection(connectionString);
connection.Open();

using (SqlTransaction transaction = connection.BeginTransaction())
{
    try
    {
        using SqlCommand command1 = new SqlCommand(
            "UPDATE products SET price = @price WHERE id = @id",
            connection,
            transaction);

        command1.Parameters.AddWithValue("@price", 250m);
        command1.Parameters.AddWithValue("@id", 1);

        int rowsAffected1 = command1.ExecuteNonQuery();


        using SqlCommand command2 = new SqlCommand(
            "UPDATE products SET price = @price WHERE id = @id",
            connection,
            transaction);
            
        command2.Parameters.AddWithValue("@price", 300m);
        command2.Parameters.AddWithValue("@id", 2);

        int rowsAffected2 = command2.ExecuteNonQuery();


        if (rowsAffected1 == 1 && rowsAffected2 == 1)
        {
            // ERROR FOR TEST (PART 3)
            // throw new InvalidOperationException("TEST ERROR");
            transaction.Commit();
            Console.WriteLine("SUCCESS: Rows updated");
        }
        else
        {
            transaction.Rollback();
            Console.WriteLine("ERROR: wrong rows values");
        }
    }
    catch(Exception ex)
    {
        try {transaction.Rollback();}
        catch (Exception rollbackEx)
        {
            Console.WriteLine($"ROLLBACK ERROR: {rollbackEx.Message}");
        }

        Console.WriteLine($"CRITICAL ERROR: {ex.Message}");
    }
}


// part 4

Console.WriteLine("\nPart 4");

try
{
    string sql4 = """
        SELECT id, full_name FROM customers;
        SELECT id, name, price FROM products;
        """;

    using SqlCommand command4 = new SqlCommand(sql4, connection);
    using SqlDataReader reader = command4.ExecuteReader();

    if (reader.HasRows)
    {
        while (reader.Read())
        {
            int customer_id = reader.GetInt32(0);
            string customer_name = reader.GetString(1);
            Console.WriteLine($"CLIENT {customer_id}. {customer_name}");
            Console.WriteLine();
        }
    }
    else
    {
        Console.WriteLine("Clients not exists");
    }

    if (reader.NextResult())
    {
        while (reader.Read())
        {
            int product_id = reader.GetInt32(0);
            string product_name = reader.GetString(1);
            decimal product_price = reader.GetDecimal(2);
            Console.WriteLine($"PRODUCT {product_id}. {product_name} | PRICE: {product_price}");
        }
    }
    else
    {
        Console.WriteLine("Products not exists");
    }

    reader.Close();
}
catch(Exception ex)
{
    Console.WriteLine($"CRITICAL ERROR: {ex.Message}");
}



// part 5-6

Console.WriteLine("\nPart 5-6");

Console.Write("Введите ID клиента для оформления заказа: ");
int customerId = Convert.ToInt32(Console.ReadLine());

Console.Write("Введите ID товара: ");
int productId = Convert.ToInt32(Console.ReadLine());

Console.Write("Введите количество товара: ");
int quantity = Convert.ToInt32(Console.ReadLine());

Console.Write("Введите цену товара : ");
decimal unitPrice = Convert.ToDecimal(Console.ReadLine());

using (SqlTransaction transaction5 = connection.BeginTransaction())
{
    try
    {
        string sql5_1 = """
            INSERT INTO orders (customer_id, order_date, status)
            VALUES (@customer_id, SYSDATETIME(), N'Новый');
            SELECT CAST(SCOPE_IDENTITY() AS int);
        """;

        using SqlCommand command5_1 = new SqlCommand(sql5_1, connection, transaction5);
        command5_1.Parameters.AddWithValue("@customer_id", customerId);

        int orderId = (int)command5_1.ExecuteScalar()!;


        string sql5_2 = """
            INSERT INTO order_items (order_id, product_id, quantity, unit_price)
            VALUES (@order_id, @product_id, @quantity, @unit_price);
        """;

        using SqlCommand command5_2 = new SqlCommand(sql5_2, connection, transaction5);
        command5_2.Parameters.AddWithValue("@order_id", orderId);
        command5_2.Parameters.AddWithValue("@product_id", productId);
        command5_2.Parameters.AddWithValue("@quantity", quantity);
        command5_2.Parameters.AddWithValue("@unit_price", unitPrice);

        int itemRows = command5_2.ExecuteNonQuery();


        if (itemRows == 1)
        {
            transaction5.Commit();
            Console.WriteLine($"SUCCESS: order created\nNew order ID: {orderId}");
        }
        else
        {
            transaction5.Rollback();
            Console.WriteLine("ERROR: wrong rows values");
        }
    }
    catch(Exception ex)
    {
        try {transaction5.Rollback();}
        catch (Exception rollbackEx)
        {
            Console.WriteLine($"ROLLBACK ERROR: {rollbackEx.Message}");
        }

        Console.WriteLine($"CRITICAL ERROR: {ex.Message}");
    }
}



// part 7

Console.WriteLine("\nPart 7");

try
{
    string sql7 = """
        SELECT o.id, o.order_date, o.status, oi.product_id,
            oi.quantity, oi.unit_price
        FROM orders AS o
        JOIN order_items AS oi ON oi.order_id = o.id
        ORDER BY o.id DESC;
        """;

    using SqlCommand command7 = new SqlCommand(sql7, connection);
    using SqlDataReader reader = command7.ExecuteReader();

    if (reader.HasRows)
    {
        // throw new InvalidOperationException("TEST ERROR");
        while (reader.Read())
        {
            int orderId = reader.GetInt32(0);
            DateTime orderDate = reader.GetDateTime(1);
            string status = reader.GetString(2);
            int productId7 = reader.GetInt32(3);
            int quantity7 = reader.GetInt32(4);
            decimal unitPrice7 = reader.GetDecimal(5);

            Console.WriteLine($"ORDER №{orderId} from {orderDate:dd.MM.yyyy HH:mm} [STATUS: {status}]");
            Console.WriteLine($"  -> Product ID: {productId7} | QUANTITY: {quantity7} | Price for 1: {unitPrice7} руб.");
            Console.WriteLine();
        }
    }
    else
    {
        Console.WriteLine("Orders and positions not exists");
    }

    reader.Close();
}
catch(Exception ex)
{
    Console.WriteLine($"CRITICAL ERROR: {ex.Message}");
}



// part 8

Console.WriteLine("\nPart 8");

Console.Write("Введите ID клиента: ");
int custId = Convert.ToInt32(Console.ReadLine());

Console.Write("Введите ID первого товара: ");
int prodId1 = Convert.ToInt32(Console.ReadLine());
Console.Write("Введите количество первого товара: ");
int qty1 = Convert.ToInt32(Console.ReadLine());

Console.Write("Введите ID второго товара: ");
int prodId2 = Convert.ToInt32(Console.ReadLine());
Console.Write("Введите количество второго товара: ");
int qty2 = Convert.ToInt32(Console.ReadLine());


decimal price1 = 0;
decimal price2 = 0;

using (SqlCommand cmdPrice1 = new SqlCommand("SELECT price FROM products WHERE id = @id", connection))
{
    cmdPrice1.Parameters.AddWithValue("@id", prodId1);
    object res = cmdPrice1.ExecuteScalar()!;
    if (res != null) price1 = (decimal)res;
}

using (SqlCommand cmdPrice2 = new SqlCommand("SELECT price FROM products WHERE id = @id", connection))
{
    cmdPrice2.Parameters.AddWithValue("@id", prodId2);
    object res = cmdPrice2.ExecuteScalar()!;
    if (res != null) price2 = (decimal)res;
}


if (price1 == 0 || price2 == 0)
{
    Console.WriteLine("ERROR: Один или оба товара не существуют в базе данных! Транзакция даже не начнется.");
    return;
}


using (SqlTransaction transaction8 = connection.BeginTransaction())
{
    try
    {
        string sqlOrder = """
            INSERT INTO orders (customer_id, order_date, status)
            VALUES (@customer_id, SYSDATETIME(), N'Новый');
            SELECT CAST(SCOPE_IDENTITY() AS int);
        """;

        using SqlCommand cmdOrder = new SqlCommand(sqlOrder, connection, transaction8);
        cmdOrder.Parameters.AddWithValue("@customer_id", custId);
        
        int newOrderId = (int)cmdOrder.ExecuteScalar()!;


        string sqlItem = """
            INSERT INTO order_items (order_id, product_id, quantity, unit_price)
            VALUES (@order_id, @product_id, @quantity, @unit_price);
        """;

        using SqlCommand Item1 = new SqlCommand(sqlItem, connection, transaction8);
        Item1.Parameters.AddWithValue("@order_id", newOrderId);
        Item1.Parameters.AddWithValue("@product_id", prodId1);
        Item1.Parameters.AddWithValue("@quantity", qty1);
        Item1.Parameters.AddWithValue("@unit_price", price1);

        int ItemRows1 = Item1.ExecuteNonQuery();


        using SqlCommand Item2 = new SqlCommand(sqlItem, connection, transaction8);
        Item2.Parameters.AddWithValue("@order_id", newOrderId);
        Item2.Parameters.AddWithValue("@product_id", prodId2);
        Item2.Parameters.AddWithValue("@quantity", qty2);
        Item2.Parameters.AddWithValue("@unit_price", price2);

        int ItemRows2 = Item2.ExecuteNonQuery();


        if (ItemRows1 == 1 &&  ItemRows2 == 1)
        {
            transaction8.Commit();

            decimal totalSum = (price1 * qty1) + (price2 * qty2);
            
            Console.WriteLine("\n[SUCCESS] Transaction successfully fixated!");
            Console.WriteLine($"Created order ID: {newOrderId}");
            Console.WriteLine($"Total order sum: {totalSum} руб.");
        }
        else
        {
            transaction8.Rollback();
            Console.WriteLine("ERROR: Failed to add one of the items");
        }
    }
    catch (Exception ex)
    {
        try {transaction8.Rollback();}
        catch (Exception rollbackEx)
        {
            Console.WriteLine($"ROLLBACK ERROR: {rollbackEx.Message}");
        }

        Console.WriteLine($"CRITICAL ERROR: {ex.Message}");
        Console.WriteLine("ORDER CANCELED");
    }
}

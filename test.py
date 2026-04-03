class User:
    def __init__(self, login: str, password: str):
        self.login = login
        self.__password = password
        self.orders = []
    
    def add_order(self, order: 'Order'):
        self.orders.append(order)
    
    def get_orders(self) -> list:
        return self.orders

class Order:
    def __init__(self, order_id: int, total: float):
        self.order_id = order_id
        self.total = total
        self.items = []
    
    def add_item(self, product: 'Product', quantity: int):
        self.items.append({'product': product, 'qty': quantity})
    
    def get_total(self) -> float:
        return self.total

class Product:
    def __init__(self, name: str, price: float):
        self.name = name
        self.price = price
    
    def get_price(self) -> float:
        return self.price

class Cart:
    def __init__(self, user: User):
        self.user = user
        self.products = []
    
    def add_to_cart(self, product: Product):
        self.products.append(product)
    
    def show_cart(self):
        if not self.products:
            print("Корзина пуста")
            return
        
        print(f"\n🛒 Корзина пользователя {self.user.login}:")
        print("-" * 50)
        for i, product in enumerate(self.products, 1):
            print(f"{i}. {product.name} — {product.price}руб")
        print("-" * 50)
        total = sum(p.price for p in self.products)
        print(f"Итого: {total}руб\n")
    
    def checkout(self) -> Order:
        if not self.products:
            return None
        
        total = sum(p.price for p in self.products)
        order = Order(order_id=1, total=total)
        
        for product in self.products:
            order.add_item(product, 1)
        
        self.products = []  
        return order

if __name__ == "__main__":
    p1 = Product("Чипсики", 200.0)
    p2 = Product("Энергетический напиток Flash с ментолом и соленым перцем", 100.0)
    
    u1 = User("Захар", "12345")
    
    cart = Cart(u1)
    cart.add_to_cart(p1)
    cart.add_to_cart(p2)
    
    cart.show_cart()
    
    order = cart.checkout()
    if order:
        u1.add_order(order)
        print(f"Заказ {order.order_id} создан на сумму {order.total}руб")
    else:
        print("Корзина пуста")
    
    print(f"У пользователя {u1.login} заказов: {len(u1.get_orders())}")

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <algorithm>

// Класс для товара
class Product {
public:
    std::string name;
    int quantity;

    Product(const std::string& name, int quantity) : name(name), quantity(quantity) {}
};

// Класс для склада
class Warehouse {
public:
    std::string location;
    std::vector<Product> products;

    Warehouse(const std::string& location) : location(location) {}

    void addProduct(const Product& product) {
        products.push_back(product);
        notify("Product added: " + product.name);
    }

    void removeProduct(const std::string& productName) {
        auto it = std::remove_if(products.begin(), products.end(),
            [&productName](const Product& p) { return p.name == productName; });
        if (it != products.end()) {
            notify("Product removed: " + productName);
            products.erase(it, products.end());
        }
        else {
            std::cout << "Product not found: " << productName << std::endl;
        }
    }

    void editProduct(const std::string& productName, int newQuantity) {
        for (auto& product : products) {
            if (product.name == productName) {
                product.quantity = newQuantity;
                notify("Product edited: " + productName + " New quantity: " + std::to_string(newQuantity));
                return;
            }
        }
        std::cout << "Product not found for editing: " << productName << std::endl;
    }

    // Сигналы для событий
    std::function<void(const std::string&)> notify;
};

// Класс для логирования событий
class EventLogger {
public:
    void logEvent(const std::string& message) {
        std::ofstream logFile("events.log", std::ios::app);
        if (logFile.is_open()) {
            logFile << message << std::endl;
            logFile.close();
        }
        std::cout << message << std::endl; // Выводим сообщение в консоль
    }
};

// Класс для управления товарами
class ProductManager {
private:
    Warehouse& warehouse;
    EventLogger logger;

public:
    ProductManager(Warehouse& warehouse) : warehouse(warehouse) {
        warehouse.notify = [this](const std::string& message) { logger.logEvent(message); };
    }

    void createProduct(const std::string& name, int quantity) {
        Product product(name, quantity);
        warehouse.addProduct(product);
    }

    void deleteProduct(const std::string& name) {
        warehouse.removeProduct(name);
    }

    void updateProduct(const std::string& name, int newQuantity) {
        warehouse.editProduct(name, newQuantity);
    }
};

int main() {
    Warehouse warehouse("Main Warehouse");
    ProductManager manager(warehouse);

    manager.createProduct("Milk", 10);
    manager.createProduct("Cookies", 20);
    manager.updateProduct("Milk", 15);
    manager.deleteProduct("Cookies");
    manager.deleteProduct("Chocolate"); // Попытка удалить несуществующий товар
    manager.updateProduct("Coca-Cola", 5); // Попытка редактировать несуществующий товар

    return 0;
}
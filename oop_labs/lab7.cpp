#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

// Перечисление типов событий
enum class EventType {
    CREATE_PRODUCT,
    DELETE_PRODUCT,
    EDIT_PRODUCT
};

// Класс-товар
class Product {
private:
    string name;
    int quantity;
public:
    Product(const string& productName, int productQuantity)
        : name(productName), quantity(productQuantity) {
    }

    string getName() const { return name; }
    int getQuantity() const { return quantity; }

    void setName(const string& newName) { name = newName; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
};

// Класс-склад
class Warehouse {
private:
    string name;
    vector<Product> products;
public:
    Warehouse(const string& warehouseName) : name(warehouseName) {}

    string getName() const { return name; }

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void removeProduct(const string& productName) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getName() == productName) {
                products.erase(it);
                break;
            }
        }
    }

    void editProduct(const string& productName, const string& newName, int newQuantity) {
        for (auto& product : products) {
            if (product.getName() == productName) {
                product.setName(newName);
                product.setQuantity(newQuantity);
                break;
            }
        }
    }

    void displayProducts() const {
        cout << "Склад: " << name << "\n";
        for (const auto& product : products) {
            cout << "Товар: " << product.getName() << ", Количество: " << product.getQuantity() << "\n";
        }
    }
};

// Класс для логирования событий в файл
class EventLogger {
private:
    ofstream logFile;
public:
    EventLogger(const string& filename) {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            cerr << "Не удалось открыть файл для записи.\n";
        }
    }

    ~EventLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void logEvent(const string& event) {
        if (logFile.is_open()) {
            logFile << event << endl;
        }
    }
};

// Класс для управления событиями и подписчиками
class EventManager {
private:
    map<EventType, vector<function<void(const string&)>>> listeners;
public:
    void subscribe(EventType eventType, function<void(const string&)> listener) {
        listeners[eventType].push_back(listener);
    }

    void trigger(EventType eventType, const string& message) {
        if (listeners.find(eventType) != listeners.end()) {
            for (auto& listener : listeners[eventType]) {
                listener(message);
            }
        }
    }
};

// Класс с общим перечнем товаров
class ProductList {
private:
    map<string, vector<string>> productLocations;
public:
    void addProduct(const string& productName, const string& warehouseName) {
        productLocations[productName].push_back(warehouseName);
    }

    void removeProduct(const string& productName, const string& warehouseName) {
        auto it = productLocations.find(productName);
        if (it != productLocations.end()) {
            auto& locations = it->second;
            for (auto locIt = locations.begin(); locIt != locations.end(); ++locIt) {
                if (*locIt == warehouseName) {
                    locations.erase(locIt);
                    if (locations.empty()) {
                        productLocations.erase(it);
                    }
                    break;
                }
            }
        }
    }

    void editProduct(const string& oldProductName, const string& newProductName) {
        if (productLocations.find(oldProductName) != productLocations.end()) {
            productLocations[newProductName] = productLocations[oldProductName];
            productLocations.erase(oldProductName);
        }
    }

    void displayProductList() const {
        cout << "\n=== Общий перечень товаров ===\n";
        if (productLocations.empty()) {
            cout << "Товаров нет.\n";
            return;
        }
        for (const auto& pair : productLocations) {
            cout << "Товар: " << pair.first << ", Расположение: ";
            for (const auto& location : pair.second) {
                cout << location << " ";
            }
            cout << "\n";
        }
    }
};

// Главная функция с меню
int main() {
    setlocale(LC_ALL, "RU");
    // Создаем менеджер событий, логгер и общий перечень товаров
    EventManager eventManager;
    EventLogger logger("events.log");
    ProductList productList;

    // Подписываемся на события для логирования и обновления общего перечня товаров
    eventManager.subscribe(EventType::CREATE_PRODUCT, [&](const string& msg) {
        logger.logEvent(msg);
        });

    eventManager.subscribe(EventType::DELETE_PRODUCT, [&](const string& msg) {
        logger.logEvent(msg);
        });

    eventManager.subscribe(EventType::EDIT_PRODUCT, [&](const string& msg) {
        logger.logEvent(msg);
        });

    // Создаем склад
    Warehouse warehouse("Склад 1");

    int choice;
    do {
        cout << "\n=== Меню ===\n";
        cout << "1. Добавить товар на склад\n";
        cout << "2. Удалить товар со склада\n";
        cout << "3. Редактировать товар на складе\n";
        cout << "4. Показать товары на складе\n";
        cout << "5. Показать общий перечень товаров\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        // Обработка некорректного ввода
        if (cin.fail()) {
            cin.clear(); // Сброс состояния ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорирование некорректных символов
            cout << "Некорректный ввод. Пожалуйста, введите число от 0 до 5.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            string name;
            int quantity;
            cout << "Введите название товара: ";
            cin.ignore(); // Очистка буфера ввода
            getline(cin, name);
            cout << "Введите количество товара: ";
            cin >> quantity;
            Product product(name, quantity);
            warehouse.addProduct(product);
            string msg = "Создан товар: " + name + ", Количество: " + to_string(quantity) + ", Склад: " + warehouse.getName();
            cout << msg << endl;
            eventManager.trigger(EventType::CREATE_PRODUCT, msg);
            productList.addProduct(name, warehouse.getName());
            break;
        }
        case 2: {
            string name;
            cout << "Введите название товара для удаления: ";
            cin.ignore(); // Очистка буфера ввода
            getline(cin, name);
            warehouse.removeProduct(name);
            string msg = "Удален товар: " + name + ", Склад: " + warehouse.getName();
            cout << msg << endl;
            eventManager.trigger(EventType::DELETE_PRODUCT, msg);
            productList.removeProduct(name, warehouse.getName());
            break;
        }
        case 3: {
            string oldName, newName;
            int newQuantity;
            cout << "Введите текущее название товара: ";
            cin.ignore(); // Очистка буфера ввода
            getline(cin, oldName);
            cout << "Введите новое название товара: ";
            getline(cin, newName);
            cout << "Введите новое количество товара: ";
            cin >> newQuantity;
            warehouse.editProduct(oldName, newName, newQuantity);
            string msg = "Отредактирован товар: " + oldName + " -> " + newName + ", Количество: " + to_string(newQuantity) + ", Склад: " + warehouse.getName();
            cout << msg << endl;
            eventManager.trigger(EventType::EDIT_PRODUCT, msg);
            productList.editProduct(oldName, newName);
            break;
        }
        case 4: {
            warehouse.displayProducts();
            break;
        }
        case 5: {
            productList.displayProductList();
            break;
        }
        case 0: {
            cout << "Выход из программы.\n";
            break;
        }
        default: {
            cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <windows.h> // Подключение библиотеки Windows

using namespace std; // Использование пространства имен std

// Базовый класс для исключений матрицы
class MatrixException : public exception {
protected:
    string message;
public:
    MatrixException(const string& msg) : message(msg) {}
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Исключение для неверных индексов
class InvalidIndexException : public MatrixException {
public:
    InvalidIndexException(const string& msg) : MatrixException(msg) {}
};

// Исключение для несоответствия размеров матриц
class DimensionMismatchException : public MatrixException {
public:
    DimensionMismatchException(const string& msg) : MatrixException(msg) {}
};

class Matrix {
private:
    vector<vector<int>> data; // Двумерный вектор для хранения элементов матрицы
    int rows; // Количество строк
    int cols; // Количество столбцов

public:
    // Конструктор, который инициализирует матрицу заданного размера
    Matrix(int r, int c) : rows(r), cols(c) {
        if (r <= 0 || c <= 0) {
            throw InvalidIndexException("Размеры матрицы должны быть положительными числами.");
        }
        data.resize(rows, vector<int>(cols, 0)); // Заполнение матрицы нулями
    }

    // Деструктор (по умолчанию)
    ~Matrix() {}

    // Метод для установки значения элемента матрицы
    void setValue(int r, int c, int value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value; // Установка значения, если индексы в пределах
        }
        else {
            throw InvalidIndexException("Индекс вне границ матрицы!");
        }
    }

    // Метод для получения значения элемента матрицы
    int getValue(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return data[r][c]; // Возврат значения, если индексы в пределах
        }
        else {
            throw InvalidIndexException("Индекс вне границ матрицы!");
        }
    }

    // Перегрузка оператора вычитания
    Matrix operator-(const Matrix& other) const {
        // Проверка на совпадение размеров матриц
        if (rows != other.rows || cols != other.cols) {
            throw DimensionMismatchException("Размеры матриц должны совпадать для вычитания.");
        }

        Matrix result(rows, cols); // Создание матрицы для результата
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Вычитание соответствующих элементов
                result.setValue(i, j, this->getValue(i, j) - other.getValue(i, j));
            }
        }
        return result; // Возврат результирующей матрицы
    }

    // Перегрузка оператора сложения
    Matrix operator+(const Matrix& other) const {
        // Проверка на совпадение размеров матриц
        if (rows != other.rows || cols != other.cols) {
            throw DimensionMismatchException("Размеры матриц должны совпадать для сложения.");
        }

        Matrix result(rows, cols); // Создание матрицы для результата
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Сложение соответствующих элементов
                result.setValue(i, j, this->getValue(i, j) + other.getValue(i, j));
            }
        }
        return result; // Возврат результирующей матрицы
    }

    // Перегрузка оператора умножения
    Matrix operator*(const Matrix& other) const {
        // Проверка возможности умножения (количество столбцов первой матрицы должно равняться количеству строк второй)
        if (cols != other.rows) {
            throw DimensionMismatchException("Количество столбцов первой матрицы должно равняться количеству строк второй матрицы для умножения.");
        }

        Matrix result(rows, other.cols); // Создание матрицы для результата
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                int sum = 0;
                for (int k = 0; k < cols; ++k) {
                    sum += this->getValue(i, k) * other.getValue(k, j);
                }
                result.setValue(i, j, sum);
            }
        }
        return result; // Возврат результирующей матрицы
    }

    // Перегрузка оператора присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) { // Проверка на самоприсваивание
            rows = other.rows; // Копирование количества строк
            cols = other.cols; // Копирование количества столбцов
            data = other.data; // Копирование данных матрицы
        }
        return *this; // Возврат текущего объекта
    }

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
        for (const auto& row : matrix.data) { // Проход по каждой строке
            for (const auto& elem : row) { // Проход по каждому элементу строки
                os << elem << " "; // Вывод элемента
            }
            os << endl; // Переход на новую строку после вывода строки
        }
        return os;
    }

    // Метод для вывода матрицы на экран
    void print() const {
        for (const auto& row : data) { // Проход по каждой строке
            for (const auto& elem : row) { // Проход по каждому элементу строки
                cout << elem << " "; // Вывод элемента
            }
            cout << endl; // Переход на новую строку после вывода строки
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); // Установка кодировки для консольного вывода

    try {
        // Создание матриц A и B размером 2x2
        Matrix A(2, 2);
        Matrix B(2, 2);

        // Установка значений для матрицы A
        A.setValue(0, 0, 5);
        A.setValue(0, 1, 3);
        A.setValue(1, 0, 4);
        A.setValue(1, 1, 2);

        // Установка значений для матрицы B
        B.setValue(0, 0, 2);
        B.setValue(0, 1, 1);
        B.setValue(1, 0, 3);
        B.setValue(1, 1, 1);

        // Вычитание матриц
        Matrix C = A - B; // Результат вычитания A - B сохраняется в C

        // Сложение матриц
        Matrix D = A + B; // Результат сложения A + B сохраняется в D

        // Умножение матриц (пример корректного умножения)
        Matrix E(2, 3);
        E.setValue(0, 0, 1);
        E.setValue(0, 1, 2);
        E.setValue(0, 2, 3);
        E.setValue(1, 0, 4);
        E.setValue(1, 1, 5);
        E.setValue(1, 2, 6);

        Matrix F(3, 2);
        F.setValue(0, 0, 7);
        F.setValue(0, 1, 8);
        F.setValue(1, 0, 9);
        F.setValue(1, 1, 10);
        F.setValue(2, 0, 11);
        F.setValue(2, 1, 12);

        Matrix G = E * F; // Результат умножения E * F сохраняется в G

        // Вывод матриц на экран
        cout << "Матрица A:" << endl;
        cout << A;

        cout << "Матрица B:" << endl;
        cout << B;

        cout << "Матрица C (A - B):" << endl;
        cout << C;

        cout << "Матрица D (A + B):" << endl;
        cout << D;

        cout << "Матрица E:" << endl;
        cout << E;

        cout << "Матрица F:" << endl;
        cout << F;

        cout << "Матрица G (E * F):" << endl;
        cout << G;

        // Пример обработки исключений при неправильных индексах
        cout << "Попытка установить значение с неверными индексами:" << endl;
        A.setValue(2, 2, 10); // Это вызовет исключение
    }
    catch (const InvalidIndexException& ex) {
        cerr << "Ошибка индексации: " << ex.what() << endl;
    }
    catch (const DimensionMismatchException& ex) {
        cerr << "Ошибка размеров матриц: " << ex.what() << endl;
    }
    catch (const MatrixException& ex) {
        cerr << "Общая ошибка матрицы: " << ex.what() << endl;
    }
    catch (const exception& ex) {
        cerr << "Неизвестная ошибка: " << ex.what() << endl;
    }

    return 0; // Завершение программы
}

#include <iostream>
#include <vector>
#include <stdexcept>

class MatrixException : public std::exception {
public:
    explicit MatrixException(const char* message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_;
    }
private:
    const char* msg_;
};

class SizeMismatchException : public MatrixException {
public:
    SizeMismatchException() : MatrixException("Size mismatch between matrices") {}
};

class Matrix {
private:
    std::vector<std::vector<int>> data;
    size_t rows;
    size_t cols;

public:
    // Конструктор
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<int>(c, 0)) {}

    // Метод для установки значения элемента
    void set(size_t r, size_t c, int value) {
        if (r >= rows || c >= cols) {
            throw MatrixException("Index out of bounds");
        }
        data[r][c] = value;
    }

    // Перегрузка оператора сложения
    Matrix operator+(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw SizeMismatchException();
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Метод для вывода матрицы
    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        Matrix A(2, 2);
        Matrix B(2, 2);

        A.set(0, 0, 1);
        A.set(0, 1, 2);
        A.set(1, 0, 3);
        A.set(1, 1, 4);

        B.set(0, 0, 5);
        B.set(0, 1, 6);
        B.set(1, 0, 7);
        B.set(1, 1, 8);

        Matrix C = A + B; // Сложение матриц
        std::cout << "Matrix C (A + B):" << std::endl;
        C.print();
    }
    catch (const MatrixException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
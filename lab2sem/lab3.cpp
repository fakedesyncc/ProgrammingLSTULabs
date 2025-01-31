/* лаб 3 прога 2 сем */
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

// Функция для подсчета количества слов длиной 3 символа
void countWordsOfLength(std::string text) {
    std::string word;
    bool found = false;

    std::cout << "Слова длиной 3 символа: ";
    for (char c : text) {
        if (c == '/' || c == ' ') {
            if (word.length() == 3) {
                std::cout << word << " ";
                found = true;
            }
            word = "";
        } else {
            word += c;
        }
    }

    if (word.length() == 3) {
        std::cout << word << " ";
        found = true;
    }

    if (!found) {
        std::cout << "Нет слов длиной 3 символа в строке.";
    }
    std::cout << std::endl;
}

// Функция для вычисления средней длины слова в строке
void averageWordLength(std::string text) {
    int totalLength = 0;
    int wordCount = 0;
    std::string word;
    for (char c : text) {
        if (c == '/' || c == ' ') {
            if (!word.empty()) {
                totalLength += word.length();
                wordCount++;
            }
            word = "";
        } else {
            word += c;
        }
    }

    if (wordCount == 0) {
        std::cout << "Таких слов нет." << std::endl;
    } else {
        double average = static_cast<double>(totalLength) / wordCount;
        std::cout << "Средняя длина слова: " << average << std::endl;
    }
}

// Функция для перестановки слов в обратном порядке
void reverseWords(std::string text) {
    std::string reversedText;
    std::string word;
    for (char c : text) {
        if (c == '/' || c == ' ') {
            if (!word.empty()) {
                reversedText = word + " " + reversedText;
            }
            word = "";
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        reversedText = word + " " + reversedText;
    }

    std::cout << "Текст с переставленными словами в обратном порядке: " << reversedText << std::endl;
}

int main() {
    int inputChoice;
    std::string text;

    std::cout << "Выберите способ ввода данных:\n";
    std::cout << "1. Ввод с клавиатуры\n";
    std::cout << "2. Ввод из файла\n";
    std::cin >> inputChoice;

    if (inputChoice == 1) {
        std::cout << "Введите строку текста: ";
        std::cin.ignore();
        std::getline(std::cin, text);
    } else if (inputChoice == 2) {
        std::cout << "Введите имя файла: ";
        std::string filename;
        std::cin >> filename;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::getline(file, text);
            file.close();
        } else {
            std::cout << "Файл не найден." << std::endl;
            return 1;
        }
    } else {
        std::cout << "Некорректный выбор." << std::endl;
        return 1;
    }

    int methodChoice;
    std::cout << "Выберите способ формирования строк:\n";
    std::cout << "1. Через функции библиотеки string.h\n";
    std::cout << "2. Работа со строками как с массивами\n";
    std::cin >> methodChoice;

    if (methodChoice == 1) {
        // Реализация через функции библиотеки string.h
    } else if (methodChoice == 2) {
        // Реализация работы со строками как с массивами
    }

    countWordsOfLength(text);
    averageWordLength(text);
    reverseWords(text);

    int outputChoice;
    std::cout << "Выберите способ вывода данных:\n";
    std::cout << "1. Вывод на экран\n";
    std::cout << "2. Запись в файл\n";
    std::cin >> outputChoice;

    if (outputChoice == 1) {
        // Вывод на экран
    } else if (outputChoice == 2) {
        std::cout << "Введите имя файла для записи: ";
        std::string outputFilename;
        std::cin >> outputFilename;
        std::ofstream outputFile(outputFilename);
        if (outputFile.is_open()) {
            outputFile << "Исходные данные:\n" << text << "\n\n";
            outputFile << "Результаты:\n";
            // Запись результатов в файл
            outputFile.close();
        } else {
std::cout << "Ошибка при открытии файла для записи." << std::endl;
            return 1;
        }
    } else {
        std::cout << "Некорректный выбор." << std::endl;
        return 1;
    }

    return 0;
}
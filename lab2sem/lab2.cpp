**lab2sem2**
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct Record {
    std::string name;
    int attribute1;
    int attribute2;
};

const int MAX_RECORDS = 100;
Record records[MAX_RECORDS];
int recordCount = 0;

void displayMenu();
void readFromFile(const std::string&, bool isBinary);
void writeToFile(const std::string&, bool isBinary);
void readFromKeyboard();
void displayData();
void calculateAndDisplaySummary();
void addRecord();
void deleteRecord();
void handleFileError(const std::string&);

int main() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: {
                int inputChoice;
                std::cout << "Select input method:\n1. Text file\n2. Binary file\n3. Keyboard\n";
                std::cin >> inputChoice;
                if (inputChoice == 1) {
                    readFromFile("data.txt", false);
                } else if (inputChoice == 2) {
                    readFromFile("data.bin", true);
                } else if (inputChoice == 3) {
                    readFromKeyboard();
                } else {
                    std::cerr << "Invalid option.\n";
                }
                break;
            }
            case 2:
                displayData();
                break;
            case 3:
                calculateAndDisplaySummary();
                break;
            case 4:
                addRecord();
                break;
            case 5:
                deleteRecord();
                break;
            case 6: {
                int outputChoice;
                std::cout << "Select output method:\n1. Text file\n2. Binary file\n";
                std::cin >> outputChoice;
                if (outputChoice == 1) {
                    writeToFile("data.txt", false);
                } else if (outputChoice == 2) {
                    writeToFile("data.bin", true);
                } else {
                    std::cerr << "Invalid option.\n";
                }
                break;
            }
            case 7:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cerr << "Invalid option, try again.\n";
        }
    } while (choice != 7);
    return 0;
}

void displayMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Input Data\n";
    std::cout << "2. Display Data\n";
    std::cout << "3. Calculate Summary\n";
    std::cout << "4. Add Record\n";
    std::cout << "5. Delete Record\n";
    std::cout << "6. Save Data\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

void readFromFile(const std::string& filename, bool isBinary) {
    std::ifstream file;
    if (isBinary) {
        file.open(filename, std::ios::binary);
    } else {
        file.open(filename);
    }
    if (!file) {
        handleFileError(filename);
        return;
    }
    recordCount = 0;
    while (file && recordCount < MAX_RECORDS) {
        if (isBinary) {
            file.read(reinterpret_cast<char*>(&records[recordCount]), sizeof(Record));
        } else {
            file >> records[recordCount].name >> records[recordCount].attribute1 >> records[recordCount].attribute2;
        }
        if (file) {
            ++recordCount;
        }
    }
    file.close();
}

void writeToFile(const std::string& filename, bool isBinary) {
    std::ofstream file;
    if (isBinary) {
        file.open(filename, std::ios::binary);
    } else {
        file.open(filename);
    }
    if (!file) {
        handleFileError(filename);
        return;
    }
    for (int i = 0; i < recordCount; ++i) {
        if (isBinary) {
            file.write(reinterpret_cast<const char*>(&records[i]), sizeof(Record));
        } else {
            file << records[i].name << ' ' << records[i].attribute1 << ' ' << records[i].attribute2 << '\n';
        }
    }
    file.close();
}

void readFromKeyboard() {
    std::cout << "Enter the number of records: ";
    std::cin >> recordCount;
    if (recordCount > MAX_RECORDS) {
std::cerr << "Exceeding maximum records limit.\n";
        recordCount = MAX_RECORDS;
    }
    for (int i = 0; i < recordCount; ++i) {
        std::cout << "Enter name, attribute1, attribute2: ";
        std::cin >> records[i].name >> records[i].attribute1 >> records[i].attribute2;
    }
}

void displayData() {
    std::cout << std::setw(5) << "No" << std::setw(20) << "Name" << std::setw(10) << "Attr1" << std::setw(10) << "Attr2" << '\n';
    for (int i = 0; i < recordCount; ++i) {
        std::cout << std::setw(5) << i + 1 << std::setw(20) << records[i].name << std::setw(10) << records[i].attribute1 << std::setw(10) << records[i].attribute2 << '\n';
    }
}

void calculateAndDisplaySummary() {
    if (recordCount == 0) {
        std::cerr << "No records to summarize.\n";
        return;
    }
    int sumAttr1 = 0, sumAttr2 = 0;
    for (int i = 0; i < recordCount; ++i) {
        sumAttr1 += records[i].attribute1;
        sumAttr2 += records[i].attribute2;
    }
    std::cout << "Average Attribute 1: " << static_cast<double>(sumAttr1) / recordCount << '\n';
    std::cout << "Average Attribute 2: " << static_cast<double>(sumAttr2) / recordCount << '\n';
}

void addRecord() {
    if (recordCount >= MAX_RECORDS) {
        std::cerr << "Cannot add more records, array is full.\n";
        return;
    }
    std::cout << "Enter name, attribute1, attribute2: ";
    std::cin >> records[recordCount].name >> records[recordCount].attribute1 >> records[recordCount].attribute2;
    ++recordCount;
}

void deleteRecord() {
    int recordNumber;
    std::cout << "Enter the record number to delete: ";
    std::cin >> recordNumber;
    if (recordNumber < 1 || recordNumber > recordCount) {
        std::cerr << "Invalid record number.\n";
        return;
    }
    for (int i = recordNumber - 1; i < recordCount - 1; ++i) {
        records[i] = records[i + 1];
    }
    --recordCount;
}

void handleFileError(const std::string& filename) {
    std::cerr << "Error opening file: " << filename << '\n';
}
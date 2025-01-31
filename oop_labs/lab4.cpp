#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Базовый класс для условного знака
class Symbol {
protected:
    std::string name;         // Название
    std::string description;  // Описание

public:
    Symbol(const std::string& name = "", const std::string& description = "")
        : name(name), description(description) {
    }

    virtual ~Symbol() = default;

    virtual void print() const {
        std::cout << "Name: " << name << ", Description: " << description << std::endl;
    }

    virtual void serialize(std::ostream& out) const {
        out << "<Symbol>\n";
        out << "  <Name>" << name << "</Name>\n";
        out << "  <Description>" << description << "</Description>\n";
        out << "</Symbol>\n";
    }

    virtual void deserialize(std::istream& in) {
        std::getline(in, name, '\n'); // Считываем до конца строки
        name = name.substr(name.find(">") + 1, name.find("</") - name.find(">") - 1);

        std::getline(in, description, '\n');
        description = description.substr(description.find(">") + 1, description.find("</") - description.find(">") - 1);

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропустить </Symbol>
    }

    virtual std::string getType() const {
        return "Symbol";
    }
};

// Наследуемый класс с дополнительными атрибутами
class GraphicSymbol : public Symbol {
private:
    std::string color; // Цвет символа
    int size;          // Размер символа

public:
    GraphicSymbol(const std::string& name = "", const std::string& description = "",
        const std::string& color = "", int size = 0)
        : Symbol(name, description), color(color), size(size) {
    }

    void print() const override {
        Symbol::print();
        std::cout << "Color: " << color << ", Size: " << size << std::endl;
    }

    void serialize(std::ostream& out) const override {
        out << "<GraphicSymbol>\n";
        out << "  <Name>" << name << "</Name>\n";
        out << "  <Description>" << description << "</Description>\n";
        out << "  <Color>" << color << "</Color>\n";
        out << "  <Size>" << size << "</Size>\n";
        out << "</GraphicSymbol>\n";
    }

    void deserialize(std::istream& in) override {
        std::getline(in, name, '\n');
        name = name.substr(name.find(">") + 1, name.find("</") - name.find(">") - 1);

        std::getline(in, description, '\n');
        description = description.substr(description.find(">") + 1, description.find("</") - description.find(">") - 1);

        std::getline(in, color, '\n');
        color = color.substr(color.find(">") + 1, color.find("</") - color.find(">") - 1);

        std::string sizeStr;
        std::getline(in, sizeStr, '\n');
        size = std::stoi(sizeStr.substr(sizeStr.find(">") + 1, sizeStr.find("</") - sizeStr.find(">") - 1));

        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропустить </GraphicSymbol>
    }

    std::string getType() const override {
        return "GraphicSymbol";
    }
};

// Класс-агрегатор для управления справочником
class SymbolDirectory {
private:
    std::vector<Symbol*> symbols;

public:
    ~SymbolDirectory() {
        for (Symbol* symbol : symbols) {
            delete symbol;
        }
    }

    void addSymbol(Symbol* symbol) {
        symbols.push_back(symbol);
    }

    void deleteSymbol(size_t index) {
        if (index < symbols.size()) {
            delete symbols[index];
            symbols.erase(symbols.begin() + index);
        }
    }

    void print() const {
        for (size_t i = 0; i < symbols.size(); ++i) {
            std::cout << "Symbol " << i + 1 << ":" << std::endl;
            symbols[i]->print();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for writing: " << filename << std::endl;
            return;
        }

        file << "<Symbols>\n";
        for (const Symbol* symbol : symbols) {
            symbol->serialize(file);
        }
        file << "</Symbols>\n";

        file.close();
        std::cout << "Symbols successfully saved to " << filename << std::endl;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return;
        }

        std::string line;
        std::getline(file, line); // Пропустить <Symbols>

        while (std::getline(file, line)) {
            if (line.find("<Symbol>") != std::string::npos) {
                Symbol* symbol = new Symbol();
                symbol->deserialize(file);
                symbols.push_back(symbol);
            }
            else if (line.find("<GraphicSymbol>") != std::string::npos) {
                GraphicSymbol* symbol = new GraphicSymbol();
                symbol->deserialize(file);
                symbols.push_back(symbol);
            }
            else if (line.find("</Symbols>") != std::string::npos) {
                break;
            }
        }

        file.close();
        std::cout << "Symbols successfully loaded from " << filename << std::endl;
    }
};

int main() {
    SymbolDirectory directory;

    // Добавление символов
    directory.addSymbol(new Symbol("BasicSymbol", "A simple symbol"));
    directory.addSymbol(new GraphicSymbol("GraphicSymbol", "A graphic symbol", "Red", 10));

    // Печать символов
    std::cout << "Initial Symbols:" << std::endl;
    directory.print();

    // Сохранение в файл
    const std::string filename = "symbols.xml";
    directory.saveToFile(filename);

    // Загрузка из файла
    SymbolDirectory loadedDirectory;
    loadedDirectory.loadFromFile(filename);

    // Печать загруженных символов
    std::cout << "\nLoaded Symbols:" << std::endl;
    loadedDirectory.print();

    return 0;
}

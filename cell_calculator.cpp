#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "cell_calculator.h"

using namespace csv;

// удаляет знак равенства в начале строки
std::string removeEqualChar(const std::string &token) {
    std::string result = token;
    if (token.compare(0, 1, "=") == 0) {
        result = token.substr(1, token.size() - 1);
    }
    return result;
}

int csv::calculate(const cell_address_t &addr, const table_t &csv) {
    if (addr.empty()) {
        throw std::runtime_error("A cell with an empty value was passed.");
    }
    std::string token = csv.at(addr);
    token = removeEqualChar(token);

    std::string first_arg;
    std::string second_arg;
    char operation;
    bool flag = false;

    // п.4 алгоритма
    for (int j = 0; j < token.length(); j++) {
        if (token[j] == '+' || token[j] == '-' || token[j] == '*' || token[j] == '/') {
            first_arg = token.substr(0, j);
            second_arg = token.substr(j + 1, token.length());
            operation = token[j];
            flag = true;
            break;
        }
    }
    int result;
    if (flag) {
        int a = calculate(first_arg, csv);
        int b = calculate(second_arg, csv);
        switch (operation) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
        }

        // п.2 алгоритма
    } else if (!isdigit(token[0])) {
        std::string cellValue = csv.at(token);
        cellValue = removeEqualChar(cellValue);

        if (!isdigit(cellValue[0])) {
            result = calculate(cellValue, csv);
        } else {
            result = stoi(cellValue);
        }
        return result;

        // п.3 алгоритма
    } else {

        //число записать
        result = stoi(token);
        return result;
    }
}

// п.1 алгоритма
csv::table_t getTable(const std::string &path) {
    std::ifstream file(path, std::ios::in);
    std::string input;
    std::getline(file, input);

    size_t pos = input.find(',');

    csv::table_t table;
    csv::cell_data_t cellData = "";
    csv::cell_address_t cellAddress = "";
    input.erase(0, pos + 1);

    // заполняю вектор названиями столбцов
    std::vector<std::string> vec;
    while ((pos = input.find(',')) != std::string::npos) {
        cellData = input.substr(0, pos);
        vec.push_back(cellData);
        input.erase(0, pos + 1);
    }
    vec.push_back(input);

    const int tableLineSize = vec.size();
    std::string currentLineValue;
    while (file >> input) {
        std::stringstream ss(input);
        for (int i = 0; getline(ss, cellData, ','); i++) {

            // исключаю названия строк из таблицы
            int remainder = i % tableLineSize;
            if (remainder == 0 && i != tableLineSize) {
                currentLineValue = cellData;
                continue;
            }

            cellAddress = vec.at(i - 1) + currentLineValue;
            table[cellAddress] = cellData;
        }
    }
    return table;
}
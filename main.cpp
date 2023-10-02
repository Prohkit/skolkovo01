#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include "iostream"
#include "cell_calculator.h"

using namespace csv;

int main(int argc, char *argv[]) {
    table_t table = getTable(argv[1]);

    // вычисляем ячейки по очереди и выводим их значения
    auto it = table.begin();
    for (int i = 1; it != table.end(); it++, i++) {
        std::cout << " i= " << i << ": " << it->first << " " << calculate(it->first, table) << "\n";
    }
    return 0;
}

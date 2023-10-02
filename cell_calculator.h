#ifndef SKOLKOVO01_CELL_CALCULATOR_H
#define SKOLKOVO01_CELL_CALCULATOR_H

#include <map>

namespace csv {

    using cell_address_t = std::string;
    using cell_data_t = std::string;
    using table_t = std::map<cell_address_t, cell_data_t>;

    int calculate(const cell_address_t &addr, const table_t &csv);
}

std::string removeEqualChar(const std::string &token);

csv::table_t getTable(const std::string &path);

#endif

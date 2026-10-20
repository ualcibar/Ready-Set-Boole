#include "sat.hpp"

bool sat(std::vector<std::map<char, int>> truth_table) {
    for (const auto& line : truth_table) {
        auto result = line.find('=');
        if (result->second)
            return true;
    }
    return false;
}
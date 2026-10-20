#include "sat.hpp"

bool exec_sat(std::vector<std::vector<std::map<char, int>>> truth_table) {
    for (const auto& line : truth_table) {

        auto result = line[line.size() - 1].find('=');
        if (result->second)
            return true;
    }
    return false;
}

bool sat(std::string formula) {
    std::set<char> letters;

    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        if (!check_formula(*it))
            return false;
    }
    return exec_sat(truth_table(formula));
}
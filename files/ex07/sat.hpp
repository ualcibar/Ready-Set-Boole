#ifndef SAT.HPP
#define SAT.HPP

#include "truth_table.hpp"

bool exec_sat(std::vector<std::vector<std::map<char, int>>> truth_table);
bool sat(std::string formula);

#endif
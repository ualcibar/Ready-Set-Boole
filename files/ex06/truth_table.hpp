#ifndef TRUTHTABLE_HPP
#define TRUTHTABLE_HPP

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

#include "RPN.hpp"
#include "adder.hpp"

std::vector<std::vector<std::map<char, int>>> truth_table(std::string formula);
void print_truth_table (std::vector<std::vector<std::map<char, int>>> truth_table);

#endif
#ifndef EVAL_SET_HPP
#define EVAL_SET_HPP

#include <vector>
#include <stack>
#include <map>
#include <string>
#include <algorithm>

#include "RPN.hpp"

std::vector<int> eval_set(std::string formula, std::vector<std::vector<int>> sets);
std::vector<int> exec_set_operation(std::vector<int> set_a, std::vector<int> set_b, std::vector<int> global_set, char operator_simbol);


#endif
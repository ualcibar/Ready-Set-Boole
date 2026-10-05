#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include "adder.hpp"
#include <memory>

enum Opertors {
    AND = '&', 
    NOT = '!', 
    OR = '|', 
    XOR = '^', 
    MATERIAL_CONDITION = '>', 
    LOGICAL_EQUIVALENCE = '='
};

bool RPN_bool (std::string stack);
bool isOperator(char operator_simbol);
bool extract_bit(std::stack <bool> &operate);
bool exec_operation(bool bit_a, bool bit_b, char operator_simbol);
bool AST(std::string stack);
bool truth_table (std::string formula);

#endif
#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>

enum Opertors {
    AND = '&', 
    NOT = '!', 
    OR = '|', 
    XOR = '^', 
    MATERIAL_CONDITION = '>', 
    LOGICAL_EQUIVALENCE = '='
};

bool eval_formula (std::string formula);
bool is_operator (char operator_simbol);
bool is_bit(char bit);
bool is_operator(char operator_simbol);
bool extract_bit (std::stack <bool> &operate);
bool exec_operation (bool bit_a, bool bit_b, char operator_simbol);

#endif
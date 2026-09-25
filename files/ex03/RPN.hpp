#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <vector>

enum Opertors {AND = '&', NOT = '!', OR = '|', XOR = '^', MATERIAL_CONDITION = '>', LOGICAL_EQUIVALENCE = '='};

bool RPN_bool (std::string stack);

#endif
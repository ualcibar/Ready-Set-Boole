#include "RPN.hpp"

bool isOperator(char operator_simbol) {
    switch (operator_simbol) {
        case AND:
        case NOT:
        case OR:
        case XOR:
        case MATERIAL_CONDITION:
        case LOGICAL_EQUIVALENCE:
            return true;
        default:
            return false;
    }
}
bool exec_operation(bool bit_a, bool bit_b, char operator_simbol) {
    switch (operator_simbol) {
        case AND:
            return (bit_a & bit_b);
        case OR:
            return (bit_a | bit_b);
        case XOR:
            return (bit_a ^ bit_b);
        case MATERIAL_CONDITION:
            return (!bit_a | bit_b);
        case LOGICAL_EQUIVALENCE:
            return (!(bit_a ^ bit_b));
    }
    return 0;
}

bool RPN_bool(std::string stack) {
    std::vector<bool> operate;
    bool a;
    bool b;

    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        if((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() == 0)) {
            std::cout << "Invalid formula\n";
            return 0;
        }
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE:
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();

                operate.push_back(exec_operation(a, b, *it));
                break;
            case NOT:
                a = operate.back();
                operate.pop_back();
                operate.push_back(!a);
                break;
            case '1':
                operate.push_back(true); 
                break;
            case '0':
                operate.push_back(false); 
                break;
        }
    }
    return operate.back();
}
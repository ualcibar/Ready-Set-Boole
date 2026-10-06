#include "RPN.hpp"

bool is_operator(char operator_simbol) {
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

bool is_bit(char bit) {
    switch (bit) {
        case '1':
        case '0':
            return true;
        default:
            return false;
    }
}

bool extract_bit(std::stack <bool> &operate) {
    bool bit = operate.top();
    operate.pop();
    return bit;
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

bool eval_formula(std::string formula) {
    std::stack<bool> operate;
    bool a;
    bool b;

    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        if(!(is_operator(*it) || is_bit(*it)) /*|| ((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() > 0))*/) {
            
            std::cout << "Invalid formula\n";
            return 0;
        }
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE:
                b = operate.top();
                operate.pop();
                a = operate.top();
                operate.pop();

                operate.push(exec_operation(a, b, *it));
                break;
            case NOT:
                a = operate.top();
                operate.pop();
                operate.push(!a);
                break;
            case '1':
                operate.push(true); 
                break;
            case '0':
                operate.push(false); 
                break;
        }
    }
    return operate.top();
}

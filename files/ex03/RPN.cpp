#include "RPN.hpp"

bool isOperator(char c) {
    switch (c) {
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
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();
                operate.push_back((a & b));
                break;
            case NOT:
                a = operate.back();
                operate.pop_back();
                operate.push_back(!a);
                break;
            case OR: 
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();
                operate.push_back((a | b));
                break;
            case XOR: 
                std::cout << "XOR\n";
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();
                operate.push_back((a ^ b));
                break;
            case '1':
                operate.push_back(true); 
                break;
            case '0':
                operate.push_back(false); 
                break;
            case MATERIAL_CONDITION: 
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();
                operate.push_back((!a | b));
                break;
            case LOGICAL_EQUIVALENCE:
                b = operate.back();
                operate.pop_back();
                a = operate.back();
                operate.pop_back();
                operate.push_back(!(a ^ b));             
                std::cout << "LOGICAL_EQUIVALENCE\n";  
                break;
        }
    }
    return operate.back();
}
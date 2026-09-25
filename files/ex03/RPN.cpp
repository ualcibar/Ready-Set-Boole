#include "RPN.hpp"
        
bool RPN_bool(std::string stack) {
    std::vector<bool> operate;

    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        switch(*it) {
                case AND  : std::cout << "AND\n";   break;
                case NOT : std::cout << "NOT\n"; break;
                case OR : std::cout << "OR\n"; break;
                case XOR : std::cout << "XOR\n"; break;
                case MATERIAL_CONDITION : std::cout << "MATERIAL_CONDITION\n"; break;
                case LOGICAL_EQUIVALENCE  : std::cout << "LOGICAL_EQUIVALENCE\n";  break;
                case '1' : operate.push_back(true); break;
                case '0' : operate.push_back(false); break;
        }
    }
    return 1;
}
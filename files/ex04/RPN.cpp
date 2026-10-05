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

bool isBit(char bit) {
    switch (bit) {
        case '1':
        case '0':
            return true;
        default:
            return false;
    }
}

bool isLetterUppercase (char letter) {
    if ((letter >= 65) & (letter <= 90))
        return true;
    return false;
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

bool RPN_bool(std::string stack) {
    std::stack<bool> operate;
    bool a;
    bool b;

    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        if(!(isOperator(*it) || isBit(*it)) /*|| ((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() > 0))*/) {
            
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

bool check_formula (char formula) {
    if (isBit (formula) | isLetterUppercase(formula) | isOperator(formula))
        return true;
    return false;
}

bool truth_table (std::string formula) {

    std::set<char> letters;
    std::vector<std::map<char, int>> truth_table_line;
    std::vector<std::vector<std::map<char, int>>> truth_table;
    std::vector<int> result;
    
    int max_number = 0;
    int letter_cont = 0;
    int i = 0;
    
    std::cout << formula << "\n";
    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        if (!check_formula(*it))
        return false;
        if (isLetterUppercase(*it)) {
            letters.insert(*it); 
        }
    }
    
    
    letter_cont = letters.size();
    max_number = (1 << letter_cont) - 1;
    std::string vars(letters.begin(), letters.end());
    std::cout << "Letters: " << vars << "\n";
    std::cout << "Max number: " << max_number << "\n";
    std::cout << "letter_cont: " << letter_cont << "\n";

    while (i <= max_number) {
        int t = 0;
        std::vector<std::map<char, int>> truth_table_line;
        std::map<char, int> result;
        int complete_bit = i;

        while (t < letter_cont)
        {
            int bit = !extract_first_bit(complete_bit);
            std::map<char, int> value;
            value[vars[t]] = bit;
            complete_bit = complete_bit >> 1;
            //std::cout << "complete_bit: " << complete_bit << ' ';
            truth_table_line.push_back(value);
            //std::cout << vars[t] << '=' << bit << ' ';
            t++;
        }
        std::string replaced = formula;

        for (const std::map<char, int>& value : truth_table_line) { 
            char letra = value.begin()->first;
            int  bit   = value.begin()->second;
            if (bit)
                std::replace(replaced.begin(), replaced.end(), letra, '1');
            else 
                std::replace(replaced.begin(), replaced.end(), letra, '0');
        }
        result['='] = RPN_bool(replaced);
        truth_table_line.push_back(result);
        truth_table.push_back(truth_table_line);
        i++;
    }

    // cabecera
for (size_t t = 0; t < vars.size(); t++)
    std::cout << "| " << vars[t] << ' ';
std::cout << "| " << '=' << ' ';
std::cout << "|\n";

// filas
for (const auto& line : truth_table) {           // cada fila
    for (const auto& value : line)               // cada map (una letra)
        for (const auto& p : value)              // su único par letra/bit
            std::cout << "| " << p.second << ' ';
    std::cout << "|\n";
}

return 1;
}
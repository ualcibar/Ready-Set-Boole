#include "eval_set.hpp"

std::vector<int> not_set_operation (std::vector<int> set_a, std::vector<int> global_set) {
    std::vector<int> result;    
    for (int x : global_set) {
        if (std::find(set_a.begin(), set_a.end(), x) == set_a.end())
            result.push_back(x);
    }
    return result;
}
std::vector<int> exec_set_operation(std::vector<int> set_a, std::vector<int> set_b, std::vector<int> global_set, char operator_simbol) {
    std::vector<int> result;

    switch (operator_simbol) {
        case AND:
            for (int x : set_b) {
                if (std::find(set_a.begin(), set_a.end(), x) == set_a.end())
                    set_a.push_back(x);
            }
            return (set_a);
        case OR:
            for (int x : set_a) {
                if (std::find(set_b.begin(), set_b.end(), x) == set_b.end())
                    result.push_back(x);
            }
            return (result);
        case XOR:
            for (int x : set_a) {
                if (std::find(set_b.begin(), set_b.end(), x) == set_b.end())
                    result.push_back(x);
            }
            for (int x : set_b) {
                if (std::find(set_a.begin(), set_a.end(), x) == set_a.end())
                    result.push_back(x);
            }
            return (result);
        case MATERIAL_CONDITION:
            return exec_set_operation(not_set_operation(set_a, global_set), set_b, global_set, OR);
        case LOGICAL_EQUIVALENCE:
            return (not_set_operation(exec_set_operation(set_a, set_b, global_set, XOR), global_set));
    }
    return result;
}

std::vector<int> eval_set(std::string formula, std::vector<std::vector<int>> sets) {
    
    std::map<char, std::vector<int>> set_map;
    std::vector<int> global_set;
    std::stack <std::vector<int>> operate;
    std::vector<int> set_a;
    std::vector<int> set_b;
    int i = 0;

    for (char c : formula) {
        if (c >= 'A' && c <= 'Z' && set_map.find(c) == set_map.end()) {
            if (i >= static_cast<int>(sets.size()))
                throw std::invalid_argument("Faltan conjuntos");
            set_map.emplace(c, sets[i]);
            i++;
        }
    }

    for (auto set : sets) {
        for (auto number : set) {
            if (std::count(global_set.begin(), global_set.end(), number) == 0)
            global_set.push_back(number);
        }
    }

    for (char c : formula) {
        if (c >= 'A' && c <= 'Z')
            operate.push(set_map[c]);
        else {
            switch(c) {
                case AND: 
                case XOR:
                case MATERIAL_CONDITION: 
                case OR: 
                case LOGICAL_EQUIVALENCE:
                    set_b = operate.top();
                    operate.pop();
                    set_a = operate.top();
                    operate.pop();
                    operate.push(exec_set_operation(set_b, set_b, global_set, c));
                    break;
                default:
                    throw std::invalid_argument("caracter de Formula invalido");
            }
        }
    }
    return operate.top();
}

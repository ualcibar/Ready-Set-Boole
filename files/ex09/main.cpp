#include <iostream>
#include <string>
#include "eval_set.hpp"

int main() {
    std::vector <std::vector <int>> sets;
    std::vector<int> set1;
    set1.push_back(6);
    set1.push_back(7);
    set1.push_back(1);
    set1.push_back(2);

    std::vector<int> set2;
    set2.push_back(6);
    set2.push_back(7);
    set2.push_back(2);
    set2.push_back(9);
    sets.push_back(set2);
    sets.push_back(set1);

    std::vector<int> result = eval_set("AB|", sets);
    for (int i : result) {
        std::cout << i << "\n";
    }
}
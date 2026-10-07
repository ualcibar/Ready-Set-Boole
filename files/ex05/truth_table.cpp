#include "truth_table.hpp"

bool is_letter_uppercase(char letter) {
    if ((letter >= 65) & (letter <= 90))
        return true;
    return false;
}

bool check_formula(char formula) {
    if (is_bit(formula) | is_letter_uppercase(formula) | is_operator(formula))
        return true;
    return false;
}

std::vector<std::vector<std::map<char, int>>> truth_table(std::string formula) {
    std::string replaced;
    std::set<char> letters;
    std::vector<int> result;
    std::vector<std::map<char, int>> truth_table_line;
    std::vector<std::vector<std::map<char, int>>> truth_table;

    int max_number = 0;
    int letter_cont = 0;
    int i = 0;
    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        if (!check_formula(*it))
            return truth_table;
        if (is_letter_uppercase(*it)) {
            letters.insert(*it); 
        }
    }
    letter_cont = letters.size();
    max_number = (1 << letter_cont) - 1;
    std::string vars(letters.begin(), letters.end());
    while (i <= max_number) {
        int t = 0;
        std::vector<std::map<char, int>> truth_table_line;
        std::map<char, int> result;
        int complete_bit = i;

        while (t < letter_cont)
        {
            std::map<char, int> value;
            int bit;

            bit = !extract_first_bit(complete_bit);
            value[vars[t]] = bit;
            complete_bit = complete_bit >> 1;
            truth_table_line.push_back(value);
            t++;
        }
        replaced = formula;
        for (const std::map<char, int>& value : truth_table_line) { 
            char letra = value.begin()->first;
            int  bit   = value.begin()->second;
            if (bit)
                std::replace(replaced.begin(), replaced.end(), letra, '1');
            else 
                std::replace(replaced.begin(), replaced.end(), letra, '0');
        }
        result['='] = eval_formula(replaced);
        truth_table_line.push_back(result);
        truth_table.push_back(truth_table_line);
        i++;
    }
    return truth_table;
}

void print_truth_table (std::vector<std::vector<std::map<char, int>>> truth_table) {
    if (truth_table.empty())
        return;

    for (const auto& value : truth_table[0])
        for (const auto& p : value)
            std::cout << "| " << p.first << ' ';
    std::cout << "| = |\n";

    for (const auto& line : truth_table) {
        for (const auto& value : line)
            for (const auto& p : value)
                std::cout << "| " << p.second << ' ';
        std::cout << "|\n";
    }
}
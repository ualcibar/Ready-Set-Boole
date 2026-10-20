#include "powerset.hpp"

std::vector<std::vector<int>> powerset (std::vector<int> set) {
    int size_set;
    int max_number;
    int i = 0;
    std::vector<std::vector<int>> powerset;

    size_set = set.size() - 1;
    max_number = (1 << size_set) - 1;

    while (i <= max_number) {
        std::vector<int> tmp_set;
        int complete_bit = i;
        int t = 0;

        while (t < size_set)
        {
            int bit;
            std::vector<int> tmp_set;

            bit = !extract_first_bit(complete_bit);
            if (bit == 1) {
                tmp_set.push_back(set[t]);
            }
            complete_bit = complete_bit >> 1;
            t++;
        }
        powerset.push_back(tmp_set);
        i++;
    }
    return powerset;
}

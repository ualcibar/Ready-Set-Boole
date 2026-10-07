#include "multiplier.hpp"
        
uint32_t multiplier(uint32_t a, uint32_t b) {
    int i = 0;
    uint32_t result = 0;

    while (b != 0)
    {
        if (extract_first_bit(b) == 1) {
            result = adder(result, a << i);
        }  
        i++;
        b = b >> 1;
    }
    return result;
}
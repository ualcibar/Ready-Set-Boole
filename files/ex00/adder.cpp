#include "adder.hpp"

uint32_t extract_first_bit(uint32_t num)
{
    return num & 1;
}

void addOperation(uint32_t a, uint32_t b, uint32_t *result, uint32_t *c_in) {
    *result = (a ^ b) ^ *c_in;
    *c_in = ((a ^ b) & *c_in) | (a & b);
}
        
uint32_t adder(uint32_t a, uint32_t b) {
    uint32_t result_bit;
    uint32_t result = 0;
    uint32_t c_in = 0;
    int i = 1;

    addOperation(extract_first_bit(a), extract_first_bit(b), &result, &c_in);
    a = a >> 1;
    b = b >> 1;
    while (a != 0 || b != 0 || c_in != 0) {
        addOperation(extract_first_bit(a), extract_first_bit(b), &result_bit, &c_in);
        result = result | result_bit << i;
        a = a >> 1;
        b = b >> 1;
        i++;
    }
    return result;
}


uint32_t adder2bit(uint32_t a, uint32_t b) {
    uint32_t a_bit;
    uint32_t b_bit;
    uint32_t s_bit;
    uint32_t s = 0;

    a_bit = extract_first_bit(a);
    b_bit = extract_first_bit(b);
    s_bit = a_bit ^ b_bit;
    s = s | s_bit;

    a = a >> 1;
    b = b >> 1;
    return s;
}
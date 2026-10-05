#ifndef ADDER_HPP
#define ADDER_HPP

#include <iostream>
#include <cstdint>

uint32_t adder(uint32_t a, uint32_t b);
void addOperation(uint32_t a, uint32_t b, uint32_t *result, uint32_t *c_in);
uint32_t extract_first_bit(uint32_t num);


#endif

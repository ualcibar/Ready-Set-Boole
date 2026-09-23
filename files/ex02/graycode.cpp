#include "graycode.hpp"
        
uint32_t gray_code(uint32_t n) {
    return n ^ (n >> 1);
}
#include "adder.hpp"

uint32_t extract_first_bit(uint32_t num)
{
    return num & 1;
}

/*
uint32_t adder(uint32_t a, uint32_t b) {
    uint32_t a_bit;
    uint32_t b_bit;
    uint32_t s_bit;
    uint32_t c_out, c_in, s = 0;
    
    a_bit = extract_first_bit(a);
    b_bit = extract_first_bit(b);    
    c_in = 0;
    
    while (a != 0 || b != 0 || c_out != 0) {
        std::cout << "Estamos dento del bucle!\n";
        a_bit = extract_first_bit(a);
        b_bit = extract_first_bit(b);
        
        s_bit = a_bit ^ b_bit;
        if (c_in != 0) {
            // hay acarreo
            c_out = a_bit & b_bit;
            c_in = c_in | c_out;
        }
        s = s << 1;
        s = s | s_bit;
        a = a >> 1;
        b = b >> 1;
    }
    return s;
}
*/

uint32_t adder(uint32_t a, uint32_t b) {
    uint32_t a_bit;
    uint32_t b_bit;
    uint32_t s_bit;
    uint32_t s = 0;
    uint32_t acarreo_1;
    uint32_t acarreo_2 = 0;
    uint32_t acarreo_anterior;

    a_bit = extract_first_bit(a);
    b_bit = extract_first_bit(b);
    std::cout << "first a =" << a_bit << "\n";
    std::cout << "first b =" << b_bit << "\n";
    std::cout << "s =" << s << "\n";
    s_bit = a_bit ^ b_bit;
    acarreo_1 =  a_bit & b_bit;

    s = s | s_bit;
    a = a >> 1;
    b = b >> 1;
    acarreo_anterior = acarreo_1;
    std::cout << "s_bit =" << s_bit << "\n";
    std::cout << "s =" << s << "\n";
    while (a != 0 || b != 0 || acarreo_anterior != 0) {
        std::cout << "Estamos dentro del bucle!\n";
        std::cout << "a =" << a << "\n";
        std::cout << "b =" << b << "\n";
        
        a_bit = extract_first_bit(a);
        b_bit = extract_first_bit(b);
        acarreo_1 = a_bit ^ b_bit;
        s_bit = a_bit & b_bit;
        
        s_bit = s_bit ^ acarreo_anterior;
        acarreo_2 = acarreo_1 & acarreo_anterior;
        acarreo_anterior = acarreo_2 | acarreo_1;

        
        s = s | s_bit;
        s = s << 1;

        a = a >> 1;
        b = b >> 1;
    }
    return s;
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
#include <iostream>
#include "adder.hpp"

int main()
{
    std::cout << adder(8, 8) << " <-Final Result\n";
    std::cout << adder(8, 1) << " <-Final Result\n";
    std::cout << adder(8, 5) << " <-Final Result\n";
    std::cout << adder(54, 112) << " <-Final Result\n";
    std::cout << adder(8, -3) << " <-Final Result\n";
    std::cout << adder(83, 1) << " <-Final Result\n";
    return 1;
}

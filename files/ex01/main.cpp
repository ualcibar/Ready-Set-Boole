#include "adder.hpp"
#include "multiplier.hpp"

int main()
{
    std::cout << multiplier(8, 8) << " <-Final Result\n";
    std::cout << multiplier(8, 1) << " <-Final Result\n";
    std::cout << multiplier(5, 0) << " <-Final Result\n";
    std::cout << multiplier(54, 112) << " <-Final Result\n";
    std::cout << multiplier(8, -3) << " <-Final Result\n";
    std::cout << multiplier(83, 1) << " <-Final Result\n";
    return 1;
}

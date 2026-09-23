#include <iostream>
#include "adder.hpp"

int main()
{
    struct TestCase { uint32_t a; uint32_t b; uint32_t expected; };
    /*
    TestCase tests[] = {
        {5, 2, 7},
        {7, 1, 8},
        {10, 6, 16},
        {13, 11, 24},
        {31, 1, 32},
        {11, 11, 22},
        {0, 0, 0},
        {0, 5, 5},
    };
    int failed = 0;
    int cont = 0;
    */

    std::cout << adder(8, 8) << " <-Final Result\n";
    std::cout << adder(8, 1) << " <-Final Result\n";
    std::cout << adder(8, 5) << " <-Final Result\n";
    std::cout << adder(54, 112) << " <-Final Result\n";
    std::cout << adder(8, -3) << " <-Final Result\n";
    std::cout << adder(83, 1) << " <-Final Result\n";
    
    /*
    for (const auto& t : tests)
    {
        cont++;
        std::cout << "Estamos en el " << cont << " test!\n";
        uint32_t result = adder(t.a, t.b);
        bool ok = (result == t.expected);
        std::cout << t.a << " + " << t.b << " = " << result
        << " (esperado " << t.expected << ") "
        << (ok ? "OK" : "FALLO") << '\n';
        if (!ok) failed++;
    }
    
    std::cout << '\n' << (failed == 0 ? "Todos los tests pasan." :
    std::to_string(failed) + " test(s) fallaron.") << '\n';
    return failed == 0 ? 0 : 1;
    */
    return 1;
}

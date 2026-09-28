/*#include "RPN.hpp"


int main()
{
    std::cout << RPN_bool("00=") << "\n";
    return 1;
}
*/

#include <iostream>
#include <string>
#include "RPN.hpp"

struct TestCase {
    std::string formula;
    bool        expected;
    std::string note;
};

int main()
{
    TestCase tests[] = {
        // Conjuncion / disyuncion / XOR
        {"10&", false, ""},
        {"11&", true,  ""},
        {"10|", true,  ""},
        {"00|", false, ""},
        {"10^", true,  ""},
        {"11^", false, ""},

        // Material condition (>)
        {"00>", true,  ""},
        {"01>", true,  ""},
        {"10>", false, "unico caso falso de A > B"},
        {"11>", true,  ""},

        // Logical equivalence (=)
        {"00=", true,  ""},
        {"01=", false, ""},
        {"10=", false, ""},
        {"11=", true,  ""},

        // Negacion (unario)
        {"1!", false, ""},
        {"0!", true,  ""},

        // Compuestas
        {"10|1&",   true,  "(1|0)&1"},
        {"101|&",   true,  "1&(0|1)"},
        {"10&!",    true,  "!(1&0)"},
        {"11>0=",   false, "(1>1)=0"},
        {"1011||=", true,  "ejemplo del subject"},
    };

    const std::string RED   = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string RESET = "\033[0m";

    int total  = 0;
    int failed = 0;

    for (const auto& t : tests)
    {
        bool got = RPN_bool(t.formula);
        bool ok  = (got == t.expected);
        total++;

        if (ok)
        {
            std::cout << GREEN << "[OK]    " << RESET
                      << t.formula << " -> " << got << "\n";
        }
        else
        {
            failed++;
            std::cout << RED << "[FALLO] " << RESET
                      << t.formula << " -> obtenido " << got
                      << ", esperado " << t.expected;
            if (!t.note.empty())
                std::cout << "  (" << t.note << ")";
            std::cout << "\n";
        }
    }

    std::cout << "\n" << (total - failed) << "/" << total << " correctos";
    if (failed)
        std::cout << RED << "  (" << failed << " fallos)" << RESET;
    std::cout << "\n";

    return failed == 0 ? 0 : 1;
}
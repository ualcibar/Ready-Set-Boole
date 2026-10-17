#include <iostream>
#include <string>
#include "AST.hpp"

int main ()
{
    std::cout << AST_to_RPN(to_nnf(create_AST("10>!!").get()).get()) << "\n";  // hoy: 10>;       esperado: 1!0|
}
    /*
    // NNF en RPN con hojas 0/1: solo 0 1 & | !, y cada '!' justo detrás de una hoja
    static bool is_nnf_rpn(const std::string &s) {
        if (s.empty())
        return false;
        for (size_t i = 0; i < s.size(); ++i) {
            char c = s[i];
            if (c == '0' || c == '1' || c == '&' || c == '|')
            continue;
        if (c == '!' && i > 0 && (s[i - 1] == '0' || s[i - 1] == '1'))
            continue;
        return false;
    }
    return true;
}

static void check(const std::string &formula, const std::string &expected) {
    std::string got = AST_to_RPN(to_nnf(create_AST(formula).get()).get());
    std::cout.width(10);
    std::cout << std::left << formula << " -> " << (got.empty() ? "(vacio)" : got);
    if (got == expected) {
        std::cout << "   [ OK ]\n";
    } else if (is_nnf_rpn(got) &&
               eval_AST(create_AST(got).get()) == eval_AST(create_AST(formula).get())) {
        std::cout << "   [ OK*] distinta a la esperada (" << expected << ") pero NNF valida\n";
    } else {
        std::cout << "   [FAIL] esperada: " << expected << "\n";
    }
}

int main() {
    // ya es NNF
    check("10|",       "10|");
    // solo negaciones
    check("10&!",      "1!0!|");
    check("10|!",      "1!0!&");
    check("1!!",       "1");
    check("10&!!",     "10&");
    check("1!0|!",     "10!&");
    check("10|1&!",    "1!0!&1!|");
    // > = ^
    check("10>",       "1!0|");
    check("10>!",      "10!&");
    check("10=",       "10&1!0!&|");
    check("10=!",      "10!&1!0&|");
    check("10^",       "10!&1!0&|");
    check("10^!",      "10&1!0!&|");
    // anidadas
    check("10&1|0^!",  "10&1|0&1!0!|1!&0!&|");
    check("10>1=",     "1!0|1&10!&1!&|");
    check("10^1^",     "10!&1!0&|1!&10&1!0!&|1&|");
    check("10|!1&0>",  "10|1!|0|");
}
*/

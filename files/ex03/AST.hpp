#ifndef AST_HPP
#define AST_HPP
 
#include <memory>
#include <string>
 
struct Node
{
    char value;                    // '0', '1', '!', '&', '|', '^', '>', '='
    std::unique_ptr<Node> left;    // nullptr si es hoja o si el operador es unario (!)
    std::unique_ptr<Node> right;   // nullptr si es hoja
 
    Node(char v) : value(v), left(nullptr), right(nullptr) {}
};

#endif
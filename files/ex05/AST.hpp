#ifndef AST_HPP
#define AST_HPP
 
#include <memory>
#include <string>
 
struct Node
{
    char value;              
    std::unique_ptr<Node> left;    
    std::unique_ptr<Node> right;  
 
    Node(char v) : value(v), left(nullptr), right(nullptr) {}
};

void print_AST(const Node *root);
bool eval_AST(const Node* node);
bool AST(std::string stack);

#endif
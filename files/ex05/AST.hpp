#ifndef AST_HPP
#define AST_HPP
 
#include <memory>
#include <string>
#include <vector>
 
struct Node
{
    char value;              
    std::unique_ptr<Node> left;    
    std::unique_ptr<Node> right;  
 
    Node(char v) : value(v), left(nullptr), right(nullptr) {}
};

std::unique_ptr<Node> clone(const Node* node) {
    if (node == nullptr)
        return nullptr;

    auto copia = std::make_unique<Node>(node->value);
    copia->left  = clone(node->left.get());
    copia->right = clone(node->right.get());
    return copia;
}

void print_AST(const Node *tree_root);
bool eval_AST(const Node *tree_root);
std::string NNF(std::string formula);
//std::unique_ptr<Node> eval_AST_NNF(const Node *tree_root);
std::unique_ptr<Node> to_nnf(const Node* node);
std::unique_ptr<Node> create_AST(std::string formula);
std::unique_ptr<Node> create_bin_AST(std::string formula);

#endif
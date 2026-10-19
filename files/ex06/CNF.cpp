#include "CNF.hpp"

std::unique_ptr<Node> to_cnf(const Node* node) {
    std::unique_ptr<Node> new_node;

    if (node != nullptr) {
        if (node->value == OR) {
            if (node->left->value == AND && (is_variable(node->right->value) || node->right->value == NOT)) {
                    new_node = std::make_unique<Node>(AND);
                    new_node->left = std::make_unique<Node>(OR);
                    new_node->right = std::make_unique<Node>(OR);

                    new_node->left->left = clone (node->right.get());
                    new_node->left->right = clone (node->left->left.get());

                    new_node->right->right = clone (node->right.get());
                    new_node->right->left = clone (node->left->right.get());
            } else if (node->right->value == AND && (is_variable(node->left->value) || node->left->value == NOT)) {
                    new_node = std::make_unique<Node>(AND);
                    new_node->left = std::make_unique<Node>(OR);
                    new_node->right = std::make_unique<Node>(OR);

                    new_node->right->left = clone (node->right.get());
                    new_node->right->right = clone (node->left->left.get());

                    new_node->left->right = clone (node->right.get());
                    new_node->left->left = clone (node->left->right.get());
            }
        } 
            
        if (new_node == nullptr)
            new_node = clone (node);
        
        if (new_node->left != nullptr)
            new_node->left = to_cnf(new_node->left.get());
        if (new_node->right != nullptr)
            new_node->right = to_cnf(new_node->right.get());
    } 
    return new_node;
}


std::string conjuction_normal_form(std::string formula) {
    std::unique_ptr<Node> tree = create_AST(formula);
    if (tree == nullptr)
        return ""; 
    
    return AST_to_RPN(to_cnf(to_nnf(tree.get()).get()).get());
}
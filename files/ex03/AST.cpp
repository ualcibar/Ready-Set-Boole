#include "AST.hpp"
#include "RPN.hpp"

void print_AST(const Node *root) {
    const Node* current = root;
    int i = 1;

    while (current->right != nullptr) {
        if ((i == 1)) {
            for (int f = 0; f < (i - 1) * 2; ++f)
                std::cout << " ";
            std::cout << "  " << current->value << "\n";
        }
        for (int f = 0; f < (i - 1) * 2; ++f)
            std::cout << " ";
        std::cout << " /" << " \\ \n";
        for (int f = 0; f < (i - 1) * 2; ++f)
            std::cout << " ";
        if (current->left != nullptr)
            std::cout << current->left->value;
        if (current->right != nullptr) {
            if (isOperator(current->right->value))
                std::cout << " ";
            std::cout << "  " << current->right->value;
        }
        std::cout << "\n";
        current = current->right.get();
        i++;
    }
    return;
}
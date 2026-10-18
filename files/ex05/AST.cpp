#include "AST.hpp"
#include "RPN.hpp"

void print_AST(const Node *tree_root) {
    int i = 1;

    while (tree_root->right != nullptr) {
        if ((i == 1)) {
            for (int f = 0; f < (i - 1) * 2; ++f)
                std::cout << " ";
            std::cout << "  " << tree_root->value << "\n";
        }
        for (int f = 0; f < (i - 1) * 2; ++f)
            std::cout << " ";
        std::cout << " /" << " \\ \n";
        for (int f = 0; f < (i - 1) * 2; ++f)
            std::cout << " ";
        if (tree_root->left != nullptr)
            std::cout << tree_root->left->value;
        if (tree_root->right != nullptr) {
            if (is_operator(tree_root->right->value))
                std::cout << " ";
            std::cout << "  " << tree_root->right->value;
        }
        std::cout << "\n";
        tree_root = tree_root->right.get();
        i++;
    }
}

std::string AST_to_RPN(const Node *node) {
    if (node == nullptr)
        return "";
    return AST_to_RPN(node->left.get()) + AST_to_RPN(node->right.get()) + node->value;
}

bool eval_AST(const Node *tree_root) {
    if (tree_root->value == '1')
        return true;
    if (tree_root->value == '0')
        return false;
    if (tree_root->value == '!')
        return !eval_AST(tree_root->right.get());

    bool left_val  = eval_AST(tree_root->left.get());
    bool right_val = eval_AST(tree_root->right.get());
    return exec_operation(left_val, right_val, tree_root->value);
}

std::unique_ptr<Node> create_bin_AST(std::string formula) {
    std::stack<std::unique_ptr<Node>> operate;

    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE: {
                if (operate.empty() || operate.size() < 2) {
                    std::cout << "invalid formula\n";
                    return nullptr;
                }
                std::unique_ptr<Node> node = std::make_unique<Node>(*it);
                node->right = std::move(operate.top());
                operate.pop();
                node->left = std::move(operate.top()); 
                operate.pop();
                operate.push(std::move(node));
                break;
            }
            case NOT: {
                if (operate.empty()) {
                    std::cout << "invalid formula\n";
                    return nullptr;
                }
                std::unique_ptr<Node> neg = std::make_unique<Node>(NOT);
                neg->right = std::move(operate.top()); 
                operate.pop();
                operate.push(std::move(neg));
                break;
            }
            case '1': 
            case '0': {
                std::unique_ptr<Node> node = std::make_unique<Node>(*it);
                operate.push(std::move(node));
                break;
            }
        }
    }
    return std::move(operate.top());
}

std::unique_ptr<Node> create_AST(std::string formula) {
    std::stack<std::unique_ptr<Node>> operate;

    for (std::string::iterator it = formula.begin(); it != formula.end(); ++it) {
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE: {
                if (operate.empty() || operate.size() < 2) {
                    std::cout << "invalid formula\n";
                    return nullptr;
                }
                std::unique_ptr<Node> node = std::make_unique<Node>(*it);                
                node->right = std::move(operate.top());
                operate.pop();
                node->left = std::move(operate.top()); 
                operate.pop();
                operate.push(std::move(node));
                break;
            }
            case NOT: {
                if (operate.empty()) {
                    std::cout << "invalid formula\n";
                    return nullptr;
                }
                std::unique_ptr<Node> neg = std::make_unique<Node>(NOT);
                neg->right = std::move(operate.top()); 
                operate.pop();
                operate.push(std::move(neg));
                break;
            }
            case '1': 
            case '0': {
                std::unique_ptr<Node> node = std::make_unique<Node>(*it);
                operate.push(std::move(node));
                break;
            }
        }
    }
    return std::move(operate.top());
}

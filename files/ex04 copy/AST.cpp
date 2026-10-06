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
            if (is_operator(current->right->value))
                std::cout << " ";
            std::cout << "  " << current->right->value;
        }
        std::cout << "\n";
        current = current->right.get();
        i++;
    }
}

bool eval_AST(const Node* node) {
    if (node->left == nullptr && node->right == nullptr) {
        if (node->value == '1')
            return true;
        return false;
    }

    if (node->value == NOT) {
        if (node->right->value == '1')
            return false;
        return true;
    }

    bool left_val  = eval_AST(node->left.get());
    bool right_val = eval_AST(node->right.get());
    return exec_operation(left_val, right_val, node->value);
}

bool AST(std::string stack) {
    std::stack<char> operate;
    std::unique_ptr<Node> tree_root = nullptr;
    
    char a;
    char b;
    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        if(!(is_operator(*it) || is_bit(*it))/* || ((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() > 0))*/) {
            
            std::cout << "Invalid formula\n";
            return 0;
        }
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE: {
                    std::unique_ptr<Node> root = std::make_unique<Node>(*it);
                    
                    if (tree_root == nullptr) {
                        b = operate.top();
                        operate.pop();
                        a = operate.top();
                        operate.pop();

                        std::unique_ptr<Node> right_leaf  = std::make_unique<Node>(b);
                        std::unique_ptr<Node> left_leaf = std::make_unique<Node>(a);

                        root->left  = std::move(left_leaf);
                        root->right = std::move(right_leaf);
                        
                        tree_root = std::move(root);
                    } else {
                        a = operate.top();
                        operate.pop();

                        std::unique_ptr<Node> left_leaf = std::make_unique<Node>(a);
                        
                        root->left  = std::move(left_leaf);
                        root->right = std::move(tree_root);   // <- aquí el cambio
                        tree_root   = std::move(root);
                    }
                }
                break;
            case NOT: {
                std::unique_ptr<Node> root = std::make_unique<Node>(*it);
                if (tree_root == nullptr) {
                    a = operate.top();
                    operate.pop();
                    root->right = std::make_unique<Node>(a);
                    tree_root  = std::move(root);
                } else {
                    root->right = std::move(tree_root);
                    tree_root  = std::move(root);
                }
                break;
            }
            case '1':
                operate.push('1'); 
                break;
            case '0':
                operate.push('0'); 
                break;
        }
    }
    return eval_AST(tree_root.get());
}
#include "RPN.hpp"

bool isOperator(char operator_simbol) {
    switch (operator_simbol) {
        case AND:
        case NOT:
        case OR:
        case XOR:
        case MATERIAL_CONDITION:
        case LOGICAL_EQUIVALENCE:
            return true;
        default:
            return false;
    }
}

bool isBit(char bit) {
    switch (bit) {
        case '1':
        case '0':
            return true;
        default:
            return false;
    }
}

bool extract_bit(std::stack <bool> &operate) {
    bool bit = operate.top();
    operate.pop();
    return bit;
}

bool exec_operation(bool bit_a, bool bit_b, char operator_simbol) {
    switch (operator_simbol) {
        case AND:
            return (bit_a & bit_b);
        case OR:
            return (bit_a | bit_b);
        case XOR:
            return (bit_a ^ bit_b);
        case MATERIAL_CONDITION:
            return (!bit_a | bit_b);
        case LOGICAL_EQUIVALENCE:
            return (!(bit_a ^ bit_b));
    }
    return 0;
}

bool RPN_bool(std::string stack) {
    std::stack<bool> operate;
    bool a;
    bool b;

    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        if(!(isOperator(*it) || isBit(*it)) /*|| ((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() > 0))*/) {
            
            std::cout << "Invalid formula\n";
            return 0;
        }
        switch(*it) {
            case AND: 
            case XOR:
            case MATERIAL_CONDITION: 
            case OR: 
            case LOGICAL_EQUIVALENCE:
                b = operate.top();
                operate.pop();
                a = operate.top();
                operate.pop();

                operate.push(exec_operation(a, b, *it));
                break;
            case NOT:
                a = operate.top();
                operate.pop();
                operate.push(!a);
                break;
            case '1':
                operate.push(true); 
                break;
            case '0':
                operate.push(false); 
                break;
        }
    }
    return operate.top();
}

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
            std::cout << "   " << current->right->value;
        }
        std::cout << "\n";
        current = current->right.get();
        i++;
    }
    return;
}

bool AST(std::string stack) {
    std::stack<char> operate;
    std::unique_ptr<Node> tree_root = nullptr;

    char a;
    char b;
    int i = 0;
    for (std::string::iterator it = stack.begin(); it != stack.end(); ++it) {
        if(!(isOperator(*it) || isBit(*it))/* || ((isOperator(*it) && operate.size() < 2) && (*it != NOT && operate.size() > 0))*/) {
            
            std::cout << "Invalid formula\n";
            return 0;
        }
        std::cout << i << "\n";
        i++;
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

    print_AST(tree_root.get());
    //return operate.top();
    return 1;
}
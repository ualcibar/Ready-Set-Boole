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

std::unique_ptr<Node> double_negation(const Node* node) {
    std::unique_ptr<Node> new_node;
    
    if (node->left != nullptr) {
        if (node->left->value == NOT) {
            if (node->left->left != nullptr)
            new_node = clone (node->left->left.get());
            else if (node->left->right != nullptr)
            new_node = clone (node->left->right.get());
        }
    } else if (node->right != nullptr) {
        if (node->right->value == NOT) {
            if (node->right->left != nullptr)
            new_node = clone (node->right->left.get());
            else if (node->right->right != nullptr)
            new_node = clone (node->right->right.get());
        }
    }
    
    return new_node;
}

std::unique_ptr<Node> material_condition(const Node* node) {
    std::unique_ptr<Node> new_node;
    
    new_node = std::make_unique<Node>(OR);
    
    new_node->left = std::make_unique<Node>(NOT);
    new_node->left->right = clone(node->left.get());
    new_node->right = clone(node->right.get());
    
    return new_node;
}

std::unique_ptr<Node> equivalence(const Node* node) {
    std::unique_ptr<Node> new_node;
    
    new_node = std::make_unique<Node>(AND);
    
    new_node->left = std::make_unique<Node>(MATERIAL_CONDITION);
    new_node->left->left = clone (node->left.get());
    new_node->left->right = clone (node->right.get());
    new_node->left = clone(material_condition(new_node->left.get()).get());
    
    new_node->right = std::make_unique<Node>(MATERIAL_CONDITION);
    new_node->right->left = clone (node->right.get());
    new_node->right->right = clone (node->left.get());
    new_node->right = clone(material_condition(new_node->right.get()).get());
    
    return new_node;
}

std::unique_ptr<Node> xor_to_nff(const Node* node) {
    std::unique_ptr<Node> new_node;
    
            new_node = std::make_unique<Node>(OR);
            
            new_node->left = std::make_unique<Node>(AND);
            new_node->left->left = clone(node->left.get());
            new_node->left->right = std::make_unique<Node>(NOT);
            new_node->left->right->right = clone(node->right.get());
            
            new_node->right = std::make_unique<Node>(AND);
            new_node->right->right = clone(node->right.get());
            new_node->right->left = std::make_unique<Node>(NOT);
            new_node->right->left->right = clone(node->left.get());
    return new_node;
}


std::unique_ptr<Node> morgan_law(const Node* node) {
    std::unique_ptr<Node> new_node;

    if (node->value == AND)
        new_node = std::make_unique<Node>(OR);
    else if (node->value == OR)
        new_node = std::make_unique<Node>(AND);

    new_node->left = std::make_unique<Node>(NOT);
    new_node->left->right = clone(node->left.get());
    new_node->right = std::make_unique<Node>(NOT);
    new_node->right->right = clone(node->right.get());
    return new_node;
}

std::unique_ptr<Node> not_to_nff(const Node* node) {
    std::unique_ptr<Node> new_node;

    if (node->value == NOT) {
        // !!X -> X   (X es el hijo del '!' que recibimos)
        const Node* child = (node->left != nullptr) ? node->left.get() : node->right.get();
        new_node = to_nnf(child);
    } else if (is_operator_NNF_valid(node->value)) {
        new_node = morgan_law(node);
    } else if (node->value == MATERIAL_CONDITION) {
        new_node = morgan_law(material_condition(node).get());
    } else if (node->value == LOGICAL_EQUIVALENCE) {
        new_node = morgan_law(equivalence(node).get());
    } else if (node->value == XOR) {
        new_node = morgan_law(xor_to_nff(node).get());
    }
    return new_node;
}


std::unique_ptr<Node> to_nnf(const Node* node) {
    std::unique_ptr<Node> new_node;

    if (node != nullptr) {
        if (node->value == XOR) {
            new_node = xor_to_nff(node);
        } else if (node->value == LOGICAL_EQUIVALENCE) {
            new_node = equivalence(node);
        } else if (node->value == MATERIAL_CONDITION) {
            new_node = material_condition(node);
        } else if (node->value == NOT) {
            if (node->left != nullptr) {
               new_node = not_to_nff (node->left.get());
            } else if (node->right != nullptr) {
                new_node = not_to_nff (node->right.get());
            }
        }
        
        if (new_node == nullptr)
            new_node = clone (node);
        
        if (new_node->left != nullptr)
            new_node->left = to_nnf(new_node->left.get());
        if (new_node->right != nullptr)
            new_node->right = to_nnf(new_node->right.get());
    } 
    return new_node;
}

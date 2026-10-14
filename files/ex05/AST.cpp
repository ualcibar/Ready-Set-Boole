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
    
        if (node->left != nullptr) {

            switch (node->left->value) {
                case AND:
                new_node = std::make_unique<Node>(OR);
                new_node->left = std::make_unique<Node>(NOT);
                new_node->right = std::make_unique<Node>(NOT);
                new_node->left->left = clone(node->left->left.get());
                new_node->right->left = clone(node->left->right.get());
                break;
                
                case OR:
                new_node = std::make_unique<Node>(AND);
                new_node->left = std::make_unique<Node>(NOT);
                new_node->right = std::make_unique<Node>(NOT);
                new_node->left->left = clone(node->left->left.get());
                new_node->right->left = clone(node->left->right.get());
                break;
            }
        }else if (node->right != nullptr) {

            switch (node->right->value) {
                case AND:
                new_node = std::make_unique<Node>(OR);
                new_node->left = std::make_unique<Node>(NOT);
                new_node->right = std::make_unique<Node>(NOT);
                new_node->left->left = clone(node->right->left.get());
                new_node->right->left = clone(node->right->right.get());
                break;
                
                case OR:
                new_node = std::make_unique<Node>(AND);
                new_node->left = std::make_unique<Node>(NOT);
                new_node->right = std::make_unique<Node>(NOT);
                new_node->left->left = clone(node->right->left.get());
                new_node->right->left = clone(node->right->right.get());
                break;
            }
        }
        return new_node;
}

std::unique_ptr<Node> to_nnf(const Node* node) {
    std::unique_ptr<Node> nuevo;

    if (node != nullptr) {
        if (node->value == XOR) {
            nuevo = xor_to_nff(node);
            
        } else if (node->value == LOGICAL_EQUIVALENCE) {
            nuevo = equivalence(node);
            
        } else if (node->value == MATERIAL_CONDITION) {
            nuevo = material_condition(node);
            
        } else if (node->value == NOT) {
            if (node->left != nullptr) {
                if (node->left->value == NOT) {
                    nuevo = std::move(double_negation(node));
                } else if (is_operator_NNF_valid(node->left->value)) {
                    nuevo = std::move(morgan_law(node));
                } else if (node->left->value == MATERIAL_CONDITION) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(material_condition(node->left.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                } else if (node->left->value == LOGICAL_EQUIVALENCE) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(equivalence(node->left.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                } else if (node->left->value == XOR) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(xor_to_nff(node->left.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                }
            } else if (node->right != nullptr) {
                if (node->right->value == NOT) {
                    nuevo = double_negation(node);
                } else if (is_operator_NNF_valid(node->right->value))
                    nuevo = std::move(morgan_law(node));
                else if (node->right->value == MATERIAL_CONDITION) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(material_condition(node->right.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                } else if (node->right->value == LOGICAL_EQUIVALENCE) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(equivalence(node->right.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                } else if (node->right->value == XOR) {
                    std::unique_ptr<Node> tmp_node = std::make_unique<Node>(NOT);
                    tmp_node->right = clone(xor_to_nff(node->left.get()).get());
                    nuevo = std::move(morgan_law(tmp_node.get()));
                }
            }
        }
        if (nuevo == nullptr)
            nuevo = clone (node);
        if (nuevo->left != nullptr)
            nuevo->left = to_nnf(nuevo->left.get());
        if (nuevo->right != nullptr)
            nuevo->right = to_nnf(nuevo->right.get());
    } 
    return nuevo;
}

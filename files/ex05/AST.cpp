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
/*
std::unique_ptr<Node> eval_AST_NNF(Node *tree_root) {
    std::unique_ptr<Node> NNF_tree = nullptr; 
    if (tree_root->value == XOR) {

        NNF_tree = std::move(std::make_unique<Node>(OR));
        NNF_tree->left = std::make_unique<Node>(AND);
        NNF_tree->right = std::make_unique<Node>(AND);
        NNF_tree->left->left = std::move(eval_AST_NNF(tree_root->left.get()));
        NNF_tree->left->right = std::make_unique<Node>(NOT);
        NNF_tree->left->right->left = std::move(eval_AST_NNF(tree_root->left.get()));

    } else if (tree_root->value == LOGICAL_EQUIVALENCE) {

        NNF_tree = std::move(std::make_unique<Node>(NOT));
        NNF_tree->left = std::move(std::make_unique<Node>(XOR));
        NNF_tree->left->left = std::move(tree_root->left);
        NNF_tree->left->right = std::move(tree_root->right);
        NNF_tree= std::move(eval_AST_NNF(NNF_tree.get())); 

    } else if (tree_root->value == MATERIAL_CONDITION) {
        NNF_tree = std::move(std::make_unique<Node>(NOT));

    }

    //return eval_AST_NNF(or_node.get());
    return NNF_tree;
}
*/
std::unique_ptr<Node> to_nnf(const Node* node) {
    std::unique_ptr<Node> nuevo;
    std::unique_ptr<Node> tmp_left;
    std::unique_ptr<Node> tmp_right;
    
    if (node->value == XOR) {
        nuevo = std::make_unique<Node>(OR);
        
        tmp_left = std::make_unique<Node>(AND);
        tmp_left->left = clone(node->left.get());
        tmp_left->right = std::make_unique<Node>(NOT);
        tmp_left->right->right = clone(node->right.get());
        
        tmp_right = std::make_unique<Node>(AND);
        tmp_right->right = clone(node->right.get());
        tmp_right->left = std::make_unique<Node>(NOT);
        tmp_right->left->right = clone(node->left.get());

    } else if (node->value == LOGICAL_EQUIVALENCE) {
        nuevo = std::make_unique<Node>(AND);

        tmp_left = std::make_unique<Node>(OR);
        tmp_left->left = clone(node->left.get());
        tmp_left->right = std::make_unique<Node>(NOT);
        tmp_left->right->right = clone(node->right.get());

        tmp_right = std::make_unique<Node>(OR);
        tmp_right->left = clone(node->right.get());
        tmp_right->left = std::make_unique<Node>(NOT);
        tmp_right->left->right = clone(node->left.get());

    } else if (node->value == MATERIAL_CONDITION) {
        nuevo = std::make_unique<Node>(OR);
        
        tmp_left = std::make_unique<Node>(NOT);
        tmp_left->right = clone(node->left.get());
        tmp_right = clone(node->right.get());

    } else if (node->value == NOT & (node->left != nullptr | node->right != nullptr)) {
        if (node->left->value == NOT) {
            if (node->left->left != nullptr)
        }

        std::cout << "eval !\n";
    }
    if (tmp_left != nullptr)
        nuevo->left = to_nnf(tmp_left.get());
    if (tmp_right != nullptr)
        nuevo->right = to_nnf(tmp_right.get());
    return nuevo;
}


/*
std::string NNF(std::string formula) {
    std::unique_ptr<Node> AST;
    
    AST = std::move(create_AST(formula));
    eval_AST_NNF(AST.get());
}
*/
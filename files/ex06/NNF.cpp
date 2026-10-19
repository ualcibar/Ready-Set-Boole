#include "NNF.hpp"

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

std::string negation_normal_form(std::string formula) {
    std::unique_ptr<Node> tree = create_AST(formula);
    if (tree == nullptr)
        return "";   // fórmula inválida: create_AST ya imprimió el error
    return AST_to_RPN(to_nnf(tree.get()).get());
}

std::unique_ptr<Node> material_condition_equivalent(const Node* node) {
    std::unique_ptr<Node> new_node;
    
    new_node = std::make_unique<Node>(OR);
    
    new_node->left = std::make_unique<Node>(NOT);
    new_node->left->right = clone(node->left.get());
    new_node->right = clone(node->right.get());
    
    return new_node;
}

std::unique_ptr<Node> equivalence_equivalent(const Node* node) {
    std::unique_ptr<Node> new_node;
    
    new_node = std::make_unique<Node>(AND);
    
    new_node->left = std::make_unique<Node>(MATERIAL_CONDITION);
    new_node->left->left = clone (node->left.get());
    new_node->left->right = clone (node->right.get());
    new_node->left = clone(material_condition_equivalent(new_node->left.get()).get());
    
    new_node->right = std::make_unique<Node>(MATERIAL_CONDITION);
    new_node->right->left = clone (node->right.get());
    new_node->right->right = clone (node->left.get());
    new_node->right = clone(material_condition_equivalent(new_node->right.get()).get());
    
    return new_node;
}

std::unique_ptr<Node> xor_equivalent(const Node* node) {
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
        const Node* child = (node->left != nullptr) ? node->left.get() : node->right.get();
        new_node = to_nnf(child);
    } else if (is_operator_NNF_valid(node->value)) {
        new_node = morgan_law(node);
    } else if (node->value == MATERIAL_CONDITION) {
        new_node = morgan_law(material_condition_equivalent(node).get());
    } else if (node->value == LOGICAL_EQUIVALENCE) {
        new_node = morgan_law(equivalence_equivalent(node).get());
    } else if (node->value == XOR) {
        new_node = morgan_law(xor_equivalent(node).get());
    }
    return new_node;
}


std::unique_ptr<Node> to_nnf(const Node* node) {
    std::unique_ptr<Node> new_node;

    if (node != nullptr) {
        if (node->value == XOR) {
            new_node = xor_equivalent(node);
        } else if (node->value == LOGICAL_EQUIVALENCE) {
            new_node = equivalence_equivalent(node);
        } else if (node->value == MATERIAL_CONDITION) {
            new_node = material_condition_equivalent(node);
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

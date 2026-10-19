#ifndef NFF_HPP
#define NFF_HPP
 
#include <memory>
#include <string>
#include <vector>

#include "AST.hpp"
#include "RPN.hpp"
 
std::unique_ptr<Node> double_negation(const Node* node);
std::unique_ptr<Node> material_condition_equivalent(const Node* node);
std::unique_ptr<Node> equivalence_equivalent(const Node* node);
std::unique_ptr<Node> xor_equivalent(const Node* node);
std::unique_ptr<Node> morgan_law(const Node* node);
std::unique_ptr<Node> not_to_nff(const Node* node);
std::unique_ptr<Node> to_nnf(const Node* node);
std::string negation_normal_form(std::string formula);


#endif
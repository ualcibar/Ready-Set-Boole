#ifndef CNF_HPP
#define CNF_HPP
 
#include <memory>
#include <string>
#include <vector>

#include "NNF.hpp"
 
std::string conjuction_normal_form(std::string formula);
std::unique_ptr<Node> to_cnf(const Node* node);

#endif
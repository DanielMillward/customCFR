//
// Created by danielfm on 5/16/22.
//

#include "BaseNode.h"

std::unordered_map<string, double> BaseNode::get_average_strategy() {
    return std::unordered_map<string, double>();
}

std::unordered_map<string, double> BaseNode::get_strategy(double realization_weight) {
    return std::unordered_map<string, double>();
}

bool BaseNode::isThisInfoSet(BaseState gameState) {
    return false;
}


//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_BASENODE_H
#define CUSTOMCFR_BASENODE_H


#include <array>
#include <vector>
#include "BaseState.h"

class BaseNode {
public:
    std::unordered_map<string, double> regret_sum{};
    vector<string> actions;
    virtual std::unordered_map<string, double> get_average_strategy();
    virtual std::unordered_map<string, double> get_strategy(double realization_weight);
    virtual bool isThisInfoSet(BaseState gameState);

    double node_utility;
protected:
    int numActions;
    BaseState currState;
    std::unordered_map<string, double> strategy{};
    std::unordered_map<string, double> strategy_sum{};
};


#endif //CUSTOMCFR_BASENODE_H

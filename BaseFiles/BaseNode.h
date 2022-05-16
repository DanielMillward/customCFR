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

    virtual std::unordered_map<string, double> get_average_strategy() const = 0;
    virtual std::unordered_map<string, double> get_strategy(double realization_weight) = 0;
    virtual std::pair<bool, vector< pair< std::string, float> > > isThisInfoSet(BaseState* gameState) const = 0;
protected:
    vector<string> actions;
    int numActions;
    std::unordered_map<string, double> strategy{};
    std::unordered_map<string, double> strategy_sum{};
};


#endif //CUSTOMCFR_BASENODE_H

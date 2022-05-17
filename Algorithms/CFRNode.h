//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_CFRNODE_H
#define CUSTOMCFR_CFRNODE_H


#include <vector>
#include "../BaseFiles/BaseNode.h"

class CFRNode : public BaseNode{
public:
    CFRNode(BaseState gameState, int numActions, vector<string> actions);
    std::unordered_map<string, double> get_average_strategy() override;
    std::unordered_map<string, double> get_strategy(double realization_weight) override;
    bool isThisInfoSet(BaseState gameState) override;
};


#endif //CUSTOMCFR_CFRNODE_H

//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_CFRNODE_H
#define CUSTOMCFR_CFRNODE_H


#include <vector>
#include "../BaseFiles/BaseNode.h"

class CFRNode : BaseNode{
public:
    CFRNode(int numActions, vector<string> actions);
    std::unordered_map<string, double> get_average_strategy() const override;
    std::unordered_map<string, double> get_strategy(double realization_weight) override;
    std::pair<bool, vector< pair< std::string, float> > > isThisInfoSet(BaseState* gameState) const override;
};


#endif //CUSTOMCFR_CFRNODE_H

//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_CFRALGO_H
#define CUSTOMCFR_CFRALGO_H

#include "../BaseFiles/BaseAlgo.h"

class CFRAlgo : public BaseAlgo{
public:

    CFRAlgo(BaseData gameData, BaseState gameState);

    ~CFRAlgo() override;

    vector<struct BaseNode> train(int numIterations, BaseState rootState) override;

    double doAlgo(vector<double> playerProbOfCurrState, BaseState currGameState);

    BaseNode get_node(BaseState gameState);
};


#endif //CUSTOMCFR_CFRALGO_H

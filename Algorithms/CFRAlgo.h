//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_CFRALGO_H
#define CUSTOMCFR_CFRALGO_H

#include "../BaseFiles/BaseAlgo.h"

class CFRAlgo : BaseAlgo{
public:
    CFRAlgo(BaseData gameData, BaseState* gameState);
    double doAlgo(vector<double> playerProbOfCurrState) override;
    vector<BaseNode> train(int numIterations) override;
};


#endif //CUSTOMCFR_CFRALGO_H

//
// Created by danielfm on 5/16/22.
//

#ifndef CUSTOMCFR_CFRALGO_H
#define CUSTOMCFR_CFRALGO_H

#include "../BaseFiles/BaseAlgo.h"

class CFRAlgo : BaseAlgo{
public:
    CFRAlgo(BaseData gameData, BaseState* gameState);

    BaseNode * get_node(BaseState *const gameState);

    double doAlgo(vector<double> playerProbOfCurrState, BaseState *currGameState);

    ~CFRAlgo() override;

    vector<struct BaseNode *> train(int numIterations, BaseState *rootState);
};


#endif //CUSTOMCFR_CFRALGO_H

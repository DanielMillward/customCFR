//
// Created by danielfm on 5/11/22.
//

#ifndef CUSTOMCFR_BASEALGO_H
#define CUSTOMCFR_BASEALGO_H


#include "BaseState.h"
#include "BaseNode.h"

class BaseAlgo {
public:
    //BaseAlgo(BaseData gameData, BaseState* gameState);
    virtual double doAlgo(vector<double> playerProbOfCurrState) = 0;
    virtual vector<BaseNode> train(int numIterations) = 0;

protected:
    BaseData gameData;
    BaseState* currGameState;
};


#endif //CUSTOMCFR_BASEALGO_H

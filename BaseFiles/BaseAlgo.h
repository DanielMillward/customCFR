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
    virtual double doAlgo(vector<double> playerProbOfCurrState, BaseState currGameState) = 0;
    virtual vector<struct BaseNode> train(int numIterations, BaseState rootState) = 0;
    virtual ~BaseAlgo()
    = default;
protected:
    BaseData gameData;
    BaseState currGameState;
    vector<BaseNode> nodeList;
};


#endif //CUSTOMCFR_BASEALGO_H

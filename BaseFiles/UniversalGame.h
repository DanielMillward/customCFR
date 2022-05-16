//
// Created by danielfm on 5/10/22.
//

#ifndef CUSTOMCFR_UNIVERSALGAME_H
#define CUSTOMCFR_UNIVERSALGAME_H

#include <map>
#include <vector>
#include "BaseState.h"
#include "BaseAlgo.h"
#include "BaseData.h"

/*
 * start
 * defines a terminal state
 * public info of state
 * private info of state
 * how you can transition from one to another
 * legal actions - based on history (so a function that returns action objects? input history, stuff state has)
 * number of players - range?
 * has chance player
 * way to store an action (e.g. b200 for betting 200)
 * Also have action with float next to it (b for bet as well as 200 for number?)
 * need more parameters, e.g. for chance player need both deal action and which player, and what card!
 * 4 things: history of actions, private known info, public known info (have isnull for speed purposes), also
 *  reward function?
 * class of state itself? has array enum of action maybe
 * way to see actions for thing
 * how to integrate probability strategies here
 * also information sets of hidden actions
 * way to see what's going on in an iteration
 *
 *
 */

class UniversalGame {
public:
    //<action, (min, max)> for all actions. If max==0, then it's not a variable action
    //all data as well?
    //<dataType, dataValue> for all player stuff
    UniversalGame(BaseData gameData);

    void train(BaseAlgo& algo);
    //playerStrategies - different chars, e.g. 'r' would be pick randomly, 'p' is go with probabilities, etc.
    //manualControl - if you want to play the bot. Player defaults to player 1 (?)
    BaseState* play(BaseState* gameState, bool manualControl, int manualPlayerNumber, bool visualize);

    BaseData gameData;
private:

    float randomFloat(float min, float max);

    pair<string, float> parseInput(string basicString, vector<pair<std::string, pair<float, float>>> vector);

    void visualizeAction(int player, const string& basicString, float value, const vector<pair<string, float>>& vector1);

    BaseState* takeRandomAction(BaseState* gameState, bool visualize);

    BaseState* takeManualAction(BaseState* gameState, bool visualize);

    BaseState* takeAutomaticAction(BaseState* gameState, bool visualize);

    vector<BaseNode*> allInfoSets{};


    void train(BaseState *rootState, BaseAlgo &algo, int numIterations);
};


#endif //CUSTOMCFR_UNIVERSALGAME_H

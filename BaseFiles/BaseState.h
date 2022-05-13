//
// Created by danielfm on 5/11/22.
//

#ifndef CUSTOMCFR_BASESTATE_H
#define CUSTOMCFR_BASESTATE_H


#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "BaseData.h"
#include "BaseState.h"

using namespace std;

class BaseState {
    //need list of strings, with bool values for whether they have values next to them? or min/max.
    //if max is 0, assumed to be a non-float action.
public:

    vector<pair<string, float>> history; // sequential list of what happened

    // Every player data, indexed by the vector.
    //each being a map of <dataType, value>
     vector<multimap<string, float>> privatePlayersData;
    vector<multimap<string, float>> publicPlayersData;
    //<private, public> board data
    vector<pair<string, string>> boardData;


    //IMPLEMENT THESE!!!
    //BaseState(int numPlayers, vector<pair<string, string>> boardData, vector<multimap<string, float>> publicPlayersData, vector<multimap<string, float>> privatePlayersData, vector<pair<string, float>> history, bool isRoot, vector<pair<string, pair<float, float>>> allActions, multimap<string, pair<float, float>> allPrivatePlayerData, multimap<string, pair<float, float>> allPublicPlayerData);
    virtual BaseState* takeAction(string action, float value);

    virtual std::vector<int> getPayoffs();

    virtual vector<pair<std::string, float>> getInfoSet(int player) = 0;
    virtual bool isTerminal();
    virtual int getCurrPlayer() = 0;
    virtual vector<pair<string, pair<float, float>>> getLegalActions();
    virtual void visualizeState();
    // END IMPLEMENT

protected:
    int currPlayer{}; //whose turn is it?
    bool isRoot{};
    int numPlayers{};
    vector<pair<string, pair<float, float>>> allPlayerActions;
    vector<pair<string, pair<float, float>>> allChanceActions;
    multimap<string, pair<float, float>> allPrivatePlayerData;
    multimap<string, pair<float, float>> allPublicPlayerData;
    vector<pair<string, float>> infoSet;
};


#endif //CUSTOMCFR_BASESTATE_H

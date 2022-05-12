//
// Created by danielfm on 5/11/22.
//

#ifndef CUSTOMCFR_BASESTATE_H
#define CUSTOMCFR_BASESTATE_H


#include <string>
#include <vector>
#include <map>
#include <unordered_map>

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
    pair<string, string> boardData;


    BaseState(bool isRoot);
    BaseState takeAction(string action, float value);
    std::vector<int> getPayoffs();
    std::string getInfoSet(int player);
    bool isTerminal();
    int getCurrPlayer();
    vector<pair<string, pair<float, float>>> getLegalActions();

private:
    int currPlayer; //whose turn is it?
    vector<pair<string, pair<float, float>>> allActions;
    multimap<string, pair<float, float>> allPrivatePlayerData;
    multimap<string, pair<float, float>> allPublicPlayerData;
};


#endif //CUSTOMCFR_BASESTATE_H

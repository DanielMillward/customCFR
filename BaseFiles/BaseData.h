//
// Created by danielfm on 5/12/22.
//

#ifndef CUSTOMCFR_BASEDATA_H
#define CUSTOMCFR_BASEDATA_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;
class BaseData {
public:
    vector<pair<string, pair<float, float>>> allPlayerActions;
    vector<pair<string, pair<float, float>>> allChanceActions;
    multimap<string, pair<float, float>> allPrivatePlayerData;
    multimap<string, pair<float, float>> allPublicPlayerData;
    //string is representation of infoset, map is the probabilities for each action of that infoset
    vector<unordered_map<string, map<string, float>>> playerProbabilities;

    vector<char> playerStrategies;
    int numPlayers;
    bool isConstructed;


    virtual void instantiateObject();
};


#endif //CUSTOMCFR_BASEDATA_H

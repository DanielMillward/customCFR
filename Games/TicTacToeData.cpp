//
// Created by danielfm on 5/12/22.
//

#include "TicTacToeData.h"

/*
 * Implement this data:
 * unordered_map<string, pair<float, float>> allPlayerActions;
    unordered_map<string, pair<float, float>> allChanceActions;
    unordered_map<string, pair<float, float>> allPrivatePlayerData;
    unordered_map<string, pair<float, float>> allPublicPlayerData;
    //string is representation of infoset, map is the probabilities for each action of that infoset
    vector<unordered_map<string, map<string, float>>> playerProbabilities;

    vector<char> playerStrategies;
    int numPlayers;
    bool isConstructed;
 *
 */
void TicTacToeData::instantiateObject() {
    BaseData::instantiateObject();
    //Instantiate player actions
    allPlayerActions.emplace_back("tl", std::make_pair(0,0));
    allPlayerActions.emplace_back(std::make_pair("tm", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("tr", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("ml", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("mm", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("mr", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("bl", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("bm", std::make_pair(0,0)));
    allPlayerActions.emplace_back(std::make_pair("br", std::make_pair(0,0)));

    playerStrategies.push_back('m'); // manual player
    playerStrategies.push_back('r'); // random player

    numPlayers = 2;
    isConstructed = true;


}

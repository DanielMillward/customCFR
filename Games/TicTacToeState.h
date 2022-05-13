//
// Created by danielfm on 5/12/22.
//

#ifndef CUSTOMCFR_TICTACTOESTATE_H
#define CUSTOMCFR_TICTACTOESTATE_H


#include "../BaseFiles/BaseState.h"
#include "../BaseFiles/BaseData.h"

using namespace std;
class TicTacToeState : public BaseState {

    TicTacToeState * takeAction(string action, float value);
    std::vector<int> getPayoffs();
    vector<pair<std::string, float>> getInfoSet(int player);
    bool isTerminal();
    int getCurrPlayer() override;
    vector<pair<std::string, pair<float, float>>> getLegalActions();
    void visualizeState();

public:
    TicTacToeState(vector<pair<string, float>> history, vector<multimap<string, float>> privatePlayersData,
                   vector<multimap<string, float>> publicPlayersData, vector<pair<string, string>> boardData,
                   BaseData baseData, bool isRoot);

private:
    int didSomeoneWin();
};


#endif //CUSTOMCFR_TICTACTOESTATE_H

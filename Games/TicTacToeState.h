//
// Created by danielfm on 5/12/22.
//

#ifndef CUSTOMCFR_TICTACTOESTATE_H
#define CUSTOMCFR_TICTACTOESTATE_H


#include "../BaseFiles/BaseState.h"
#include "../BaseFiles/BaseData.h"

using namespace std;
class TicTacToeState : public BaseState {

    TicTacToeState * takeAction(string action, float value) override;
    std::vector<int> getPayoffs() override;
    vector<pair<std::string, float>> getInfoSet(int player) override;
    bool isTerminal() override;
    int getCurrPlayer() override;
    vector<pair<std::string, pair<float, float>>> getLegalActions() override;
    void visualizeState() override;

public:
    TicTacToeState(vector<pair<string, float>> history, vector<multimap<string, float>> privatePlayersData,
                   vector<multimap<string, float>> publicPlayersData, vector<pair<string, string>> boardData,
                   BaseData baseData, bool isRoot);

private:
    int didSomeoneWin();
};


#endif //CUSTOMCFR_TICTACTOESTATE_H

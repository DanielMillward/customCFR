#include <iostream>
#include "BaseFiles/UniversalGame.h"
#include "Games/TicTacToeData.h"
#include "Games/TicTacToeState.h"
int main() {
    TicTacToeData toeData = TicTacToeData();
    toeData.instantiateObject();
    vector<pair<string, float>> history;
    vector<multimap<string, float>> privatePlayersData;
    vector<multimap<string, float>> publicPlayersData;
    vector<pair<string, string>> boardData;
    auto *toeState = new TicTacToeState(history, privatePlayersData,
            publicPlayersData, boardData,toeData, true);
    UniversalGame myGame = UniversalGame(toeData);
    BaseState* endGame = myGame.play(toeState, true, false, true);
    delete toeState;
    delete endGame;

    return 0;
}

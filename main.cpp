#include <iostream>
#include "BaseFiles/UniversalGame.h"
#include "Games/TicTacToeData.h"
#include "Games/TicTacToeState.h"
int main() {
    //Instantiate objects
    TicTacToeData toeData = TicTacToeData();
    toeData.instantiateObject();
    vector<pair<string, float>> history;
    vector<multimap<string, float>> privatePlayersData;
    vector<multimap<string, float>> publicPlayersData;
    vector<pair<string, string>> boardData;
    //Instantiate the TicTacToe state with data and stuff
    auto *toeState = new TicTacToeState(history, privatePlayersData,
            publicPlayersData, boardData,toeData, true);
    //Make the game
    UniversalGame myGame = UniversalGame(toeData);
    //Play the game

    BaseState* endGame = myGame.play(toeState, true, 1, true);
    delete toeState;
    delete endGame;

    return 0;
}

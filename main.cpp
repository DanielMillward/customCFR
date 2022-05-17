#include <iostream>
#include "BaseFiles/UniversalGame.h"
#include "Games/TicTacToeData.h"
#include "Games/TicTacToeState.h"
#include "Algorithms/CFRAlgo.h"

int main() {
    //Instantiate objects
    TicTacToeData toeData = TicTacToeData();
    toeData.instantiateObject();
    vector<pair<string, float>> history;
    vector<multimap<string, float>> privatePlayersData;
    vector<multimap<string, float>> publicPlayersData;
    vector<pair<string, string>> boardData;
    //Instantiate the TicTacToe state with data and stuff
    TicTacToeState toeState = TicTacToeState(history, privatePlayersData,
            publicPlayersData, boardData,toeData, true);
    auto *algoState = new TicTacToeState(history, privatePlayersData,
                                          publicPlayersData, boardData,toeData, true);
    BaseState trainState = TicTacToeState(history, privatePlayersData,
                                                   publicPlayersData, boardData, toeData, true);
    //Make the game
    UniversalGame myGame = UniversalGame(toeData);
    //Play the game
    CFRAlgo cfrAlgo = CFRAlgo(toeData, *algoState);
    myGame.train(trainState, cfrAlgo, 2);
    BaseState endGame = myGame.play(toeState, true, 1, true);
    return 0;
}

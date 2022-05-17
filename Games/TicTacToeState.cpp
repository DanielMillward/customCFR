//
// Created by danielfm on 5/12/22.
//

#include <iostream>
#include "TicTacToeState.h"


TicTacToeState::TicTacToeState(vector<pair<string, float>> history, vector<multimap<string, float>> privatePlayersData,
                               vector<multimap<string, float>> publicPlayersData, vector<pair<string, string>> boardData,
                               BaseData baseData, bool isRoot) : BaseState() {
    this->numPlayers = baseData.numPlayers;
    this->boardData = boardData;
    this->publicPlayersData = publicPlayersData;
    this->privatePlayersData = privatePlayersData;
    this->isRoot = isRoot;
    this->allPlayerActions = baseData.allPlayerActions;
    this->allPrivatePlayerData = baseData.allPrivatePlayerData;
    this->allPublicPlayerData = baseData.allPublicPlayerData;
    this->history = history;
}

BaseState TicTacToeState::takeAction(string action, float value) {
    //update history
    history.push_back(make_pair(action, value));
    //update board data
    boardData.push_back(make_pair(action, std::to_string(value)));
    currPlayer = (currPlayer + 1) % 2 + 1;
    return *this;
}

std::vector<int> TicTacToeState::getPayoffs() {
    vector<int> output = vector<int>();
    if (isTerminal()) {
        int winner = didSomeoneWin();
        if (winner == -1) {
            //no one won
            for (int i = 0; i < numPlayers; ++i) {
                output.push_back(0);
            }
            return output;
        } else {
            //someone won, give them 1 and the other 0
            for (int i = 0; i < numPlayers; ++i) {
                if (i == winner - 1) {
                    output.push_back(1);
                } else {
                    output.push_back(-1);
                }
            }
        }
    } else {
        return {};
    }
    return output;
}

vector<pair<std::string, float>> TicTacToeState::getInfoSet(int player) {
    return history;
}

bool TicTacToeState::isTerminal() {
    if (history.size() >= 9 || didSomeoneWin() > 0) {
        return true;
    }
    return false;
}

int TicTacToeState::getCurrPlayer() {
    int size = history.size();
    return history.size() % 2 + 1;
}

vector<pair<std::string, pair<float, float>>> TicTacToeState::getLegalActions() {
    vector<pair<std::string, pair<float, float>>> output;

    for (int i = 0; i < allPlayerActions.size(); ++i) {
        //check if the action in allActions is already in history (if someone already played it). If not, add.
        bool alreadyIn = false;
        for (int j = 0; j < history.size(); ++j) {
            if (allPlayerActions.at(i).first == history.at(j).first) {
                alreadyIn = true;
            }
        }
        if (!alreadyIn) {
            output.push_back(allPlayerActions.at(i));
        }
    }
    return output;
}

void TicTacToeState::visualizeState() {
    vector<string> boardState;
    currPlayer = getCurrPlayer();
    for (int i = 0; i < 9; ++i) {
        boardState.push_back(".");
    }
    for (int i = 0; i < history.size(); ++i) {
        //note: the current player we're checking is for a state AFTER the action was taken!
        if (history.at(i).first == "tl") {
            boardState.at(0) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "tm") {
            boardState.at(1) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "tr") {
            boardState.at(2) = (i % 2 + 1 == 2)?  "O" : "X";
        }
        if (history.at(i).first == "ml") {
            boardState.at(3) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "mm") {
            boardState.at(4) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "mr") {
            boardState.at(5) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "bl") {
            boardState.at(6) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "bm") {
            boardState.at(7) = (i % 2 + 1 == 2)? "O" : "X";
        }
        if (history.at(i).first == "br") {
            boardState.at(8) = (i % 2 + 1 == 2)? "O" : "X";
        }
    }
    //print it out
    std::cout << boardState.at(0) << " " << boardState.at(1) << " " << boardState.at(2) << std::endl;
    std::cout << boardState.at(3) << " " << boardState.at(4) << " " << boardState.at(5) << std::endl;
    std::cout << boardState.at(6) << " " << boardState.at(7) << " " << boardState.at(8) << std::endl;
}

int TicTacToeState::didSomeoneWin() {
    int winner;
    int board[3][3] = {{-1}};
    //convert to 2d array form
    for (int i = 0; i < history.size(); ++i) {
        int player = i % 2 + 1;
        if (history.at(i).first == "tl") {
            board[0][0] = player;
        }
        else if (history.at(i).first == "tm") {
            board[0][1] = player;
        }
        else if (history.at(i).first == "tr") {
            board[0][2] = player;
        }
        else if (history.at(i).first == "ml") {
            board[1][0] = player;
        }
        else if (history.at(i).first == "mm") {
            board[1][1] = player;
        }
        else if (history.at(i).first == "mr") {
            board[1][2] = player;
        }
        else if (history.at(i).first == "bl") {
            board[2][0] = player;
        }
        else if (history.at(i).first == "bm") {
            board[2][1] = player;
        }
        else if (history.at(i).first == "br") {
            board[2][2] = player;
        }
    }
    // any of the rows is same
    for (int i=0; i<=2; i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!=0)
        {
            winner = board[i][0];
            return winner;
        }
    }

    // any of the columns is same
    for(int i=0; i<=2; i++)
    {
        if (board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!=0)
        {
            winner = board[0][i];
            return winner;
        }
    }

    // 1st diagonal is same
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!=0)
    {
        winner = board[0][0];
        return winner;
    }

    // 2nd diagonal is same
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board [0][2]!=0)
    {
        winner = board[0][2];
        return winner;
    }

    // if we reached here nobody has won yet

    // if any empty box on board then play on
    for(int i=0; i<=2; i++)
    {
        for(int j=0; j<=2; j++)
        {
            if(board[i][j]==0)
            {
                winner = 0;
                return winner;
            }
        }
    }

    winner = -1; // all boxes full and nobody won so A tie has occurred
    return winner;
}









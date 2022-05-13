//
// Created by danielfm on 5/10/22.
//

#include <iostream>
#include "UniversalGame.h"
#include "BaseState.h"

//YOU NEED TO DELETE GAMESTATE AFTER PLAY!!!!!!
BaseState* UniversalGame::play(BaseState* gameState, const bool manualControl1, const bool manualControl2, const bool visualize) {
    //returns the final base state of the game
    if (!gameData.isConstructed) {
        throw std::invalid_argument("Object not instantiated, probably didn't add your data");
    }
    //make the start root state
    //main game loop
    while (!gameState->isTerminal()) {
        int currPlayer = gameState->getCurrPlayer();
        if (currPlayer == -1) {
            //chance, sample random action
            vector<pair<string, pair<float, float>>> chanceActions = gameState->getLegalActions();
            int randAction = rand() % chanceActions.size();
            float randActionValue = 0;
            if (chanceActions.at(randAction).second.second != 0) {
                //Since the max of range is not 0, we know that it's a value-needed action.
                randActionValue = randomFloat(chanceActions.at(randAction).second.first,chanceActions.at(randAction).second.second);
            }
            //visualize the chance action
            if (visualize) {
                visualizeAction(currPlayer, chanceActions.at(randAction).first, randActionValue, gameState->history);
                gameState->visualizeState();
            }
            gameState = gameState->takeAction(chanceActions.at(randAction).first, randActionValue);
        }
        else if (currPlayer == 1 && manualControl1) {
            //player wants to do his thing
            std::cout << "List of legal actions:" << std::endl;
            for (int i = 0; i < gameState->getLegalActions().size(); ++i) {
                std::cout << gameState->getLegalActions().at(i).first;
                if (gameState->getLegalActions().at(i).second.second == 0) {
                    std::cout << ", ";
                } else {
                   std::cout << " (" << gameState->getLegalActions().at(i).second.first << "," << gameState->getLegalActions().at(i).second.second << "), ";
                }
            }
            std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
            string input;
            cin >> input;
            pair<string, float> userAction = parseInput(input, gameState->getLegalActions());
            //Got invalid input, retrying.
            while (userAction.first == "XXXX") {
                std::cout << "illegal action. Please try again." << std::endl;
                std::cout << "List of legal actions:" << std::endl;
                for (int i = 0; i < gameState->getLegalActions().size(); ++i) {
                    std::cout << gameState->getLegalActions().at(i).first;
                    if (gameState->getLegalActions().at(i).second.second == 0) {
                        std::cout << ", ";
                    } else {
                        std::cout << " (" << gameState->getLegalActions().at(i).second.first << "," << gameState->getLegalActions().at(i).second.second << "), ";
                    }
                }
                std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
                cin >> input;
                userAction = parseInput(input, vector<pair<std::string, pair<float, float>>>());
            }
            //Known that a legal action was taken (b/c parseInput)
            //got a valid input, take action and visualize
            gameState = gameState->takeAction(userAction.first, userAction.second);
            if (visualize) {
                visualizeAction(currPlayer, userAction.first,userAction.second, gameState->history);
                gameState->visualizeState();
            }
            //take player action

        }
        else if (currPlayer == 2 && manualControl2) {
            //player wants to do his thing
            std::cout << "List of legal actions:" << std::endl;
            for (int i = 0; i < gameState->getLegalActions().size(); ++i) {
                std::cout << gameState->getLegalActions().at(i).first << " (" <<
                          gameState->getLegalActions().at(i).second.first << "," << gameState->getLegalActions().at(i).second.second << " ";
            }
            std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
            string input;
            cin >> input;
            pair<string, float> userAction = parseInput(input, gameState->getLegalActions());
            //Got invalid input, retrying.
            while (userAction.first == "XXXX") {
                std::cout << "illegal action. Please try again." << std::endl;
                std::cout << "List of legal actions:" << std::endl;
                for (int i = 0; i < gameState->getLegalActions().size(); ++i) {
                    std::cout << gameState->getLegalActions().at(i).first << " (" <<
                              gameState->getLegalActions().at(i).second.first << "," << gameState->getLegalActions().at(i).second.second << " ";
                }
                std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
                cin >> input;
                userAction = parseInput(input, vector<pair<std::string, pair<float, float>>>());
            }
            //Known that a legal action was taken (b/c parseInput)
            //take player action
            gameState = gameState->takeAction(userAction.first, userAction.second);
            //got a valid input
            if (visualize) {
                visualizeAction(currPlayer, userAction.first,userAction.second, gameState->history);
                gameState->visualizeState();
            }

        }
        else {
            //it's a regular player move, whose strategy is to be selected from the char vector
            char playerAction = gameData.playerStrategies.at(currPlayer-1);
            switch (playerAction) {
                case 'r': {
                    vector<pair<string, pair<float, float>>> chanceActions = gameState->getLegalActions();
                    int randAction = rand() % chanceActions.size();
                    float randActionValue = 0;
                    if (chanceActions.at(randAction).second.second != 0) {
                        //Since the max of range is not 0, we know that it's a value-needed action.
                        randActionValue = randomFloat(chanceActions.at(randAction).second.first,chanceActions.at(randAction).second.second);
                    }
                    //Known that a legal action was taken
                    gameState = gameState->takeAction(chanceActions.at(randAction).first, randActionValue);
                    //visualize the chance action
                    if (visualize) {
                        visualizeAction(currPlayer, chanceActions.at(randAction).first, randActionValue, gameState->history);
                        gameState->visualizeState();
                    }

                    break;
                }
                case 'p':
                    std::cout << "probability" << std::endl;
                    break;
                default:
                    break;
            }
        }
    }
    //game finished
    std::cout << "game finished!" << std::endl;
    vector<int> payoffs = gameState->getPayoffs();
    bool foundWinner = false;
    for (int i = 0; i < payoffs.size(); ++i) {
        if (payoffs.at(i) == 1) {
            std::cout << "Player " << to_string(i+1) << " won!" << std::endl;
            foundWinner = true;
        }
    }
    if (!foundWinner) {
        std::cout << "Tie!" << std::endl;
    }

    gameState->visualizeState();
    return gameState;
}

void UniversalGame::train(BaseAlgo algo) {

}

UniversalGame::UniversalGame(BaseData gameData) {
//need to instantiate all the stuff
    this->gameData = gameData;
    srand (time(NULL));
    this->gameData.isConstructed = true;
}

float UniversalGame::randomFloat(float min, float max) {
    return  (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min ;
}

pair<string, float> UniversalGame::parseInput(string input, vector<pair<std::string, pair<float, float>>> legalActions) {
    //parses user input, makes sure it's legal
    std::string::size_type pos = input.find(':');
    //need to check if its just a no value action
    if (pos != std::string::npos)
    {
        string action =  input.substr(0, pos);
        string valueString = input.substr(pos+1);
        auto value = (float) std::stod(valueString);
        //check if it's a legal Action
        bool isLegal = false;
        for (auto & legalAction : legalActions) {
            if (legalAction.first == action) {
                if (legalAction.second.first <= value <= legalAction.second.second) {
                    isLegal = true;
                }
            }
        }
        if (isLegal) {
            return pair<string, float>(action, value);
        } else {
            return pair<string, float>("XXXX", 0);
        }
    }
    else
    {
        const string& action =  input;
        //check if it's a legal Action
        bool isLegal = false;
        for (auto & legalAction : legalActions) {
            if (legalAction.first == action) {
                if (legalAction.second.second == 0) {
                    isLegal = true;
                }
            }
        }
        if (isLegal) {
            return pair<string, float>(action, 0);
        } else {
            return pair<string, float>("XXXX", 0);
        }
    }
}

void UniversalGame::visualizeAction(int player, const string& action, float value, const vector<pair<string, float>>& history) {
    if (player == -1) {
        std::cout << "Action " << history.size() << " - player CHANCE" << std::endl;
    } else {
        std::cout << "Action " << history.size() << " - player " << player  << std::endl;
    }
    std::cout << "Action taken: " << action << " with value " << value << std::endl;
}







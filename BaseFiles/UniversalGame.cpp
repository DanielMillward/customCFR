//
// Created by danielfm on 5/10/22.
//

#include <iostream>
#include "UniversalGame.h"
#include "BaseState.h"

//YOU NEED TO DELETE GAMESTATE AFTER PLAY!!!!!!
BaseState UniversalGame::play(BaseState gameState, bool manualControl, int manualPlayerNumber, const bool visualize) {
    //returns the final base state of the game
    if (!gameData.isConstructed) {
        throw std::invalid_argument("Object not instantiated, probably didn't add your data");
    }
    //main game loop
    while (!gameState.isTerminal()) {
        //find currPlayer
        int currPlayer = gameState.getCurrPlayer();
        if (currPlayer == -1) {
            //chance, sample random action
            gameState = takeRandomAction(gameState, visualize);
        }
        else if (manualControl && manualPlayerNumber == currPlayer) {
            //player wants to do his thing
            gameState = takeManualAction(gameState, visualize);
        }
        else {
            //it's a regular player move, whose strategy is to be selected from the char vector
            gameState = takeAutomaticAction(gameState, visualize);
        }
    }
    //game finished
    std::cout << "game finished!" << std::endl;
    vector<int> payoffs = gameState.getPayoffs();
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

    gameState.visualizeState();
    return gameState;
}

void UniversalGame::train(BaseState rootState, BaseAlgo& algo, int numIterations) {
    //Train it, return a big vector of states with their strategies
    allInfoSets = algo.train(numIterations, rootState);
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

BaseState UniversalGame::takeRandomAction(BaseState gameState, bool visualize) {
    vector<pair<string, pair<float, float>>> chanceActions = gameState.getLegalActions();
    int randAction = rand() % chanceActions.size();
    float randActionValue = 0;
    if (chanceActions.at(randAction).second.second != 0) {
        //Since the max of range is not 0, we know that it's a value-needed action.
        randActionValue = randomFloat(chanceActions.at(randAction).second.first,chanceActions.at(randAction).second.second);
    }
    //visualize the chance action
    if (visualize) {
        visualizeAction(gameState.getCurrPlayer(), chanceActions.at(randAction).first, randActionValue, gameState.history);
        gameState.visualizeState();
    }
    return gameState.takeAction(chanceActions.at(randAction).first, randActionValue);
}

BaseState UniversalGame::takeManualAction(BaseState gameState, bool visualize) {
    //Get user input
    std::cout << "List of legal actions:" << std::endl;
    for (int i = 0; i < gameState.getLegalActions().size(); ++i) {
        std::cout << gameState.getLegalActions().at(i).first;
        if (gameState.getLegalActions().at(i).second.second == 0) {
            std::cout << ", ";
        } else {
            std::cout << " (" << gameState.getLegalActions().at(i).second.first << "," << gameState.getLegalActions().at(i).second.second << "), ";
        }
    }
    std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
    string input;
    cin >> input;
    pair<string, float> userAction = parseInput(input, gameState.getLegalActions());
    //Got invalid input, retrying.
    while (userAction.first == "XXXX") {
        std::cout << "illegal action. Please try again." << std::endl;
        std::cout << "List of legal actions:" << std::endl;
        for (int i = 0; i < gameState.getLegalActions().size(); ++i) {
            std::cout << gameState.getLegalActions().at(i).first;
            if (gameState.getLegalActions().at(i).second.second == 0) {
                std::cout << ", ";
            } else {
                std::cout << " (" << gameState.getLegalActions().at(i).second.first << "," << gameState.getLegalActions().at(i).second.second << "), ";
            }
        }
        std::cout << "Please enter action in the form of actionName:actionValue, or just actionName if no value needed" << std::endl;
        string newInput;
        cin >> newInput;
        userAction = parseInput(newInput, gameState.getLegalActions());
    }
    //Known that a legal action was taken (b/c parseInput)
    //got a valid input, take action and visualize
    BaseState output = gameState.takeAction(userAction.first, userAction.second);
    if (visualize) {
        visualizeAction(output.getCurrPlayer(), userAction.first,userAction.second, output.history);
        gameState.visualizeState();
    }
    return output;
}

BaseState UniversalGame::takeAutomaticAction(BaseState gameState, bool visualize) {
    char playerAction = gameData.playerStrategies.at(gameState.getCurrPlayer()-1);
    switch (playerAction) {
        case 'r': {
            //Player strategy is random
            vector<pair<string, pair<float, float>>> chanceActions = gameState.getLegalActions();
            int randAction = rand() % chanceActions.size();
            float randActionValue = 0;
            if (chanceActions.at(randAction).second.second != 0) {
                //Since the max of range is not 0, we know that it's a value-needed action.
                randActionValue = randomFloat(chanceActions.at(randAction).second.first,chanceActions.at(randAction).second.second);
            }
            //Known that a legal action was taken
            gameState = gameState.takeAction(chanceActions.at(randAction).first, randActionValue);
            //visualize the chance action
            if (visualize) {
                visualizeAction(gameState.getCurrPlayer(), chanceActions.at(randAction).first, randActionValue, gameState.history);
                gameState.visualizeState();
            }
            break;
        }
        case 'p':
            std::cout << "probability" << std::endl;
            //iterate through vector of nodes. If .isThisInfoSet(gameState) is true, then use that strats
            for (BaseNode infoSet: allInfoSets) {
                bool infoResult = infoSet.isThisInfoSet(gameState);
                if (infoResult) {
                    //The current game state matches this info set, so now we just take the action
                    //Pick a random float from 0 to 1, then keep adding the probabilities until we pass it, then
                    //return last action given.
                    //NEED TO FIND WAY TO DO ACTIONS AS WELL!!!!
                    float randFloat = randomFloat(0,1);
                    float totalProbabilities = 0;
                    int actionCounter = 0;
                    //convert the map to vector
                    std::vector<std::pair<string, double>> actionVector;
                    auto myMap = infoSet.get_average_strategy();
                    for (const auto & it : myMap) {
                        actionVector.emplace_back(it);
                    }
                    //find the thing to make
                    while (totalProbabilities < randFloat) {
                        totalProbabilities += actionVector.at(actionCounter).second;
                        actionCounter++;
                    }
                    gameState = gameState.takeAction(actionVector.at(actionCounter-1).first, 0);
                    //visualize the chance action
                    if (visualize) {
                        visualizeAction(gameState.getCurrPlayer(), actionVector.at(actionCounter-1).first, 0, gameState.history);
                        gameState.visualizeState();
                    }

                }
            }
            break;
        default:
            break;
    }
    return gameState;
}







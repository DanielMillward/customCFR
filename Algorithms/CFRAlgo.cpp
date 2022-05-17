//
// Created by danielfm on 5/16/22.
//

#include "CFRAlgo.h"

#include <utility>
#include <iostream>
#include "CFRNode.h"
#include "../Games/TicTacToeData.h"
#include "../Games/TicTacToeState.h"

CFRAlgo::CFRAlgo(BaseData gameData, BaseState gameState) {
    this->gameData = std::move(gameData);
    this->currGameState = gameState;
}

double CFRAlgo::doAlgo(vector<double> playerProbOfCurrState, BaseState currGameState) {
    int player = currGameState.getCurrPlayer();


    //get the node corresponding to this info state
    auto node = get_node(currGameState);

    // return payoff for terminal states (for current player)
    if (currGameState.isTerminal()) {
        std::cout << "reached a terminal state" << std::endl;
        return currGameState.getPayoffs().at(player-1);
        std::cout << "never reach here" << std::endl;
    }

    // for each action, recursively call cfr with additional history and probability
    std::unordered_map<string, double> playerStrat = node.get_strategy(
            player == 1 ? playerProbOfCurrState.at(0) : playerProbOfCurrState.at(1));
    std::unordered_map<string, double> utilities{};
    double currNodeUtility = 0;

    //problem might be staying in the endgame after we're done...

    for (string action : node.actions) {
        std::cout << "currGameState history is this long: " << currGameState.history.size() << std::endl;
        //take the iterated action
        if (currGameState.isTerminal()) {
            std::cout << "reached somewhere we shouldn't!" << std::endl;
        }
        BaseState newState = currGameState.takeAction(action, 0);

        //for debugging
        std::cout << "Player " << player << "\'s turn: ";
        for (int i = 0; i < newState.history.size(); ++i) {
            std::cout << newState.history.at(i).first << " ";
        }
        std::cout << std::endl << "num nodes is " << nodeList.size() << std::endl;

        playerProbOfCurrState[0] *= playerStrat[action];

        if (player == 1) {
            playerProbOfCurrState[0] *= playerStrat[action];
            std::cout << "player one doing a thing..." << std::endl;
            float actionUtility = doAlgo(playerProbOfCurrState, newState);
            utilities[action] = -1 * actionUtility;
        } else {
            playerProbOfCurrState[1] *= playerStrat[action];
            std::cout << "player two doing a thing..." << std::endl;
            float actionUtility = doAlgo(playerProbOfCurrState, newState);
            utilities[action] = -1 * actionUtility;
        }
        node.node_utility += playerStrat[action] * utilities[action];
    }

    for (string action : node.actions) {
        // for each action, compute and accumulate counterfactual regret
        double regret = utilities[action] - node.node_utility;
        node.regret_sum[action] += (player == 0 ? playerProbOfCurrState.at(1) : playerProbOfCurrState.at(0)) * regret;
    }


    return node.node_utility;
}

BaseNode CFRAlgo::get_node(BaseState gameState) {
    //Finds the node in the algo node_set.
    for (int i = 0; i < nodeList.size(); ++i) {
        bool isMatching = nodeList.at(i).isThisInfoSet(gameState);
        if (isMatching) {
    //found our node, return it
            BaseNode output = nodeList.at(i);
            return output;
        }
    }
    //Went through all nodes, didn't find it. Make a new one!
    vector<string> actionList{};
    for (auto pair : gameState.getLegalActions()) {
        actionList.push_back(pair.first);
    }
    CFRNode currNode = CFRNode(gameState, gameState.getLegalActions().size(), actionList);
    nodeList.push_back(currNode);
    return currNode;
}

CFRAlgo::~CFRAlgo() {

}

vector<BaseNode> CFRAlgo::train(int numIterations, BaseState rootState){
    double utility = 0;
    vector<double> playerProbOfState{};
    playerProbOfState.push_back(1);
    playerProbOfState.push_back(1);
    for (int i = 0; i < numIterations; i++) {
        utility += doAlgo(playerProbOfState, rootState);
    }

    // construct a map with the average strategy over the training process
    return nodeList;
}


//
// Created by danielfm on 5/16/22.
//

#include "CFRAlgo.h"

#include <utility>
#include "CFRNode.h"
#include "../Games/TicTacToeData.h"
#include "../Games/TicTacToeState.h"

CFRAlgo::CFRAlgo(BaseData gameData, BaseState *gameState) {
    this->gameData = std::move(gameData);
    this->currGameState = gameState;
}

double CFRAlgo::doAlgo(vector<double> playerProbOfCurrState, BaseState* currGameState) {
    int player = currGameState->getCurrPlayer();

    // return payoff for terminal states (for current player)
    if (currGameState->isTerminal()) {
        return currGameState->getPayoffs().at(player-1);
    }
    //get the node corresponding to this info state
    auto node = get_node(currGameState);

    // for each action, recursively call cfr with additional history and probability
    std::unordered_map<string, double> playerStrat = node->get_strategy(
            player == 1 ? playerProbOfCurrState.at(0) : playerProbOfCurrState.at(1));
    std::unordered_map<string, double> utilities{};
    double currNodeUtility = 0;
    for (string action : node->actions) {
        //take the iterated action
        BaseState* newState = currGameState->takeAction(action, 0);
        //find the utility of taking that action
        if (player == 1) {
            playerProbOfCurrState[0] *= playerStrat[action];
            utilities[action] = - doAlgo(playerProbOfCurrState, newState);
        } else {
            playerProbOfCurrState[1] *= playerStrat[action];
            utilities[action] = - doAlgo(playerProbOfCurrState, newState);
        }
        node->node_utility += playerStrat[action] * utilities[action];
    }

    for (string action : node->actions) {
        // for each action, compute and accumulate counterfactual regret
        double regret = utilities[action] - node->node_utility;
        node->regret_sum[action] += (player == 0 ? playerProbOfCurrState.at(1) : playerProbOfCurrState.at(0)) * regret;
    }


    return node->node_utility;
}

BaseNode* CFRAlgo::get_node(BaseState *const gameState) {
    //Finds the node in the algo node_set.
    for (int i = 0; i < nodeList.size(); ++i) {
        bool isMatching =nodeList.at(i)->isThisInfoSet(gameState);
        if (isMatching) {
    //found our node, return it
            BaseNode* output = nodeList.at(i);
            return output;
        }
    }
    //Went through all nodes, didn't find it. Make a new one!
    vector<string> actionList{};
    for (auto pair : gameState->getLegalActions()) {
        actionList.push_back(pair.first);
    }
    CFRNode* currNode = new CFRNode(gameState, gameState->getLegalActions().size(), actionList);
    return currNode;
}

CFRAlgo::~CFRAlgo() {

}

vector<BaseNode*> CFRAlgo::train(int numIterations, BaseState* rootState){
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


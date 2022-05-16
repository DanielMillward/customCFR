//
// Created by danielfm on 5/16/22.
//

#include "CFRNode.h"

std::unordered_map<string, double> CFRNode::get_average_strategy() const {
    std::unordered_map<string, double> average_strategy{};
    double normalizing_sum = 0;

    for (const string& action : actions) {
    //add all the strategies of the sums of strategies to this normalizer
        normalizing_sum += strategy_sum.find(action)->second;
    }

    //return the good final strategy stuff (averaged out if not trained yet for this node)
    for (const string action: actions) {
        if (normalizing_sum > 0) {
            average_strategy[action] = strategy_sum.find(action)->second / normalizing_sum;
        } else {
            average_strategy[action] = 1.0 / numActions;
        }
    }

    return average_strategy;
}

std::unordered_map<string, double> CFRNode::get_strategy(double realization_weight) {
    double normalizing_sum = 0;
    //If the (cumulative?) regret for an action is negative, make it at least 0.
    for (const string& action : actions) {
        strategy[action] = regret_sum[action] > 0 ? regret_sum[action] : 0;
        normalizing_sum += strategy[action];
    }
    //normalize it by the realization weight
    for (const string& action : actions) {
        if (normalizing_sum > 0) {
            strategy[action] /= normalizing_sum;
        } else {
            strategy[action] = 1.0 / numActions;
        }
    //add the strategy (weighted by the probability of this node) to the strategy sum
        strategy_sum[action] += realization_weight * strategy[action];
    }

    return strategy;
}

bool CFRNode::isThisInfoSet(BaseState *gameState) const {
    //check if sequence of player moves are the same in history (e.g. chance, p1, p2, p1, p2)
    //check if the value for this player's actions are the same
    //check if visible chance actions are the same
    //check if visible other player actions are the same
    //check if current player data is the same

    //basically, check if histories are the same except for hidden other player actions/chance actions

    //right now, just check if exact histories are the same
    if (gameState->history.size() == currState->history.size()) {
        for (int i = 0; i < gameState->history.size(); ++i) {
            if (!(gameState->history.at(i).first == currState->history.at(i).first)) {
                return false;
            } else if (gameState->history.at(i).second != currState->history.at(i).second) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

CFRNode::CFRNode(BaseState *gameState, int numActions, vector<string> actions) {
    this->numActions = numActions;
    for (int i = 0; i < numActions; ++i) {
        strategy[actions.at(i)] = 0;
        strategy_sum[actions.at(i)] = 0;
        regret_sum[actions.at(i)] = 0;
    }
    this->actions = actions;
    this->currState = gameState;
}


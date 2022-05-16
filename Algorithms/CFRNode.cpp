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

std::pair<bool, vector<pair<std::string, float> > > CFRNode::isThisInfoSet(BaseState *gameState) const {
    return std::pair<bool, vector<pair<std::string, float>>>();
}

CFRNode::CFRNode(int numActions, vector<string> actions) {
    this->numActions = numActions;
    for (int i = 0; i < numActions; ++i) {
        strategy[actions.at(i)] = 0;
        strategy_sum[actions.at(i)] = 0;
        regret_sum[actions.at(i)] = 0;
    }
    this->actions = actions;
}


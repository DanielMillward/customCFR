//
// Created by danielfm on 5/11/22.
//

#include "BaseState.h"

std::vector<int> BaseState::getPayoffs() {
    return std::vector<int>();
}

bool BaseState::isTerminal() {
    return false;
}

int BaseState::getCurrPlayer() {
    return 69;
}

vector<pair<string, pair<float, float>>> BaseState::getLegalActions() {
    return vector<pair<string, pair<float, float>>>();
}

void BaseState::visualizeState() {

}

vector<pair<std::string, float>> BaseState::getInfoSet(int player) {
    return vector<pair<std::string, float>>();
}

BaseState BaseState::takeAction(string action, float value) {
    return BaseState();
}


cmake_minimum_required(VERSION 3.22)
project(customCFR)

set(CMAKE_CXX_STANDARD 14)

add_executable(customCFR main.cpp BaseFiles/UniversalGame.cpp BaseFiles/UniversalGame.h BaseFiles/BaseState.cpp BaseFiles/BaseState.h BaseFiles/BaseAlgo.cpp BaseFiles/BaseAlgo.h BaseFiles/BaseData.cpp BaseFiles/BaseData.h Games/TicTacToeData.cpp Games/TicTacToeData.h Games/TicTacToeState.cpp Games/TicTacToeState.h)

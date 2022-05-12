cmake_minimum_required(VERSION 3.22)
project(customCFR)

set(CMAKE_CXX_STANDARD 14)

add_executable(customCFR main.cpp BaseFiles/BaseGame.cpp BaseFiles/BaseGame.h BaseFiles/BaseState.cpp BaseFiles/BaseState.h BaseFiles/BaseAlgo.cpp BaseFiles/BaseAlgo.h Games/TicTacToe.cpp Games/TicTacToe.h)

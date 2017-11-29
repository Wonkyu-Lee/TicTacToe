cmake_minimum_required(VERSION 3.8)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TicTacToe.h TicTacToeGame.cpp TicTacToeRun.cpp)
add_executable(TicTacToe ${SOURCE_FILES})
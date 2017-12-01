cmake_minimum_required(VERSION 3.6)

project(CppTrivia)

set(SOURCE_FILES
        GameRunner.cpp
        Game.cpp)

add_executable(Trivia ${SOURCE_FILES})

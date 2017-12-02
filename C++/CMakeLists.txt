cmake_minimum_required(VERSION 3.6)

project(CppTrivia)

set(SOURCE_FILES
        game/GameRunner.cpp
        game/Game.cpp)

add_library(TriviaLib ${SOURCE_FILES})
target_include_directories(TriviaLib PUBLIC game)

add_executable(Trivia main.cpp)
target_link_libraries(Trivia TriviaLib)

add_executable(TriviaTest test/mainTest.cpp)
target_link_libraries(TriviaTest TriviaLib)
target_compile_features(TriviaTest PRIVATE cxx_auto_type cxx_constexpr)

enable_testing()

add_test(NAME compareRefrence
         COMMAND TriviaTest
         WORKIGIN_DIRECTORY test)

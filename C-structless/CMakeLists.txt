cmake_minimum_required(VERSION 3.6)

project(CppTrivia
        LANGUAGES C)

set(SOURCE_FILES
        game/game_runner.c
        game/game.c
        game/player.c)

add_library(TriviaLib ${SOURCE_FILES})
target_include_directories(TriviaLib PUBLIC game)

add_executable(Trivia main.c)
target_link_libraries(Trivia TriviaLib)

add_executable(TriviaTest test/mainTest.c)
target_link_libraries(TriviaTest TriviaLib)

enable_testing()

add_test(NAME compareRefrence
        COMMAND TriviaTest
        WORKIGIN_DIRECTORY test)

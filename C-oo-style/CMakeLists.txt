cmake_minimum_required(VERSION 3.6)

project(CooTrivia
        LANGUAGES C)
#game files
set(SOURCE_FILES
        game/game_runner.c
        game/game.c)

#create the game library
add_library(TriviaLib ${SOURCE_FILES})
#export all the *.h togheder with the lib
target_include_directories(TriviaLib PUBLIC game)

#create a main
add_executable(Trivia main.c)
#link the TriviaLib game lib
target_link_libraries(Trivia TriviaLib)

### Testing ###
#create a test binary
add_executable(TriviaTest test/mainTest.c)
#add the game libs to test
target_link_libraries(TriviaTest TriviaLib)
#generat the test binary inside a test directory
set_target_properties( TriviaTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")

#enable the use of ctest
enable_testing()
#add the test to the ctest suite
add_test(NAME compareRefrence
        COMMAND TriviaTest
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")

cmake_minimum_required(VERSION 3.6)

project(CTrivia)

#games file
set(SOURCE_FILES
        game/GameRunner.cpp
        game/Game.cpp)

#create a library with all the games files
add_library(TriviaLib ${SOURCE_FILES})
#export all the *.h files togheder with the lib
target_include_directories(TriviaLib PUBLIC game)

#create a game binary
add_executable(Trivia main.cpp)
#link the trivialib
target_link_libraries(Trivia TriviaLib)

### Testing ###

#create a binary exeguible
add_executable(TriviaTest test/mainTest.cpp)
#link the test lib
target_link_libraries(TriviaTest TriviaLib)
## add the c++ feature used to select the right c++ standard
target_compile_features(TriviaTest PRIVATE cxx_auto_type cxx_constexpr)
#generate the test binary inside a test directory
set_target_properties( TriviaTest
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test")


#enable the use of ctest
enable_testing()
#add the test to the ctest suite
add_test(NAME compareRefrence
        COMMAND TriviaTest
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test")


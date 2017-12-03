package com.adaptionsoft.games.trivia.runner

fun main(args: Array<String>) {
    if(args.size>0)
        runGame(args[0].toInt())
    else
        runGame(0)
}
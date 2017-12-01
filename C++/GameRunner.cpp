#include <stdlib.h>
#include "Game.h"

static bool notAWinner;

int main(int argc, char *args[])
{

	if(argc == 2){
		srand(atoi(args[1]));
	}

	Game aGame;

	aGame.add("Chet");
	aGame.add("Pat");
	aGame.add("Sue");

	do
	{

		aGame.roll(rand() % 5 + 1);

		if (rand() % 9 == 7)
		{
			notAWinner = aGame.wrongAnswer();
		}
		else
		{
			notAWinner = aGame.wasCorrectlyAnswered();
		}
	} while (notAWinner);

}

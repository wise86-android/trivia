#include <stdlib.h>
#include <time.h>
#include "game.h"
#include <stdio.h>

int
run_game (int argc,char *args[])
{
  newGame();

  add ("Chet");
  add ( "Pat");
  add ( "Sue");

	if(argc==2) {
		printf("%s",args[1]);
		srand(atoi(args[1]));
	}

      do
	{
	  roll ( rand () % 5 + 1);

	  if (rand () % 9 == 7)
	    {
	      wrong_answer ();
	    }
	  else
	    {
	      was_correctly_answered ();
	    }
	}
      while (not_a_winner);
  }

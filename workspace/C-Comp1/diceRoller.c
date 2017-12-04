#include "diceRoller.h"

int diceRoller(void)
{
	int diceSides = 0;
	int numRolls = 0;
	int numDice = 0;

	srand(time(NULL));

	printf("Welcome to Dice Roller.\n\n"
	"How many dice would you like to roll?.\n");
	numDice = inputValInt(1, 9);

	printf("\nHow many times would you like to roll the dice?.\n");
	numRolls = inputValInt(1, 9);

	printf("\nHow many sides would you like each dice to have?.\n");
	diceSides = inputValInt(2, 9);

	for (int r = 1; r <= numRolls; r++)
	{
		for (int i = 1; i <= numDice; i++) 
		{
			int n = rand() % diceSides + 1;
			printf("\nRoll %d- Dice %d is %d.", r, i, n);
			sleep(1);
		}
	}

	return 0;
}

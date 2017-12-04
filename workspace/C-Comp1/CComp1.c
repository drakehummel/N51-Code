
#include "CComp1.h"

#define MENU_QUIT 5


int main()
{
	int selection = 0;

	do 
	{
		printf("\n\n__________________________________\n"
		"COMP 1 MENU\n\n"
		"Please select 1-5 for the following:\n"
		"1- Dice Roller\n"
		"2- Circle Area\n"
		"3- Cube Volume\n"
		"4- Number to Binary\n"
		"5- Exit\n\n");

		selection = inputValInt(1, 5);

		switch (selection)
		{	

			case 1:
			{
				diceRoller();
				break;
			}

			case 2:
			{
				circleArea();
				break;	
			}


			case 3:
			{
				cubeVol();					
				break;			
			}

		
			case 4:
			{
				convertToBinary();				
				break;
			}


			case 5:
			{
				printf("\nGoodbye!\n\n");
				return 0;
			}
		

			default:
			{
				printf("Invalid Entry\nPlease try again!\n");
			}	

		}	
		
	} while (MENU_QUIT != selection);

	return 0;
}



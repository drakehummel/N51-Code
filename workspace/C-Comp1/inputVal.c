//TODO - PUT THE REPEATED CODE INTO ONE FUNCTION
#include "inputVal.h"

// This func gets a menu selection and returns the selection if it is valid.
// Otherwise it returns menu_bad_input

#define BUFFER_SIZE 100


int inputValInt(int low, int high)
{
	char *badChar = NULL;		// address to a "bad character"
	char *location = NULL;		// address to the first newline character in the buffer
	int selection = 0;
	char buf[BUFFER_SIZE] = {0};	// initialize a buffer of BUFFER_SIZE to null. 
	char bad = 0;


	do
	{
		printf("Please enter a number that is between %d and %d.\n", low, high);

		//TODO CHECK FOR THE ERROR CONDITION AND EXIT IF THERE IS AN ERROR
		fgets(buf, BUFFER_SIZE, stdin);

		// This is searching the string (buf) for the char '\n' and setting its address to the variable location
		location = strchr(buf, '\n');

		if (location != NULL)
		{
			*location = '\0';
		}
		else
		{
			//this is clearing the buffer by reading reading each character and assigning it to bad
			do
			{
				bad = fgetc(stdin);
			}while(bad != '\n');
		}

		// strtol returns the long integer equivelant of a string
		// parameter 1- buf= the string to be converted
		// parameter 2- &badchar= the address of the first invalid character, which makes it the last character it looks at (endptr)
		// parameter 3- the base (base 10 in this case)
		selection = strtol(buf, &badChar, 10);	// converting the string to a long int

		//	printf("%x", *buf);

	}while(*buf == '\0' || selection < low || selection > high || (badChar != NULL && *badChar != '\0'));
	
	return (selection);
}


float inputValFloat(float min, float max) {
	char *badChar = NULL;			// address to a "bad character"
	char *location = NULL;			// address to the first newline character in the buffer
	float selection = 0.0;
	char buf[BUFFER_SIZE] = {0};		// initialize a buffer of BUFFER_SIZE to null.
	char bad = 0;


	do{
		printf("Please enter a number that is between %f and %f.\n", min, max);

		fgets(buf, BUFFER_SIZE, stdin);

		// This is searching the string (buf) for the char '\n' and setting its address to the variable location
		location = strchr(buf, '\n');

		if (location != NULL)
		{
			*location = '\0';
		}
		else
		{
			//this is clearing the buffer by reading reading each character and assigning it to bad
			do
			{
				bad = fgetc(stdin);
			}while(bad != '\n');
		}

		// strtol returns the long integer equivelant of a string
		// parameter 1- buf= the string to be converted
		// parameter 2- &badchar= the address of the first invalid character, which makes it the last character it looks at (endptr)
		// parameter 3- the base (base 10 in this case)
		selection = strtof(buf, &badChar); // converting the string to a float. no base bc its decimal


	}while(*buf == '\0' || selection < min || selection > max || (badChar != NULL && *badChar != '\0'));


	return (selection);
}

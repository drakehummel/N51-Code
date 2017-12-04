#include "cubeVol.h"
#include "fileWriter.h"


void cubeVol(void)
{
	float side = 0;
	float vol = 0;
	char output[100] = {0};

	printf("Welcome to Cube Volume. \n"
	"What is the length of one side of your cube?");
	side = inputValFloat(FLT_MIN, FLT_MAX);

	vol = pow(side, 3);

	//prints to a string
	snprintf(output, 100, "%f", cubeVol);
	fileWriter("Cube Volume", output);

	printf("The volume of the box is %f\n", vol);
}

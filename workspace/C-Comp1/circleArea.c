#include "circleArea.h"
#include "fileWriter.h"

#define PI 3.14

void circleArea()
{
	float circRadi = 0.0;
	float radiSqr = 0.0;
	float circArea = 0.0;
	char output[100] = {0};

	printf("\nWelcome to Circle Area.\nWhat would you like the radius of the circle to be?\n");
	
	circRadi = inputValFloat(0.0, 10000.0);


	circArea = (pow(circRadi, 2)) * PI;

	//prints to a string
	snprintf(output, 100, "%f", circArea);
	fileWriter("Circle Area", output);

	printf("\nThe area of the circle is %f\n\n", circArea);
}
	

/*
 * temp.c
 *
 *  Created on: Apr 30, 2017
 *      Author: root
 */

#include "temp.h"

int main(int argc, char *argv[])
{
	int s = 0;
	char buffer[BUFFERSIZE] = {0};

	s = square(5);

	do
	{
		fgets(buffer, sizeof(buffer), stdin);
	} while(strncmp(buffer, "QUIT\n", sizeof(buffer)));

	return 0;

}

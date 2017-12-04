#include "fileWriter.h"
#include <stdio.h>

void fileWriter(char*  label, char* data)
{
	FILE *fp;
	fp = fopen("test.txt", "a");
	fprintf(fp, "%s: %s\n", label, data);
	fclose(fp);
}

#include "binary.h"

long long convertToBinary(void)
{
	int logNum = 0;
	int num = 0;
	int ogNum = 0;
	char binaryNum[100] = {0};
	int i = 0;

	printf("What decimal number would you like to see in binary?\n");

	ogNum = num = inputValInt(0, INT_MAX);
	//ogNum = num;

	//assigns the highest power of 2 possible that could go into num, into logNum. ex- num=12 logNum=3 (2^3)
	logNum = (int)log2(num);

	if(num == 0)
	{
		binaryNum[0]= '0';
	}

	for(; logNum >= 0; logNum--)
	{	
		if(pow(2, logNum) <= num)
		{
			binaryNum[i] = '1';
			num -= pow(2, logNum);
		}
		else
		{
			binaryNum[i] = '0';		
		}

		i++;
	}


	printf("\n%d in binary = %s\n\n", ogNum, binaryNum);
	return 0;
}


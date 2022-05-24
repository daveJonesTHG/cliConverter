#include "BaseConverter.h"

void binToDec(char *valToConv, char **retPtr){
	int inputSize = 0;
	while(*(valToConv + ++inputSize) != '\0')
		;

	int resultAsInt = 0;
	int i;
	int sizeOfReturnString;

	for(i = 0; i < inputSize; i++){
		if(valToConv[i] == '1'){
			double valToAdd;
			valToAdd = pow(2, (double) (inputSize - (i + 1)));
			resultAsInt += (int) valToAdd;
		}
	}
	if(resultAsInt == 0)
		sizeOfReturnString = 1;
	else
		sizeOfReturnString = floor(log10(abs(resultAsInt))) + 1;
	
	char *retVal;
	retVal = (char *) malloc(sizeof(char) * (sizeOfReturnString + 1));

	for(i = 0; i < sizeOfReturnString; i++){
		int temp;
		temp = resultAsInt % 10;
		retVal[sizeOfReturnString - (i+1)] = temp + '0';
		resultAsInt -= temp;
		resultAsInt /= 10;
	}
	retVal[sizeOfReturnString] = '\0';
	*retPtr = retVal;
}

void decToBin(char *valToConv, char **retPtr)
{
	int firstPower = 1;
	int inputAsInt = atoi(valToConv);
	while((int) pow(2, (double) ++firstPower) < inputAsInt)
		;
	firstPower--;
	printf("%d\n", firstPower);
}

#include "BaseConverter.h"

int binToDec(char *valToConvPtr, char **retValPtr)
{
	long resultAsLong = 0;
	int i;
	int sizeOfReturnString;

	int inputSize = 0;
	while (*(valToConvPtr + ++inputSize) != '\0')
		;

	if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B'))
	{
		inputSize -= 2;
		valToConvPtr += 2;
	}

	for (i = 0; i < inputSize; i++)
	{
		switch (valToConvPtr[i])
		{
		case '0':
			break;
		case '1':
			resultAsLong += intFromNonDecimal(1, 2, i, inputSize);
			break;
		default:
			return 1;
		}
	}
	if (resultAsLong == 0)
		sizeOfReturnString = 1;
	else
		sizeOfReturnString = floor(log10(abs(resultAsLong))) + 1;

	char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

	stringFromLong(resultAsLong, sizeOfReturnString, retVal);

	*retValPtr = retVal;
	return 0;
}

void decToBin(char *valToConvPtr, char **retValPtr)
{
	int firstPower = 1;
	int inputAsInt = atoi(valToConvPtr);
	while ((int)pow(2, (double)++firstPower) < inputAsInt)
		;
	firstPower--;
	printf("%d\n", firstPower);
}

int hexToDec(char *valToConvPtr, char **retValPtr)
{
	long resultAsLong = 0;
	int i;
	long sizeOfReturnString;
	int inputSize = 0;

	while (*(valToConvPtr + ++inputSize) != '\0')
		;

	if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'x' || *(valToConvPtr + 1) == 'X'))
	{
		inputSize -= 2;
		valToConvPtr += 2;
	}

	for (i = 0; i < inputSize; i++)
	{
		switch (valToConvPtr[i])
		{
		case '0':
			break;
		case '1':
			resultAsLong += intFromNonDecimal(1, 16, i, inputSize);
			break;
		case '2':
			resultAsLong += intFromNonDecimal(2, 16, i, inputSize);
			break;
		case '3':
			resultAsLong += intFromNonDecimal(3, 16, i, inputSize);
			break;
		case '4':
			resultAsLong += intFromNonDecimal(4, 16, i, inputSize);
			break;
		case '5':
			resultAsLong += intFromNonDecimal(5, 16, i, inputSize);
			break;
		case '6':
			resultAsLong += intFromNonDecimal(6, 16, i, inputSize);
			break;
		case '7':
			resultAsLong += intFromNonDecimal(7, 16, i, inputSize);
			break;
		case '8':
			resultAsLong += intFromNonDecimal(8, 16, i, inputSize);
			break;
		case '9':
			resultAsLong += intFromNonDecimal(9, 16, i, inputSize);
			break;
		case 'a':
		case 'A':
			resultAsLong += intFromNonDecimal(10, 16, i, inputSize);
			break;
		case 'b':
		case 'B':
			resultAsLong += intFromNonDecimal(11, 16, i, inputSize);
			break;
		case 'c':
		case 'C':
			resultAsLong += intFromNonDecimal(12, 16, i, inputSize);
			break;
		case 'd':
		case 'D':
			resultAsLong += intFromNonDecimal(13, 16, i, inputSize);
			break;
		case 'e':
		case 'E':
			resultAsLong += intFromNonDecimal(14, 16, i, inputSize);
			break;
		case 'f':
		case 'F':
			resultAsLong += intFromNonDecimal(15, 16, i, inputSize);
			break;
		default:
			return 1;
		}
	}
	if (resultAsLong == 0)
		sizeOfReturnString = 1;
	else
		sizeOfReturnString = floor(log10(abs(resultAsLong))) + 1;

	char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

	stringFromLong(resultAsLong, sizeOfReturnString, retVal);
	*retValPtr = retVal;

	return 0;
}

int intFromNonDecimal(int constant, int base, int powerModifier, int inputSize)
{
	double valToAdd;
	valToAdd = constant * pow(base, (double)(inputSize - (powerModifier + 1)));
	return (int)valToAdd;
}

void stringFromLong(long resultAsLong, int sizeOfReturnString, char *retVal)
{
	for (int i = 0; i < sizeOfReturnString; i++)
	{
		long temp;
		temp = resultAsLong % 10;
		retVal[sizeOfReturnString - (i + 1)] = temp + '0';
		resultAsLong -= temp;
		resultAsLong /= 10;
	}
	*(retVal + sizeOfReturnString) = '\0';
}

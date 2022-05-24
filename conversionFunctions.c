#include "BaseConverter.h"

int binToHex(char *valToConv, char **retPtr)
{
	return 0;
}

int hexToBin(char *valToConv, char **retPtr)
{
	return 0;
}

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
		sizeOfReturnString = floor(log10(labs(resultAsLong))) + 1;

	char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

	stringFromLong(resultAsLong, sizeOfReturnString, retVal);

	*retValPtr = retVal;
	return 0;
}

int decToBin(char *valToConvPtr, char **retValPtr)
{
	int firstPower = 1;
	int inputAsInt = atoi(valToConvPtr);
	while ((int)pow(2, (double)++firstPower) < inputAsInt)
		;
	firstPower--;
	printf("%d\n", firstPower);
	return 0;
}

int decToHex(char *valToConvPtr, char **retValPtr)
{
	long inputAsLong;
	int inputSize = 0;
	int sizeOfReturnString;

	while (*(valToConvPtr + ++inputSize) != '\0')
		;
	inputAsLong = atol(valToConvPtr);
	if (inputAsLong == 0 && (*valToConvPtr != '0' || inputSize != 1))
		return 1;
	if (inputAsLong == 0)
		sizeOfReturnString = 1;
	else
		sizeOfReturnString = floor(log2(labs(inputAsLong)) / log2(16)) + 1;
	char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

	for (int i = 0; i < sizeOfReturnString; i++)
	{
		retVal[sizeOfReturnString - (i + 1)] = intToHexCharacter(inputAsLong % 16);
		inputAsLong /= 16;
	}
	*(retVal + sizeOfReturnString) = '\0';
	*retValPtr = retVal;

	return 0;
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
		sizeOfReturnString = floor(log10(labs(resultAsLong))) + 1;

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

char intToHexCharacter(int i)
{
	switch (i)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'f';
	case 15:
		return 'g';
	}
}

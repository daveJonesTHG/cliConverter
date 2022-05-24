#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  binToDec
 *  Description:  convert from binary to decimal
 * =====================================================================================
 */
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
			resultAsLong += longFromNonDecimal(1, 2, i, inputSize);
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
} /* -----  end of function binToDec  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decToBin
 *  Description:  convert from decimal to binary
 * =====================================================================================
 */
int decToBin(char *valToConvPtr, char **retValPtr)
{
	int returnValueLength = -1;
	long inputAsLong = (long) atoi(valToConvPtr);
	while(inputAsLong >= pow(2, ++returnValueLength))
		;
	char *retVal = (char *)malloc(sizeof(char) * (returnValueLength + 1));

	for(int i = 1; i <= returnValueLength; i++){
		*(retVal + (returnValueLength - i)) = (char)((inputAsLong % 2) + '0');
		inputAsLong = inputAsLong / 2;
	}
	*(retVal + returnValueLength) = '\0';

	*retValPtr = retVal;

	return 0;
} /* -----  end of function decToBin  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  binToHex
 *  Description:  convert from binary to hexadecimal
 * =====================================================================================
 */
int binToHex(char *valToConvPtr, char **retValPtr)
{
	int inputSize = 0;

	while (*(valToConvPtr + ++inputSize) != '\0')
		if (*(valToConvPtr) != '0' && *(valToConvPtr) != '1') /* checking the input is in binary format */
			return 1;
	if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B')) /* TODO: this check currently doesn't work with above line check */
	{
		inputSize -= 2;
		valToConvPtr += 2;
	}
	int retValSize = (inputSize % 4 == 0) ? (inputSize / 4) + 1 : (inputSize / 4) + 2;
	char *retVal = (char *)malloc(sizeof(char)*retValSize);

	char *trackingPtr = valToConvPtr + inputSize - 1;
	for(int i = retValSize - 2; i >= 0; i--){
		int valToInsert = 0;
		for(int j = 0; j < 4; j++){
			if(trackingPtr+1 == valToConvPtr)
				break;
			valToInsert += (int) (pow(2, j) * ((int) *(trackingPtr--) - '0'));
		}
		*(retVal + i) = valToInsert > 9 ? (char) (valToInsert - 10 + 'A') : (char) (valToInsert + '0');
	}
	*(retVal + retValSize - 1) = '\0';

	*retValPtr = retVal;
	return 0;
} /* -----  end of function binToHex  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  hexToBin
 *  Description:  convert from hexadecimal to binary
 * =====================================================================================
 */
int hexToBin(char *valToConvPtr, char **retValPtr)
{
	int inputSize = 0;
	int sizeOfReturnString;
	char hexCharacter;
	while (*(valToConvPtr + ++inputSize) != '\0')
		;
	if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'x' || *(valToConvPtr + 1) == 'X'))
	{
		inputSize -= 2;
		valToConvPtr += 2;
	}
	sizeOfReturnString = inputSize * 4;
	char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));
	*(retVal + sizeOfReturnString) = '\0';
	for (int i = sizeOfReturnString - 1; i > 0; i -= 4)
	{
		hexCharacter = *(valToConvPtr + (i / 4));
		switch (hexCharacter)
		{
		case '0':
			retVal[i] = '0';
			retVal[i - 1] = '0';
			retVal[i - 2] = '0';
			retVal[i - 3] = '0';
			break;
		case '1':
			retVal[i] = '1';
			retVal[i - 1] = '0';
			retVal[i - 2] = '0';
			retVal[i - 3] = '0';
			break;
		case '2':
			retVal[i] = '0';
			retVal[i - 1] = '1';
			retVal[i - 2] = '0';
			retVal[i - 3] = '0';
			break;
		case '3':
			retVal[i] = '1';
			retVal[i - 1] = '1';
			retVal[i - 2] = '0';
			retVal[i - 3] = '0';
			break;
		case '4':
			retVal[i] = '0';
			retVal[i - 1] = '0';
			retVal[i - 2] = '1';
			retVal[i - 3] = '0';
			break;
		case '5':
			retVal[i] = '1';
			retVal[i - 1] = '0';
			retVal[i - 2] = '1';
			retVal[i - 3] = '0';
			break;
		case '6':
			retVal[i] = '0';
			retVal[i - 1] = '1';
			retVal[i - 2] = '1';
			retVal[i - 3] = '0';
			break;
		case '7':
			retVal[i] = '1';
			retVal[i - 1] = '1';
			retVal[i - 2] = '1';
			retVal[i - 3] = '0';
			break;
		case '8':
			retVal[i] = '0';
			retVal[i - 1] = '0';
			retVal[i - 2] = '0';
			retVal[i - 3] = '1';
			break;
		case '9':
			retVal[i] = '1';
			retVal[i - 1] = '0';
			retVal[i - 2] = '0';
			retVal[i - 3] = '1';
			break;
		case 'a':
			retVal[i] = '0';
			retVal[i - 1] = '1';
			retVal[i - 2] = '0';
			retVal[i - 3] = '1';
			break;
		case 'b':
			retVal[i] = '1';
			retVal[i - 1] = '1';
			retVal[i - 2] = '0';
			retVal[i - 3] = '1';
			break;
		case 'c':
			retVal[i] = '0';
			retVal[i - 1] = '0';
			retVal[i - 2] = '1';
			retVal[i - 3] = '1';
			break;
		case 'd':
			retVal[i] = '1';
			retVal[i - 1] = '0';
			retVal[i - 2] = '1';
			retVal[i - 3] = '1';
			break;
		case 'e':
			retVal[i] = '0';
			retVal[i - 1] = '1';
			retVal[i - 2] = '1';
			retVal[i - 3] = '1';
			break;
		case 'f':
			retVal[i] = '1';
			retVal[i - 1] = '1';
			retVal[i - 2] = '1';
			retVal[i - 3] = '1';
			break;
		default:
			return 1;
		}
	}
	*retValPtr = retVal;

	return 0;
} /* -----  end of function hexToBin  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decToHex
 *  Description:  convert from decimal to hexadecimal
 * =====================================================================================
 */
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
} /* -----  end of function decToHex  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  hexToDec
 *  Description:  convert from hexadecimal to decimal
 * =====================================================================================
 */
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
			resultAsLong += longFromNonDecimal(1, 16, i, inputSize);
			break;
		case '2':
			resultAsLong += longFromNonDecimal(2, 16, i, inputSize);
			break;
		case '3':
			resultAsLong += longFromNonDecimal(3, 16, i, inputSize);
			break;
		case '4':
			resultAsLong += longFromNonDecimal(4, 16, i, inputSize);
			break;
		case '5':
			resultAsLong += longFromNonDecimal(5, 16, i, inputSize);
			break;
		case '6':
			resultAsLong += longFromNonDecimal(6, 16, i, inputSize);
			break;
		case '7':
			resultAsLong += longFromNonDecimal(7, 16, i, inputSize);
			break;
		case '8':
			resultAsLong += longFromNonDecimal(8, 16, i, inputSize);
			break;
		case '9':
			resultAsLong += longFromNonDecimal(9, 16, i, inputSize);
			break;
		case 'a':
		case 'A':
			resultAsLong += longFromNonDecimal(10, 16, i, inputSize);
			break;
		case 'b':
		case 'B':
			resultAsLong += longFromNonDecimal(11, 16, i, inputSize);
			break;
		case 'c':
		case 'C':
			resultAsLong += longFromNonDecimal(12, 16, i, inputSize);
			break;
		case 'd':
		case 'D':
			resultAsLong += longFromNonDecimal(13, 16, i, inputSize);
			break;
		case 'e':
		case 'E':
			resultAsLong += longFromNonDecimal(14, 16, i, inputSize);
			break;
		case 'f':
		case 'F':
			resultAsLong += longFromNonDecimal(15, 16, i, inputSize);
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
} /* -----  end of function hexToDec  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  longFromNonDecimal
 *  Description:  return an int from a binary character or hexadecimal character.
 * 				  Used when converting a
 * =====================================================================================
 */
int longFromNonDecimal(int constant, int base, int powerModifier, int inputSize)
{
	long double valToAdd;
	valToAdd = constant * pow(base, (long double)(inputSize - (powerModifier + 1)));
	return (long)valToAdd;
} /* -----  end of function parseArgs  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  stringFromLong
 *  Description:  converts a long into it's string representation (which is saved at
 * 				  the address the returnValue pointer points to)
 * =====================================================================================
 */
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
} /* -----  end of function longFromNonDecimal  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  intToHexCharacter
 *  Description:  converts an int (0 <= int < 16) into a hex character
 * =====================================================================================
 */
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
		return 'e';
	case 15:
		return 'f';
	}

	return '\0';
} /* -----  end of function intToHexCharacter  ----- */

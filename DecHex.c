#include "BaseConverter.h"

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
    int sizeOfReturnString, valToInsert;

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
        valToInsert = inputAsLong % 16;
        retVal[sizeOfReturnString - (i + 1)] = valToInsert > 9 ? (char)(valToInsert - 10 + 'a') : (char)(valToInsert + '0');
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

    stringFromLong(resultAsLong, sizeOfReturnString, 0, retVal);
    *retValPtr = retVal;

    return 0;
} /* -----  end of function hexToDec  ----- */
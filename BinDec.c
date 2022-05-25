#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  binToDec
 *  Description:  convert from binary to decimal
 * =====================================================================================
 */
int binToDec(char *valToConvPtr, char **retValPtr, int signedMode)
{
    long resultAsLong = 0;
    int i, sizeOfReturnString;
    int inputSize = 0;
    int negativeSignRequired = 0;

    if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B'))
    {
        valToConvPtr += 2;
    }
    while (*(valToConvPtr + ++inputSize) != '\0')
        if (*(valToConvPtr) != '0' && *(valToConvPtr) != '1')
            return 1;
    if (signedMode && *(valToConvPtr) == '1')
    {
        resultAsLong -= longFromNonDecimal(1, 2, 0, inputSize);
        negativeSignRequired = 1;
    }
    for (i = negativeSignRequired; i < inputSize; i++)
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
        sizeOfReturnString = negativeSignRequired ? floor(log10(labs(resultAsLong))) + 2 : floor(log10(labs(resultAsLong))) + 1;

    char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

    if (negativeSignRequired)
        *(retVal) = '-';
    stringFromLong(labs(resultAsLong), sizeOfReturnString, negativeSignRequired, retVal);

    *retValPtr = retVal;
    return 0;
} /* -----  end of function binToDec  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decToBin
 *  Description:  convert from decimal to binary
 * =====================================================================================
 */
int decToBin(char *valToConvPtr, char **retValPtr, int signedMode)
{
    int returnValueLength = -1;
    long inputAsLong = atol(valToConvPtr);
    long absInputAsLong = labs(inputAsLong);
    while (absInputAsLong >= pow(2, ++returnValueLength))
        ;
    char *retVal = (char *)malloc(sizeof(char) * (returnValueLength + 1));

    for (int i = 1; i <= returnValueLength; i++)
    {
        *(retVal + (returnValueLength - i)) = (char)((inputAsLong % 2) + '0');
        inputAsLong /= 2;
    }
    *(retVal + returnValueLength) = '\0';

    *retValPtr = retVal;

    return 0;
} /* -----  end of function decToBin  ----- */

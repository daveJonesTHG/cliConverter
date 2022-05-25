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
int decToBin(char *valToConvPtr, char **retValPtr, int signedMode, int returnLong)
{
    if (signedMode)
        return signedDecToBin(valToConvPtr, retValPtr, returnLong);
    else
        return unsignedDecToBin(valToConvPtr, retValPtr);
} /* -----  end of function decToBin  ----- */

int unsignedDecToBin(char *valToConvPtr, char **retValPtr)
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
}

int signedDecToBin(char *valToConvPtr, char **retValPtr, int returnLong)
{
    int returnValueLength;
    long inputAsLong = atol(valToConvPtr);
    long absInputAsLong = labs(inputAsLong);

    if (returnLong)
        returnValueLength = 64;
    else
        returnValueLength = 32;

    char *retVal = (char *)malloc(sizeof(char) * (returnValueLength + 1));

    if (inputAsLong < 0)
    {
        *(retVal) = '1';
        long currentValue = (long)pow(2, (returnValueLength - 1)) * -1;
        for (int i = 1; i < returnValueLength; i++)
        {
            if ((currentValue + absInputAsLong) <= 0)
            {
                *(retVal + i) = '1';
                currentValue += absInputAsLong;
                printf("Current value: %ld", currentValue / 1000000);
            }
            else
                *(retVal + i) = '0';
        }
    }
    else
    {
        *(retVal) = '0';
        for (int i = 1; i <= returnValueLength - 1; i++)
        {
            *(retVal + (returnValueLength - i)) = (char)((inputAsLong % 2) + '0');
            inputAsLong /= 2;
        }
    }

    *(retVal + returnValueLength) = '\0';

    *retValPtr = retVal;

    return 0;
}

int decToBin2(char *valToConvPtr, char **retValPtr, int signedMode, int returnLong)
{
    int returnValueLength;
    long inputAsLong = atol(valToConvPtr);
    long absInputAsLong = labs(inputAsLong);

    if (signedMode)
    {
        if (returnLong)
            returnValueLength = 64;
        else
            returnValueLength = 32;
    }
    else
    {
        returnValueLength = -1;
        while (absInputAsLong >= pow(2, ++returnValueLength))
            ;
    }

    char *retVal = (char *)malloc(sizeof(char) * (returnValueLength + 1));
    if (signedMode)
    {
        if (inputAsLong < 0)
            *(retVal) = '1';
        else
            *(retVal) = '0';
    }
    for (int i = 1; i <= returnValueLength - signedMode; i++)
    {
        *(retVal + (returnValueLength - i)) = (char)((inputAsLong % 2) + '0');
        inputAsLong /= 2;
    }
    *(retVal + returnValueLength) = '\0';

    *retValPtr = retVal;

    return 0;
} /* -----  end of function decToBin  ----- */

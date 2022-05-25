#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  binToDec
 *  Description:  convert from binary to decimal
 * =====================================================================================
 */
int binToDec(char *valToConvPtr, char **retValPtr)
{
    uint64_t inputSize = 0;
    if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B'))
        valToConvPtr += 2;
    while (*(valToConvPtr + inputSize) != '\0')
    {
        if (*(valToConvPtr) != '0' && *(valToConvPtr) != '1')
            return 1;
        inputSize++;
    }
    if (sign)
        return signedBinToDec(valToConvPtr, retValPtr, inputSize);
    else
        return unsignedBinToDec(valToConvPtr, retValPtr, inputSize);

} /* -----  end of function binToDec  ----- */

int unsignedBinToDec(char *valToConvPtr, char **retValPtr, uint64_t inputSize)
{
    uint64_t resultAsLong = 0;
    uint64_t sizeOfReturnString;
    for (uint64_t i = 0; i < inputSize; i++)
    {
        switch (*(valToConvPtr + i))
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
    stringFromLong(resultAsLong, sizeOfReturnString, 0, retVal);
    *retValPtr = retVal;
    return 0;
}

int signedBinToDec(char *valToConvPtr, char **retValPtr, uint64_t inputSize)
{
    int64_t resultAsLong = 0;
    uint64_t sizeOfReturnString;
    uint32_t negativeSignRequired = 0;

    if (*(valToConvPtr) == '1')
    {
        resultAsLong -= longFromNonDecimal(1, 2, 0, inputSize);
        negativeSignRequired = 1;
    }
    for (uint32_t i = negativeSignRequired; i < inputSize; i++)
    {
        switch (*(valToConvPtr + i))
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
        sizeOfReturnString = floor(log10(labs(resultAsLong))) + negativeSignRequired + 1;
    char retVal[sizeOfReturnString];
    if (negativeSignRequired)
        *(retVal) = '-';
    stringFromLong(labs(resultAsLong), sizeOfReturnString, negativeSignRequired, retVal);
    *retValPtr = retVal;
    return 0;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decToBin
 *  Description:  convert from decimal to binary
 * =====================================================================================
 */
int decToBin(char *valToConvPtr, char **retValPtr, int returnLong)
{
    int i = 0;
    if (sign)
    {
        if (*valToConvPtr == '-')
            valToConvPtr += 1;
        while (*(valToConvPtr + i) != '\0')
        {
            if (*(valToConvPtr + i) < '0' || *(valToConvPtr + i) > '9')
                return 1;
            i++;
        }
        return signedDecToBin(valToConvPtr, retValPtr, returnLong);
    }
    else
    {
        while (*(valToConvPtr + i) != '\0')
        {
            if (*(valToConvPtr + i) < '0' || *(valToConvPtr + i) > '9')
                return 1;
            i++;
        }
        return unsignedDecToBin(valToConvPtr, retValPtr);
    }
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
        long remainingAmount = ((long)pow(2, (returnValueLength - 1)) * -1) + absInputAsLong;
        long currentValue;
        for (int i = 1; i < returnValueLength; i++)
        {
            currentValue = pow(2, (returnValueLength - (i + 1)));
            if ((remainingAmount + currentValue) <= 0)
            {
                *(retVal + i) = '1';
                remainingAmount += currentValue;
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

// int binToDec2(char *valToConvPtr, char **retValPtr, int signedMode)
// {
//     if (signedMode)
//         __int64_t resultAsLong = 0;
//     else
//         __uint64_t resultAsLong = 0;
//     __uint64_t inputSize = 0;
//     __uint32_t negativeSignRequired = 0;

//     if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B'))
//     {
//         valToConvPtr += 2;
//     }
//     while (*(valToConvPtr + ++inputSize) != '\0')
//         if (*(valToConvPtr) != '0' && *(valToConvPtr) != '1')
//             return 1;
//     if (signedMode && *(valToConvPtr) == '1')
//     {
//         resultAsLong -= longFromNonDecimal(1, 2, 0, inputSize);
//         negativeSignRequired = 1;
//     }
//     for (i = negativeSignRequired; i < inputSize; i++)
//     {
//         switch (valToConvPtr[i])
//         {
//         case '0':
//             break;
//         case '1':
//             resultAsLong += longFromNonDecimal(1, 2, i, inputSize);
//             break;
//         default:
//             return 1;
//         }
//     }
//     if (resultAsLong == 0)
//         sizeOfReturnString = 1;
//     else
//         sizeOfReturnString = negativeSignRequired ? floor(log10(labs(resultAsLong))) + 2 : floor(log10(labs(resultAsLong))) + 1;

//     char *retVal = (char *)malloc(sizeof(char) * (sizeOfReturnString + 1));

//     if (negativeSignRequired)
//         *(retVal) = '-';
//     stringFromLong(labs(resultAsLong), sizeOfReturnString, negativeSignRequired, retVal);

//     *retValPtr = retVal;
//     return 0;
// }
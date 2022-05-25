#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  binToHex
 *  Description:  convert from binary to hexadecimal
 * =====================================================================================
 */
int binToHex(char *valToConvPtr, char **retValPtr)
{
    int inputSize = 0;

    if (*valToConvPtr == '0' && (*(valToConvPtr + 1) == 'b' || *(valToConvPtr + 1) == 'B'))
    {
        valToConvPtr += 2;
    }
    while (*(valToConvPtr + ++inputSize) != '\0')
        if (*(valToConvPtr) != '0' && *(valToConvPtr) != '1')
            return 1;
    int retValSize = (inputSize % 4 == 0) ? (inputSize / 4) + 1 : (inputSize / 4) + 2;
    char *retVal = (char *)malloc(sizeof(char) * retValSize);

    char *trackingPtr = valToConvPtr + inputSize - 1;
    for (int i = retValSize - 2; i >= 0; i--)
    {
        int valToInsert = 0;
        for (int j = 0; j < 4; j++)
        {
            if (trackingPtr + 1 == valToConvPtr)
                break;
            valToInsert += (int)(pow(2, j) * ((int)*(trackingPtr--) - '0'));
        }
        *(retVal + i) = valToInsert > 9 ? (char)(valToInsert - 10 + 'a') : (char)(valToInsert + '0');
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
        case 'A':
            retVal[i] = '0';
            retVal[i - 1] = '1';
            retVal[i - 2] = '0';
            retVal[i - 3] = '1';
            break;
        case 'b':
        case 'B':
            retVal[i] = '1';
            retVal[i - 1] = '1';
            retVal[i - 2] = '0';
            retVal[i - 3] = '1';
            break;
        case 'c':
        case 'C':
            retVal[i] = '0';
            retVal[i - 1] = '0';
            retVal[i - 2] = '1';
            retVal[i - 3] = '1';
            break;
        case 'd':
        case 'D':
            retVal[i] = '1';
            retVal[i - 1] = '0';
            retVal[i - 2] = '1';
            retVal[i - 3] = '1';
            break;
        case 'e':
        case 'E':
            retVal[i] = '0';
            retVal[i - 1] = '1';
            retVal[i - 2] = '1';
            retVal[i - 3] = '1';
            break;
        case 'f':
        case 'F':
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

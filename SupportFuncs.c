#include "BaseConverter.h"

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
void stringFromLong(long resultAsLong, int sizeOfReturnString, int negativeModifier, char *retVal)
{
    for (int i = 0; i < sizeOfReturnString - negativeModifier; i++)
    {
        long temp;
        temp = resultAsLong % 10;
        *(retVal + (sizeOfReturnString - (i + 1))) = temp + '0';
        resultAsLong -= temp;
        resultAsLong /= 10;
    }
    *(retVal + sizeOfReturnString) = '\0';
} /* -----  end of function longFromNonDecimal  ----- */
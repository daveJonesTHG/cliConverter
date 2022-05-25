#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int binToDec(char *valToConv, char **retPtr);
int decToBin(char *valToConv, char **retPtr);
int binToHex(char *valToConv, char **retPtr);
int hexToBin(char *valToConv, char **retPtr);
int decToHex(char *valToConv, char **retPtr);
int hexToDec(char *valToConv, char **retPtr);
void stringFromLong(long resultAsLong, int sizeOfReturnString, char *retVal);
int longFromNonDecimal(int constant, int base, int powerModifier, int inputSize);

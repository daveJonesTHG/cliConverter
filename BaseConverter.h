#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int binToDec(char *valToConv, char **retPtr);
void decToBin(char *valToConv, char **retPtr);
void binToHex(char *valToConv, char **retPtr);
void hexToBin(char *valToConv, char **retPtr);
int decToHex(char *valToConv, char **retPtr);
int hexToDec(char *valToConv, char **retPtr);
void stringFromLong(long resultAsLong, int sizeOfReturnString, char *retVal);
int intFromNonDecimal(int constant, int base, int powerModifier, int inputSize);
char intToHexCharacter(int i);

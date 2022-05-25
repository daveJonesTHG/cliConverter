#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

extern int sign;

int binToDec(char *valToConvPtr, char **retValPtr);
int unsignedBinToDec(char *valToConvPtr, char **retValPtr, uint64_t inputSize);
int signedBinToDec(char *valToConvPtr, char **retValPtr, uint64_t inputSize);
int decToBin(char *valToConvPtr, char **retValPtr, int returnLong);
int unsignedDecToBin(char *valToConvPtr, char **retValPtr);
int signedDecToBin(char *valToConvPtr, char **retValPtr, int returnLong);
int binToHex(char *valToConv, char **retPtr);
int hexToBin(char *valToConv, char **retPtr);
int decToHex(char *valToConv, char **retPtr);
int hexToDec(char *valToConv, char **retPtr);
void stringFromLong(long resultAsLong, int sizeOfReturnString, int negativeModifier, char *retVal);
int longFromNonDecimal(int constant, int base, int powerModifier, int inputSize);

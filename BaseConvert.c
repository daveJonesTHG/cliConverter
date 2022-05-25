/*
 * =====================================================================================
 *
 *       Filename:  BaseConvert.c
 *
 *    Description:	Program for converting between decimal, hexadecimal and binary on the command line
 *
 *        Version:  1.0
 *        Created:  23/05/2022 13:41:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *        Authors:  Dave Jones and Chris Woodham
 *   Organization:	THG
 *
 * =====================================================================================
 */

#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parseArgs
 *  Description:  parse the command line arguments
 * =====================================================================================
 */

int parseArgs(char *conversionType, char **valToConvPtr, int argc, char *argv[])
{
	if (argc != 3)
		return 1;

	if (strcmp(argv[1], "--hbu") != 0 && strcmp(argv[1], "--hdu") != 0 && strcmp(argv[1], "--dbu") != 0 && strcmp(argv[1], "--dhu") != 0 && strcmp(argv[1], "--bhu") != 0 && strcmp(argv[1], "--bdu") != 0 && strcmp(argv[1], "--bds") != 0)
	{
		printf("First argument should be of the form --xy, where x and y are h, d or b\n");
		return 1;
	}
	int i;
	for (i = 0; i < 6; i++)
		*(conversionType + i) = *(argv[1] + i);

	int sizeOfValue = 0;

	do
	{
		++sizeOfValue;
	} while (*(argv[2] + sizeOfValue) != '\0');
	++sizeOfValue;

	char *valToConvert;

	valToConvert = (char *)malloc(sizeof(char) * sizeOfValue);
	for (i = 0; i < sizeOfValue; i++)
	{
		*(valToConvert + i) = *(argv[2] + i);
	}

	*valToConvPtr = valToConvert;

	return 0;
} /* -----  end of function parseArgs  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  callFunctionFromFlag
 *  Description:  call the appropriate conversion function depending on the flag passed
 * 				  as a command line argument
 * =====================================================================================
 */

void callFunctionFromFlag(char *conversionType, char **valToConvPtr, char **retValPtr)
{
	if (strcmp(conversionType, "--dbu") == 0)
	{
		decToBin(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--bdu") == 0)
	{
		binToDec(*valToConvPtr, retValPtr, 0);
	}
	if (strcmp(conversionType, "--hbu") == 0)
	{
		hexToBin(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--bhu") == 0)
	{
		binToHex(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--dhu") == 0)
	{
		decToHex(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--hdu") == 0)
	{
		hexToDec(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--bds") == 0)
	{
		binToDec(*valToConvPtr, retValPtr, 1);
	}
	return;
} /* -----  end of function callFunctionFromFlag  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 * =====================================================================================
 */

int main(int argc, char *argv[])
{

	char *conversionType;
	conversionType = (char *)malloc(sizeof(char) * 6);

	char **valToConvPtr = (char **)malloc(sizeof(char **));

	int err = parseArgs(conversionType, valToConvPtr, argc, argv);
	if (err)
	{
		printf("Error in arguments. Exiting...\n");
		return EXIT_FAILURE;
	}
	char **retValuePtr = (char **)malloc(sizeof(char **));
	callFunctionFromFlag(conversionType, valToConvPtr, retValuePtr);
	printf("Here it is: %s\n", *retValuePtr);
	return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */

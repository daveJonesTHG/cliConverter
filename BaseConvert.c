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
int sign = 0;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parseArgs
 *  Description:  parse the command line arguments
 * =====================================================================================
 */

int parseArgs(char *conversionType, char **valToConvPtr, int argc, char *argv[], int maxInputSize)
{
	if (argc != 3 && argc != 4)
		return 1;

	if (strcmp(argv[1], "--hb") != 0 && strcmp(argv[1], "--hd") != 0 && strcmp(argv[1], "--db") != 0 && strcmp(argv[1], "--dh") != 0 && strcmp(argv[1], "--bh") != 0 && strcmp(argv[1], "--bd") != 0)
	{
		printf("First argument should be of the form --xy, where x and y are h, d or b\n");
		return 1;
	} else {
		strlcpy(conversionType, argv[1], 5);
	}
	
	for(int i = 0; i < argc; i++){
		if(*argv[i] == '-'){
			if(*(argv[i] + 1) == 's')
				sign = 1;
		} 
	}

	int valueArgNum = 0;
	while(*argv[++valueArgNum] == '-')
		;
	
	if(valToConvPtr != NULL)
		*valToConvPtr = strndup(argv[valueArgNum], maxInputSize);

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
	if (strcmp(conversionType, "--db") == 0 && !sign)
	{
		decToBin(*valToConvPtr, retValPtr, 0, 0);
	}
	if (strcmp(conversionType, "--bd") == 0 && !sign)
	{
		binToDec(*valToConvPtr, retValPtr, 0);
	}
	if (strcmp(conversionType, "--hb") == 0)
	{
		hexToBin(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--bh") == 0)
	{
		binToHex(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--dh") == 0)
	{
		decToHex(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--hd") == 0)
	{
		hexToDec(*valToConvPtr, retValPtr);
	}
	if (strcmp(conversionType, "--bd") == 0 && sign)
	{
		binToDec(*valToConvPtr, retValPtr, 1);
	}
	if (strcmp(conversionType, "--db") == 0 && sign)
	{
		decToBin(*valToConvPtr, retValPtr, 1, 1);
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
	enum{
		MAX_INPUT_SIZE = 128
	};

	char conversionType[5];

	char *valToConvPtr = NULL;

	int err = parseArgs(conversionType, &valToConvPtr, argc, argv, MAX_INPUT_SIZE);
	if (err)
	{
		printf("Error in arguments. Exiting...\n");
		return EXIT_FAILURE;
	}
	char **retValuePtr = (char **)malloc(sizeof(char **));
	callFunctionFromFlag(conversionType, &valToConvPtr, retValuePtr);
	printf("%s\n", *retValuePtr);
	free(retValuePtr);
	return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */

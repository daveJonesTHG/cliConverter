/*
 * =====================================================================================
 *
 *       Filename:  BaseConvert.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  23/05/2022 13:41:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#include "BaseConverter.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  parseArgs
 *  Description:
 * =====================================================================================
 */

int parseArgs(char *conversionType, char **valToConvPtr, int argc, char *argv[])
{
	if (argc != 3)
		return 1;

	if (strcmp(argv[1], "--hb") != 0 && strcmp(argv[1], "--hd") != 0 && strcmp(argv[1], "--db") != 0 && strcmp(argv[1], "--dh") != 0 && strcmp(argv[1], "--bh") != 0 && strcmp(argv[1], "--bd") != 0)
	{
		printf("First argument should be of the form --xy, where x and y are h, d or b\n");
		return 1;
	}
	int i;
	for (i = 0; i < 5; i++)
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
 *         Name:  main
 *  Description:
 * =====================================================================================
 */

int main(int argc, char *argv[])
{

	char *conversionType;
	conversionType = (char *)malloc(sizeof(char) * 5);

	char **valToConvPtr = malloc(sizeof(char **));
	// char **valToConvPtr;

	printf("Value to convert pointer:\n");
	printf("%p\n", valToConvPtr);

	int err = parseArgs(conversionType, valToConvPtr, argc, argv);
	if (err)
	{
		printf("Error in arguments. Exiting...\n");
		return EXIT_FAILURE;
	}
	char **retValuePtr = malloc(sizeof(char **));
	// char **retValuePtr;

	printf("Ret value pointer:\n");
	printf("%p\n", retValuePtr);
	hexToDec(*valToConvPtr, retValuePtr);
	printf("Converted value: %s\n", *retValuePtr);
	return EXIT_SUCCESS;
} /* ----------  end of function main  ---------- */

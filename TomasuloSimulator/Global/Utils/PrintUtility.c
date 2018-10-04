/*
 * PrintUtility.c
 *
 *  Created on: Oct 2, 2015
 *      Author: DebashisGanguly
 */

#include "../TomasuloSimulator.h"

/**
 * Utility method to print instruction cache
 */
void printInstructionCache () {
	DictionaryEntry *current;

	if (instructionCache != NULL) {
		printf ("-----------------\n");
		printf ("Instruction Cache\n");
		printf ("-----------------\n");

		for (current = instructionCache -> head; current != NULL; current = current -> next)
			printf ("%d: %s\n", *((int*)current -> key), ((char*)current -> value -> value));
	}
}

/***
 * Utility method to print code lables
 */
void printCodeLabels () {
	DictionaryEntry *current;

	if (codeLabels != NULL) {
		printf ("-----------\n");
		printf ("Code Lables\n");
		printf ("-----------\n");

		for (current = codeLabels -> head; current != NULL; current = current -> next)
			printf ("%s: %d\n", ((char*)current -> key), *((int*)current -> value -> value));
	}
}

/***
 * Utility method to print data cache
 */
void printDataCache () {
	DictionaryEntry *current;

	if (dataCache != NULL) {
		printf ("----------\n");
		printf ("Data Cache\n");
		printf ("----------\n");

		for (current = dataCache -> head; current != NULL; current = current -> next)
			printf ("Mem(%d) = %0.1lf\n", *((int*)current -> key), *((double*)current -> value -> value));
	}
}
/**
 * Utility method to print integer registers
 */
void printIntegerRegisters () {
	int i;

	printf ("-----------------\n");
	printf ("Integer Registers\n");
	printf ("-----------------\n");

	for (i = 0; i < numberOfIntRegisters; i++) {
		printf ("Int_Reg[%d]=%d\n", i, cpu -> integerRegisters [i] -> data);
	}
}

/***
 * Utility method to print floating point registers
 */
void printFPRegisters () {
	int i;

	printf ("------------------------\n");
	printf ("Floating Point Registers\n");
	printf ("------------------------\n");

	for (i = 0; i < numberOfFPRegisters; i++) {
		printf ("FP_Reg[%d]=%0.1lf\n", i, cpu -> floatingPointRegisters [i] -> data);
	}
}

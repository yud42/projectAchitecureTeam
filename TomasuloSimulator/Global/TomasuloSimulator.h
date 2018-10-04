/*
 * TomasuloSimulator.h
 *
 *  Created on: Oct 1, 2015
 *      Author: DebashisGanguly
 */

#ifndef GLOBAL_TOMASULOSIMULATOR_H_
#define GLOBAL_TOMASULOSIMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./DataTypes.h"
#include "./ADT/CircularQueue.h"
#include "./ADT/Dictionary.h"

//macros for parsing and tokenizing
#define DATA_LABEL "DATA"
#define WHITE_SPACE " \t\n"
#define LINE_TERMINATOR "\n"
#define LABEL_TERMINATOR ":"
#define LABEL_TERMINATOR_CHAR ':'
#define MEMORY_LABEL "Mem"
#define MEMORY_SEPARATOR " )(=\n"

#define MAX_LINE  4096

//global variables populated from configuration 
int numberOfIntRegisters; //NIR
int numberOfFPRegisters; //NFPR

int instructionCacheBaseAddress; //ICBA

int cacheLineSize; //CLS

int numberOfInstruction;

Dictionary *instructionCache;
Dictionary *dataCache;
Dictionary *codeLabels;


CPU *cpu;

void fillInstructionAndDataCache (char *fileName);

void initializeCPU ();

int runClockCycle ();

void printInstructionCache ();
void printCodeLabels ();
void printDataCache ();
void printIntegerRegisters ();
void printFPRegisters ();

#endif /* GLOBAL_TOMASULOSIMULATOR_H_ */

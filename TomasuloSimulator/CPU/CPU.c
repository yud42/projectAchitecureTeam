/*
 * CPU.c
 *
 *  Created on: Oct 3, 2015
 *      Author: DebashisGanguly
 */

# include "../Global/TomasuloSimulator.h"

int getHashCodeFromPCHash (void *PCHash);

/**
 * This method initializes CPU data structures and all its data members
 */
void initializeCPU () {
	int i;

	cpu = (CPU *) malloc (sizeof(CPU));

	cpu -> cycle = 0;
	cpu -> PC = instructionCacheBaseAddress;

	 //initialize integer registers
	cpu -> integerRegisters = (INTReg **) malloc (sizeof(INTReg *) * numberOfIntRegisters);

	for (i = 0; i < numberOfIntRegisters; i++) {
		cpu -> integerRegisters [i] = (INTReg *) malloc (sizeof(INTReg));
		cpu -> integerRegisters [i] -> data = 0;
		cpu -> integerRegisters [i] -> intResult = 0;
 	}

	 //initialize floating point registers
	cpu -> floatingPointRegisters = (FPReg **) malloc (sizeof(FPReg *) * numberOfFPRegisters);

	for (i = 0; i < numberOfFPRegisters; i++) {
		cpu -> floatingPointRegisters [i] = (FPReg *) malloc (sizeof(FPReg));
		cpu -> floatingPointRegisters [i] -> data = 0.0;
		cpu -> floatingPointRegisters [i] -> fpResult = 0;
 	}

	cpu -> intDestReg = 0;
	cpu -> intResult = 0;

	cpu -> fpDestReg = 0;
	cpu -> fpResult = 0; 
}

/**
 * Method that simulates the looping cycle-wise
 * @return: When the simulator stops
 */
int runClockCycle () {
	cpu -> cycle++; //increment cycle counter

	printf ("\nCycle %d\n", cpu -> cycle);


	if (cpu -> PC >= (instructionCacheBaseAddress + (cacheLineSize * numberOfInstruction))) { //check whether PC exceeds last instruction in cache
                printf ("All instructions finished...\n");
		return 0; 
        } 
	

        void *addrPtr = malloc(sizeof(int));
	*((int*)addrPtr) = cpu -> PC;

        DictionaryEntry *currentInstruction = getValueChainByDictionaryKey (instructionCache, addrPtr);

        char *instruction_str = (char *) malloc (sizeof(char) * MAX_LINE);
        strcpy (instruction_str, ((char*)currentInstruction -> value -> value));

        printf ("Fetched %d:%s\n", cpu -> PC, instruction_str);

	Instruction *instruction;

        char *token = (char *) malloc (sizeof(char) * MAX_LINE);

        OpCode op; 

        int rd; 
        int rs; 
        int rt; 

        int rsValue;
        int rtValue;

        int fd; 
        int fs; 
        int ft; 

        double fsValue;
        double ftValue;

        int immediate;

        int target;
        

	op = NOOP, rd = -1, rs = -1, rt = -1, rsValue = -1, rtValue = -1, fd = -1, fs = -1, ft = -1, fsValue = -1, ftValue = -1, immediate = 0, target = 0;

	token = (char *) malloc (sizeof(char) * MAX_LINE);

	strcpy (token, instruction_str);

	token = strtok(token, " ,()\t\n");

	if(strcmp(token, "AND") == 0) {
		op = AND;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "ANDI") == 0) {
		op = ANDI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "OR") == 0) {
		op = OR;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "ORI") == 0) {
		op = ORI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "SLT") == 0) {
		op = SLT;
		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "SLTI") == 0) {
		op = SLTI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);
	} else if(strcmp(token, "DADD") == 0) {
		op = DADD;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "DADDI") == 0) {
		op = DADDI;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");

		immediate = atoi(token);
	} else if(strcmp(token, "DSUB") == 0) {
		op = DSUB;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "DMUL") == 0) {
		op = DMUL;

		token = strtok(NULL, " ,()RF\t\n");
		rd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);
	} else if(strcmp(token, "LD") == 0) {
		op = LD;

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "SD") == 0) {
		op = SD;

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "L.D") == 0) {
		op = L_D;

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "S.D") == 0) {
		op = S_D;

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		immediate = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);
	} else if(strcmp(token, "ADD.D") == 0) {
		op = ADD_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "SUB.D") == 0) {
		op = SUB_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "MUL.D") == 0) {
		op = MUL_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "DIV.D") == 0) {
		op = DIV_D;

		token = strtok(NULL, " ,()RF\t\n");
		fd = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		fs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		ft = atoi(token);
	} else if(strcmp(token, "BEQZ") == 0) {
		op = BEQZ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BNEZ") == 0) {
		op = BNEZ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BEQ") == 0) {
		op = BEQ;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else if(strcmp(token, "BNE") == 0) {
		op = BNE;

		token = strtok(NULL, " ,()RF\t\n");
		rs = atoi(token);

		token = strtok(NULL, " ,()RF\t\n");
		rt = atoi(token);

		token = strtok(NULL, " ,()\t\n");
	} else {
		printf("Invalid instruction %s...\n", instruction_str);
		exit (EXIT_FAILURE);
	}

	if (op == BEQZ || op == BNEZ || op == BEQ || op == BNE) {
		DictionaryEntry *codeLabel = getValueChainByDictionaryKey (codeLabels, (void *) token);

		if (codeLabel == NULL) {
			printf("Invalid code label cannot be resolved...\n");
			exit (EXIT_FAILURE);
		} else {
			target = *((int*)codeLabel -> value -> value);
		}
	}

	instruction = (Instruction *) malloc (sizeof(Instruction));

	instruction -> op = op;

	instruction -> rd = rd;
	instruction -> rs = rs;
	instruction -> rt = rt;

	instruction -> rsValue = rsValue;
	instruction -> rtValue = rtValue;

	instruction -> fd = fd;
	instruction -> fs = fs;
	instruction -> ft = ft;

	instruction -> fsValue = fsValue;
	instruction -> ftValue = ftValue;

	instruction -> immediate = immediate;

	instruction -> target = target;

	printf("Decoded %d:%s -> %s, rd=%d, rs=%d, rt=%d, fd=%d, fs=%d, ft=%d, immediate=%d, target=%d\n", cpu -> PC, instruction_str,
		 getOpcodeString ((int) op), rd, rs, rt, fd, fs, ft, immediate, target);

	void *valuePtr = malloc(sizeof(double));

	DictionaryEntry *dataCacheElement;

	switch (instruction -> op) {
			case ANDI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data & instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;	
			case AND:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data & cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case ORI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data | instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case OR:                                                                                                                                                         
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data | cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case SLTI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data < instruction -> immediate ? 1 : 0;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case SLT:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data < cpu -> integerRegisters [instruction -> rt] -> data ? 1 : 0;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case DADDI:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
				break;
                        case DADD:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data + cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case DSUB:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data - cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
			case DMUL:
				cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data * cpu -> integerRegisters [instruction -> rt] -> data;
				cpu -> integerRegisters [instruction -> rd] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case ADD_D:
                                cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data + cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case SUB_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data - cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case MUL_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data * cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case DIV_D:
				cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> fs] -> data / cpu -> floatingPointRegisters [instruction -> ft] -> data;
				cpu -> floatingPointRegisters [instruction -> fd] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case L_D:
				cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;

				*((int*)addrPtr) = cpu -> memoryAddress;
				dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);

				valuePtr = dataCacheElement -> value -> value;
				cpu -> fpResult = *((double*)valuePtr);

				cpu -> floatingPointRegisters [instruction -> ft] -> data = cpu -> fpResult;
				cpu -> PC = cpu -> PC + 4;
				break;
			case LD:
				cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;

				*((int*)addrPtr) = cpu -> memoryAddress;
				dataCacheElement = getValueChainByDictionaryKey (dataCache, addrPtr);

				valuePtr = dataCacheElement -> value -> value;
				cpu -> intResult =  (int) *((double*)valuePtr);

				cpu -> integerRegisters [instruction -> rt] -> data = cpu -> intResult;
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case SD:
                                cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data + instruction -> immediate;                                                                   
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rt] -> data ;

				*((int*)addrPtr) = cpu -> memoryAddress;
				removeDictionaryEntriesByKey (dataCache, addrPtr);

				*((double*)valuePtr) = cpu -> intResult;
				addDictionaryEntry (dataCache, addrPtr, valuePtr);
				cpu -> PC = cpu -> PC + 4;
                                break;
                        case S_D:
                                cpu -> memoryAddress = cpu -> integerRegisters [instruction -> rs] -> data  + instruction -> immediate;
                                cpu -> fpResult = cpu -> floatingPointRegisters [instruction -> ft] -> data ;

				*((int*)addrPtr) = cpu -> memoryAddress;
                                removeDictionaryEntriesByKey (dataCache, addrPtr);

                                *((double*)valuePtr) = (double) cpu -> fpResult;
                                addDictionaryEntry (dataCache, addrPtr, valuePtr);
				cpu -> PC = cpu -> PC + 4;
                                break;
			case BNE:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data != cpu -> integerRegisters [instruction -> rt] -> data ? 0 : -1; 
				if (cpu -> intResult == 0) {
					cpu -> PC = instruction -> target;
				} else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BNEZ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data != 0 ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;                                                                                                                
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BEQ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data == cpu -> integerRegisters [instruction -> rt] -> data ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;                                                                                                                
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;
                        case BEQZ:
                                cpu -> intResult = cpu -> integerRegisters [instruction -> rs] -> data == 0 ? 0 : -1;
				if (cpu -> intResult == 0) {
                                        cpu -> PC = instruction -> target;                                                                                                                       
                                } else {
					cpu -> PC = cpu -> PC + 4;
				}
                                break;	
                        default:
                                break;
                }


	return 1;
}

/**
 * Helper method for BHT hash table to calculate hash value from PC
 * @param PCHash
 * @return
 */
int getHashCodeFromPCHash (void *PCHash) {
	return *((int*)PCHash);
}

/* LC-2K Instruction-level simulator */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMMEMORY 65536 /* maximum number of words in memory */
#define NUMREGS 8 /* number of machine registers */
#define MAXLINELENGTH 1000 
typedef struct stateStruct {
    int pc;
    int mem[NUMMEMORY];
    int reg[NUMREGS];
    int numMemory;
} stateType;

void printState(stateType *);
int convertNum(int num);
void loadInfo(int memNum, int *opcode, int *arg0, int *arg1, int *arg2);

void loadInfo(int memNum, int *opcode, int *arg0, int *arg1, int *arg2)
{
	*opcode = (memNum & (0b1111111111 << 22)) >> 22;
	*arg0 = (memNum & (0b111 << 19)) >> 19;
	*arg1 = (memNum & (0b111 << 16)) >> 16;
	*arg2 = convertNum(memNum & 0b1111111111111111);
}
	

int main(int argc, char *argv[])
{
    char line[MAXLINELENGTH];
    stateType state;
    FILE *filePtr;

    int opcode = 0, regA = 0, regB = 0, destReg = 0;
    int instructions = 0;

    if (argc != 2) {
        printf("error: usage: %s <machine-code file>\n", argv[0]);
        exit(1);
    }

    filePtr = fopen(argv[1], "r");
    if (filePtr == NULL) {
        printf("error: can't open file %s", argv[1]);
        perror("fopen");
        exit(1);
    }

    /* read in the entire machine-code file into memory */
    for (state.numMemory = 0; fgets(line, MAXLINELENGTH, filePtr) != NULL;
            state.numMemory++) {

        if (sscanf(line, "%d", state.mem+state.numMemory) != 1) {
            printf("error in reading address %d\n", state.numMemory);
            exit(1);
        }
        printf("memory[%d]=%d\n", state.numMemory, state.mem[state.numMemory]);
    }
    for(int i = 0; i < 8; i++)
    {
	    state.reg[i] = 0;
    }
    state.pc = 0;

    while(1)
    {
	    printState(&state);
	    loadInfo(state.mem[state.pc], &opcode, &regA, &regB, &destReg);
	    switch(opcode)
	    {
		    case 0:
			    state.reg[destReg] = state.reg[regA] + state.reg[regB];
			    break;
		    case 1:
			    state.reg[destReg] = ~(state.reg[regA] | state.reg[regB]);
			    break;
		    case 2:
			    state.reg[regB] = state.mem[state.reg[regA] + destReg];
			    break;
		    case 3:
			    state.mem[state.reg[regA] + destReg] = state.reg[regB];
			    break;
		    case 4:
			    if(state.reg[regA] == state.reg[regB])
			    {
				    state.pc += destReg;
			    }
			    break;
		    case 5:
			    state.reg[regB] = state.pc + 1;
			    state.pc = state.reg[regA] - 1;
			    break;
		    case 6:
			    state.pc++;
			    printf("machine halted\n");
			    printf("total of %d instructions executed\n", 1 + instructions);
			    printf("final state of machine:\n");
			    printState(&state);
			    return 0;
		    case 7:
			    break;
		    default:
			    printf("error: unrecognized opcode - %d\n",opcode);
			    exit(1);

	    }

	    state.pc++;
	    instructions++;
    }

		/* TODO: */
    return(0);
}

void printState(stateType *statePtr)
{
    int i;
    printf("\n@@@\nstate:\n");
    printf("\tpc %d\n", statePtr->pc);
    printf("\tmemory:\n");
    for (i = 0; i < statePtr->numMemory; i++) {
        printf("\t\tmem[ %d ] %d\n", i, statePtr->mem[i]);
    }
    printf("\tregisters:\n");
    for (i = 0; i < NUMREGS; i++) {
        printf("\t\treg[ %d ] %d\n", i, statePtr->reg[i]);
    }
    printf("end state\n");
}

int convertNum(int num)
{
	/* convert a 16-bit number into a 32-bit Linux integer */
	if (num & (1 << 15)) {
		num -= (1 << 16);
	}
	return (num);
}

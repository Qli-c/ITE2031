/* Assembler code fragment for LC-2K */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINELENGTH 1000

int readAndParse(FILE *, char *, char *, char *, char *, char *);
int isNumber(char *);
int findList(FILE *ptr, char *labelarr);

int findList(FILE *ptr, char *labelarr)
{
	int address, cnt, is_found;
	address = 0;
	cnt = 0;
	is_found = 0;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];
	rewind(ptr);
	while(readAndParse(ptr, label, opcode, arg0, arg1, arg2))
	{
		if(!strcmp(label, labelarr))
		{
			address = cnt;
			is_found = 1;
		}
		cnt++;
	}
	if(is_found == 1)
	{
		return address;
	}
	else
	{
		printf("error: undefinded label\n");
		exit(1);
	}
}

int main(int argc, char *argv[]) 
{
	char *inFileString, *outFileString;
	FILE *inFilePtr, *outFilePtr, *inFileSearch;
	char label[MAXLINELENGTH], opcode[MAXLINELENGTH], arg0[MAXLINELENGTH], 
			 arg1[MAXLINELENGTH], arg2[MAXLINELENGTH];

	if (argc != 3) {
		printf("error: usage: %s <assembly-code-file> <machine-code-file>\n", argv[0]);
		exit(1);
	}

	inFileString = argv[1];
	outFileString = argv[2];

	inFilePtr = fopen(inFileString, "r");
	if (inFilePtr == NULL) {
		printf("error in opening %s\n", inFileString);
		exit(1);
	}
	outFilePtr = fopen(outFileString, "w");
	if (outFilePtr == NULL) {
		printf("error in opening %s\n", outFileString);
		exit(1);
	}

	inFileSearch = fopen(inFileString, "r");
	
	/* here is an example for how to use readAndParse to read a line from
		 inFilePtr */
	while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
	{	
		if(strlen(label) > 6 || isNumber(label))
		{
			printf("error: undefined label - %s\n", label);
			exit(1);
		}
		if(strcmp(label, ""))
		{
			int cnt = 0;
			char now[1000];
			strcpy(now, label);
			while(readAndParse(inFileSearch, label, opcode, arg0, arg1, arg2))
			{
				if(strcmp(now, label) == 0)
				{
					cnt++;
				}
			}
			if(cnt > 1)
			{
				printf("error: duplicate definition of labels\n");
				exit(1);
			}
			rewind(inFileSearch);
		}
	}

	int addresscounter = 0;
	//if (!readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2)) {
		/* reached end of file */
	//}

	/* TODO: Phase-1 label calculation */

	/* this is how to rewind the file ptr so that you start reading from the
		 beginning of the file */
	rewind(inFilePtr);
	rewind(inFileSearch);


	while(readAndParse(inFilePtr, label, opcode, arg0, arg1, arg2))
	{
		int instruction = 0, regA = 0, regB = 0, destReg = 0;
	/* TODO: Phase-2 generate machine codes to outfile */

	/* after doing a readAndParse, you may want to do the following to test the
		 opcode */
		if (!strcmp(opcode, "add")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 0;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}
			if(isNumber(arg2) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}
			sscanf(arg2, "%d", &destReg);
			if(destReg < 0 || destReg > 7)
			{
				printf("error: registers outside the range - %d\n",destReg);
				exit(1);
			}
		}
		else if (!strcmp(opcode, "nor")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 1;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}
			if(isNumber(arg2) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}
			sscanf(arg2, "%d", &destReg);
			if(destReg < 0 || destReg > 7)
			{
				printf("error: registers outside the range - %d\n",destReg);
				exit(1);
			}
		}
		else if (!strcmp(opcode, "lw")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 2;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}

			if(isNumber(arg2) == 1)
			{
				sscanf(arg2, "%d", &destReg);
			}
			else
			{
				destReg = findList(inFileSearch, arg2);
			}
		}
		else if (!strcmp(opcode, "sw")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 3;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}

			if(isNumber(arg2) == 1)
			{
				sscanf(arg2, "%d", &destReg);
			}
			else
			{
				destReg = findList(inFileSearch, arg2);
			}
		}
		else if (!strcmp(opcode, "beq")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 4;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}

			if(isNumber(arg2) == 1)
			{
				sscanf(arg2, "%d", &destReg);
			}
			else
			{
				destReg = findList(inFileSearch, arg2) - addresscounter - 1;
			}
		}
		else if (!strcmp(opcode, "jalr")) {
			/* do whatever you need to do for opcode "add" */
			instruction = 5;
			if(isNumber(arg0) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}	
			if(isNumber(arg1) == 0)
			{
				printf("error: non-integer register arguments\n");
				exit(1);
			}

			sscanf(arg0, "%d", &regA);
			if(regA < 0 || regA > 7)
			{
				printf("error: registers outside the range - %d\n",regA);
				exit(1);
			}
			sscanf(arg1, "%d", &regB);
			if(regB < 0 || regB > 7)
			{
				printf("error: registers outside the range - %d\n",regB);
				exit(1);
			}

		}

		else if(!strcmp(opcode, "halt")){
			instruction = 6;
		}

		else if(!strcmp(opcode, "noop")){
			instruction = 7;
		}

		else if(!strcmp(opcode, ".fill")){
			if(isNumber(arg0))
			{
				sscanf(arg0, "%d", &regA);
				fprintf(outFilePtr, "%d\n", regA);
				addresscounter++;
				continue;
			}
			else
			{
				int num1 = findList(inFileSearch, arg0);
				fprintf(outFilePtr, "%d\n", num1);
				addresscounter++;
				continue;
			}
		}

		else
		{
			printf("error: unrecognized opcode - %s\n", opcode);
			exit(1);
		}
		
		if(destReg < -32768 || destReg > 32767)
		{
			printf("error: offsetField doesn't fit in 16 bits - %d\n", destReg);
			exit(1);
		}

		if(destReg < 0)
		{
			destReg += 65536;
		}
		int output = (instruction << 22) + (regA << 19) + (regB << 16) + destReg;
		fprintf(outFilePtr, "%d\n", output);
		addresscounter++;
	}








	if (inFilePtr) {
		fclose(inFilePtr);
	}
	if (outFilePtr) {
		fclose(outFilePtr);
	}
	if(inFileSearch) {
		fclose(inFileSearch);
	}
	return(0);
}

/*
 * Read and parse a line of the assembly-language file.  Fields are returned
 * in label, opcode, arg0, arg1, arg2 (these strings must have memory already
 * allocated to them).
 *
 * Return values:
 *     0 if reached end of file
 *     1 if all went well
 *
 * exit(1) if line is too long.
 */
int readAndParse(FILE *inFilePtr, char *label, char *opcode, char *arg0,
		char *arg1, char *arg2)
{
	char line[MAXLINELENGTH];
	char *ptr = line;

	/* delete prior values */
	label[0] = opcode[0] = arg0[0] = arg1[0] = arg2[0] = '\0';

	/* read the line from the assembly-language file */
	if (fgets(line, MAXLINELENGTH, inFilePtr) == NULL) {
		/* reached end of file */
		return(0);
	}

	/* check for line too long (by looking for a \n) */
	if (strchr(line, '\n') == NULL) {
		/* line too long */
		printf("error: line too long\n");
		exit(1);
	}

	/* is there a label? */
	ptr = line;
	if (sscanf(ptr, "%[^\t\n\r ]", label)) {
		/* successfully read label; advance pointer over the label */
		ptr += strlen(label);
	}

	/*
	 * Parse the rest of the line.  Would be nice to have real regular
	 * expressions, but scanf will suffice.
	 */
	sscanf(ptr, "%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]%*[\t\n\r ]%"
			"[^\t\n\r ]%*[\t\n\r ]%[^\t\n\r ]", opcode, arg0, arg1, arg2);
	return(1);
}

int isNumber(char *string)
{
	/* return 1 if string is a number */
	int i;
	return( (sscanf(string, "%d", &i)) == 1);
}


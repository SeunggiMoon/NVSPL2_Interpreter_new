//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// main.cpp - ¡÷ ∑Á∆æ
//

#include "analyze.h"
#include "execute.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage : nvspl2 <filename> <options...>\n");
		return 0;
	}
	FILE* in = fopen(argv[1], "rt");

	if (in == NULL)
	{
		printf("error : wrong filename\n");
		return 0;
	}

	int retValue;
	Code exeCode;
	bool ifExit = false;

	printf("\n");
	printf("NVSPL2 Interpreter v7\n(c) 2015~2020 Naissoft. All rights reserved.\n\n");

	printf("Analyzing...\n");

	initCode(&exeCode);

	// analyze code

	analyzeCode(in, &exeCode);
	fclose(in);

	// print intermediate code - v8 feature!

	// printf("\n%s\n\n", &exeCode.str[0]);

	printf("Executing...\n\n");
	DWORD t = GetTickCount();

	// execute code

	do
	{
		retValue = runCode(&exeCode);

		switch (retValue)
		{
		case retVal_exit:
			ifExit = true;
			break;
		case retVal_success:
			break;
		case retVal_overflow:
			printf("Runtime error : Memory overflow\n");
			ifExit = true;
			break;
		case retVal_underflow:
			printf("Runtime error : Memory underflow\n");
			ifExit = true;
			break;
		}
		exeCode.str_idx++;
	} while (!ifExit);

	DWORD diff = (GetTickCount() - t);
	printf("\nExecution finished with return value %d (%.3lfs)\n", retValue, (double)diff / 1000);

	return 0;
}
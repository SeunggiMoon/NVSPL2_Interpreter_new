//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// main.cpp - ¡÷ ∑Á∆æ
//

#include "analyze.h"
#include <Windows.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage : nvspl2 <filename>\n");
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

	printf("\n");
	printf("NVSPL2 Interpreter v7\n(c) 2015~2020 Naissoft. All rights reserved.\n\n");

	printf("Analyzing...\n");

	initCode(&exeCode);

	// analyze code
	// 
	// analyzeCode(in);
	// fclose(in);

	printf("Executing...\n\n");

	DWORD t = GetTickCount();
	
	// run code
	// 
	// retValue = runCode(code);
	// 
	// switch (retValue)
	// {
	//     ...

	DWORD diff = (GetTickCount() - t);
	printf("\n\nFinished! (%.2lfs)\n", (double)diff / 1000);

	return 0;
}
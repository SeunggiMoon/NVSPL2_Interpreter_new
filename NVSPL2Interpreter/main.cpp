// 
// MIT License
// 
// Copyright(c) 2020 Seunggi Moon
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// NVSPL2 Interpreter v8
// (c) 2015~2020 Naissoft. All rights reserved.
//
// main.cpp - 주 루틴
//

#include "analyze.h"
#include "execute.h"
#include <Windows.h>

// options

bool optPrnInt = false;
bool optSavInt = false;
bool optSavOut = false;
bool optSavLog = false;
bool optRunSbs = false;
bool optDbgMod = false;

void getArgs(int argc, char* argv[]);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("usage : nvspl2 <filename> <options...>\n");
		return 0;
	}
	getArgs(argc, argv);

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
	printf("NVSPL2 Interpreter v8\n(c) 2015~2020 Naissoft. All rights reserved.\n\n");

	printf("Analyzing...\n");

	initCode(&exeCode);

	// analyze code

	analyzeCode(in, &exeCode);
	fclose(in);

	// print intermediate code - v8 feature!

	if (optPrnInt) printf("\n%s\n\n", &exeCode.str[0]);

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

void getArgs(int argc, char* argv[])
{
	for (int i = 2; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'i':
				optPrnInt = true;
				break;
			case 'c':
				optSavInt = true;
				break;
			case 'o':
				optSavOut = true;
				break;
			case 'l':
				optSavLog = true;
				break;
			case 's':
				if (!optDbgMod) optRunSbs = true;
				break;
			case 'd':
				optDbgMod = true;
				optRunSbs = false; // -s 옵션을 무시합니다.
				break;
			default:
				break;
			}
		}
	}
}
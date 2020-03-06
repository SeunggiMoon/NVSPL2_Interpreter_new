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

// log and output files

FILE* logFile;
FILE* output;

// messages

char* msgUsage = "usage : nvspl2 <filename> <options...>\n";
char* msgWrongFile = "error : wrong filename\n";
char* msgProgInfo = "\nNVSPL2 Interpreter v8\n(c) 2015~2020 Naissoft. All rights reserved.\n\n";
char* msgIntFail = "error : failed to create intermediate code file\n";
char* msgOutFail = "error : failed to create output file\n";
char* msgLogFail = "error : failed to create log file\n";
char* msgFinished = "\nExecution finished with return value %d (%.3lfs)\n";

char* msgRunErrOverflow = "Runtime error : Memory overflow\n";
char* msgRunErrUnderflow = "Runtime error : Memory underflow\n";

void getArgs(int argc, char* argv[]);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf(msgUsage);
		return 0;
	}
	getArgs(argc, argv);

	FILE* in = fopen(argv[1], "rt");
	if (in == NULL)
	{
		printf(msgWrongFile);
		return 0;
	}

	int retValue;
	Code exeCode;
	bool ifExit = false;

	printf(msgProgInfo);
	printf("Analyzing...\n");

	initCode(&exeCode);

	// analyze code

	analyzeCode(in, &exeCode);
	fclose(in);

	// print intermediate code

	if (optPrnInt)
	{
		printf("Printing intermediate code...\n");
		printf("\n%s\n\n", &exeCode.str[0]);
	}

	// save intermediate code
	
	if (optSavInt)
	{
		printf("Saving intermediate code...\n");

		std::string fName = argv[1];
		std::string fSuffix = "-intermediate.nvs";
		fName += fSuffix;

		FILE* intCode = fopen(fName.c_str(), "wt");
		if (intCode == NULL)
		{
			printf(msgIntFail);
			return 0;
		}
		fprintf(intCode, "%s", &exeCode.str[0]);
		fclose(intCode);
	}

	if (optSavOut)
	{
		std::string fName = argv[1];
		std::string fSuffix = "-output.txt";
		fName += fSuffix;

		output = fopen(fName.c_str(), "wt");
		if (output == NULL)
		{
			printf(msgOutFail);
			return 0;
		}
	}

	if (optSavLog)
	{
		std::string fName = argv[1];
		std::string fSuffix = ".log";
		fName += fSuffix;

		logFile = fopen(fName.c_str(), "wt");
		if (logFile == NULL)
		{
			printf(msgLogFail);
			return 0;
		}
	}

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
			printf(msgRunErrOverflow);
			if (optSavLog) fprintf(logFile, msgRunErrOverflow);
			ifExit = true;
			break;
		case retVal_underflow:
			printf(msgRunErrUnderflow);
			if (optSavLog) fprintf(logFile, msgRunErrUnderflow);
			ifExit = true;
			break;
		}
		exeCode.str_idx++;
	} while (!ifExit);

	DWORD diff = (GetTickCount() - t);
	printf(msgFinished, retValue, (double)diff / 1000);
	if (optSavLog) fprintf(logFile, msgFinished, retValue, (double)diff / 1000);

	if (optSavOut && output != NULL) fclose(output);
	if (optSavLog && logFile != NULL) fclose(logFile);

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
				if (!optDbgMod) optRunSbs = true; // -d 옵션이 비활성화된 상태일 때 -s 옵션을 활성화합니다.
				break;
			case 'd':
				optDbgMod = true;
				optRunSbs = false; // -s 옵션을 비활성화합니다.
				break;
			default:
				break;
			}
		}
	}
}
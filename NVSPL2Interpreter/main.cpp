#include "analyze.h"
#include <Windows.h>

void init();

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("usage : nvspl2 <filename>\n");
		return 0;
	}
	in = fopen(argv[1], "rt");

	if (in == NULL)
	{
		printf("error : Wrong file name!\n");
		return 0;
	}

	printf("\n");
	printf("Naissoft Very Simple Programming Language Interpreter v6\n(C) 2015~2016 Naissoft.\n\n");

	printf("Analyzing...\n");
	analyzeCode();
	fclose(in);

	printf("Executing...\n\n");

	tmp = fopen("nvspl2.tmp", "rt");
	if (tmp == NULL)
	{
		printf("error : missing file!\n");
		return 0;
	}

	DWORD t = GetTickCount();
	
	while (true)
	{
		fscanf(tmp, "%c", &b);
		runCode();
		if (ifexit) break;
	}

	DWORD diff = (GetTickCount() - t);
	printf("\n\nFinished! (%.2lfs)\n", (double)diff / 1000);
	return 0;
}

void init()
{
	n = 0.0;
	cnt = depth = cdepth = 0;
	b = '\0';
	comment = ifexit = false;
}
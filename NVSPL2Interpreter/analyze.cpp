//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// analyze.cpp - 코드 분석 및 중간 코드 생성
//

#include "analyze.h"

int cnt, depth, cdepth;
double var[1024] = { 0.0 }, n;
char name[512], b;

bool comment;

void analyzeCode(FILE *fp, Code *code)
{
	do
	{
		fscanf(fp, "%c", &b);
		if (b == '#') comment = true;
		if (b == '\n') comment = false;

		if (!comment)
		{
			if (b != ' ' && b != '\n')
				fprintf(tmp, "%c", b);
		}
	} while (b != 'Q');
}
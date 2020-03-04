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
FILE *in, *log, *tmp;

bool comment;

void analyzeCode(FILE *fp)
{
	int p_cnt, m_cnt;

	tmp = fopen("nvspl2.tmp", "wt");
	do
	{
		fscanf(in, "%c", &b);
		if (b == '#') comment = true;
		if (b == '\n') comment = false;

		if (!comment)
		{
			if (b != ' ' && b != '\n')
				fprintf(tmp, "%c", b);
		}
	} while (b != 'Q');

	fclose(tmp);
}
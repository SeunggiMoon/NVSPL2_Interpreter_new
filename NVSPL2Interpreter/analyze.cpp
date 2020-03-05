//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// analyze.cpp - �ڵ� �м� �� �߰� �ڵ� ����
//

#include "analyze.h"

void analyzeCode(FILE *fp, Code *code)
{
	bool comment = false;
	char c;
	do
	{
		fscanf(fp, "%c", &c);
		if (c == '#') comment = true;
		if (c == '\n') comment = false;

		if (!comment && c != ' ' && c != '\n') addChar(code, c);

	} while (c != 'Q');
	addChar(code, '\0');
}
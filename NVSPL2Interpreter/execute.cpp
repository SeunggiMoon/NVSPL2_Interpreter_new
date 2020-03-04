//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// execute.cpp - 코드 실행부
//

#include "execute.h"

int runCode()
{
	switch (b)
	{
	case 'F':
		cnt++;
		if (cnt >= MAX_MEM)
		{
			printf("runtime error : memory overflow\n");
			ifexit = true;
			return;
		}
		break;
	case 'B':
		cnt--;
		if (cnt < 0)
		{
			printf("runtime error : inaccessible area\n");
			ifexit = true;
			return;
		}
		break;
	case '+':
		var[cnt] += 1.0;
		break;
	case '-':
		var[cnt] -= 1.0;
		break;
	case ',':
		fscanf(in, "%lf", &n);
		var[cnt] += n;
		break;
	case 'I':
		printf("%d", (int)(var[cnt]));
		break;
	case 'C':
		printf("%c", (int)(var[cnt]));
		break;
	case 'R':
		printf("%f", var[cnt]);
		break;
	case 'S':
		printf(" ");
		break;
	case 'E':
		printf("\n");
		break;
	case 'O':
		var[cnt] = 0.0;
		break;
	case ':':
		depth++;
		cdepth++;
		break;
	case ';':
		if (var[cnt] != 0.0)
		{
			while (true)
			{
				fseek(in, -2, SEEK_CUR);
				fscanf(in, "%c", &b);
				if (b == '\n') fseek(in, -1, SEEK_CUR);
				if (b == ':' && cdepth == depth) break;
				if (b == ';') cdepth++;
				if (b == ':') cdepth--;
			}
			fseek(in, -1, SEEK_CUR);
		}
		break;
	case 'Q':
		ifexit = true;
		return;
		break;
	default:
		break;
	}
}
#include "analyze.h"

int cnt, depth, cdepth;
double var[1024] = { 0.0 }, n;
char name[512], b;
FILE *in, *log, *tmp;

bool comment, ifexit;

void analyzeCode()
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

void runCode()
{
	switch (b)
	{
	case 'F':
		cnt++;
		if (cnt >= MAX_MEM)
		{
			printf("error : memory overflow");
			ifexit = true;
			return;
		}
		break;
	case 'B':
		cnt--;
		if (cnt < 0)
		{
			printf("error : can't access this area.");
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
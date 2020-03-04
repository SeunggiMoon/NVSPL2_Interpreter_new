//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// analyze.h
//

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MEM 1024

extern int cnt, depth, cdepth;
extern double n;
extern char name[512], b;
extern FILE *in, *log, *tmp;

extern bool comment, ifexit;

void analyzeCode();
void runCode();
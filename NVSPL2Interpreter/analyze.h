//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// analyze.h
//

#pragma once

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#include "code.h"

#define MAX_MEM 1024

extern int cnt, depth, cdepth;
extern double n;
extern char name[512], b;

extern bool comment, ifexit;

void analyzeCode(FILE *fp, Code *code);
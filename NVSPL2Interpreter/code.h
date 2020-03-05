//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// code.h
//

#pragma once

#define MAX_IDX 1024

#include <vector>

struct Code
{
	std::vector<char> str;

	double arr[MAX_IDX] = { 0 };
	double input;

	int arr_idx;
	int str_idx;

	int depth;
	int cdepth;
};

void initCode(Code *code);

void addChar(Code* code, char ch);
//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// code.h
//

#pragma once

#include <vector>

struct Code
{
	std::vector<char> str;
	int arr_idx;
	int str_idx;
};

void initCode(Code *code);

void addChar(Code* code, char ch);
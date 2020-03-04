//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// code.h
//

#pragma once

struct Code
{
	char* str;
	int arr_idx;
	int str_idx;
};

void initCode(Code *code, int len);

void addChar(Code* code, char ch);
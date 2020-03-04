//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// code.cpp
//

#include "code.h"

void initCode(Code* code)
{
	code->arr_idx = 0;
	code->str_idx = 0;
}

void addChar(Code* code, char ch)
{
	code->str.push_back(ch);
}
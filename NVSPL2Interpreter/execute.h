//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// execute.h
//

#pragma once

constexpr int retVal_exit = 0;
constexpr int retVal_success = 1;
constexpr int retVal_overflow = -1;
constexpr int retVal_underflow = -2;

#include <string>

#include "code.h"

int runCode(Code *code);
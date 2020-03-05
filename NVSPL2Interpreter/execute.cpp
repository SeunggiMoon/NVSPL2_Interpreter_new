//
// NVSPL2 Interpreter v7
// (c) 2015~2020 Naissoft. All rights reserved.
//
// execute.cpp - 코드 실행부
//

#include "execute.h"

int runCode(Code *code)
{
	std::string tmp1;
	const char* tmp2;

	switch (code->str[code->str_idx])
	{
	case 'F':
	case 'f':
		code->arr_idx++;
		if (code->arr_idx >= MAX_IDX)
			return retVal_overflow;
		break;
	case 'B':
	case 'b':
		code->arr_idx--;
		if (code->arr_idx < 0)
			return retVal_underflow;
		break;
	case '+':
		code->arr[code->arr_idx] += 1.0;
		break;
	case '-':
		code->arr[code->arr_idx] -= 1.0;
		break;
	case ',':
		tmp1 = std::string(code->str.begin() + code->str_idx + 1, code->str.end()); // 입력받을 수가 처음에 오도록 string 생성
		tmp2 = tmp1.c_str();
		sscanf(tmp2, "%lf", &code->input);
		code->arr[code->arr_idx] += code->input;
		code->str_idx++; // 음수에 붙어 있는 마이너스 기호가 명령어로 인식되는 것을 막기 위함
		break;
	case 'I':
	case 'i':
		printf("%d", (int)(code->arr[code->arr_idx]));
		break;
	case 'C':
	case 'c':
		printf("%c", (int)(code->arr[code->arr_idx]));
		break;
	case 'R':
	case 'r':
		printf("%f", code->arr[code->arr_idx]);
		break;
	case 'S':
	case 's':
		printf(" ");
		break;
	case 'E':
	case 'e':
		printf("\n");
		break;
	case 'O':
	case 'o':
		code->arr[code->arr_idx] = 0.0;
		break;
	case ':':
		code->depth++;
		code->cdepth++;
		break;
	case ';':
		if (code->arr[code->arr_idx] != 0.0)
		{
			while (true)
			{
				code->str_idx--;
				if (code->str[code->str_idx] == ':' && code->cdepth == code->depth)
					break;
				if (code->str[code->str_idx] == ';') code->cdepth++;
				if (code->str[code->str_idx] == ':') code->cdepth--;
			}
		}
		else
		{
			code->depth--;
			code->cdepth--;
		}
		break;
	case 'Q':
	case 'q':
		return retVal_exit;
		break;
	default:
		break;
	}
	return retVal_success;
}
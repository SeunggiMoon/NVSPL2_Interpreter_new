// 
// MIT License
// 
// Copyright(c) 2020 Seunggi Moon
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// NVSPL2 Interpreter v8
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
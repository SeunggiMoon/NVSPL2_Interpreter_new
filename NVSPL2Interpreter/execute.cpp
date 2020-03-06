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

std::string instList = "FfBb+-,IiCcRrSsEeOoQq";
std::string::size_type n;

std::string tmp1 = "";
const char* tmp2 = "";

int runCode(Code *code)
{
	char inst = code->str[code->str_idx];

	if (optSavLog)
	{
		n = instList.find(inst);
		if (n != std::string::npos) fprintf(logFile, "%c", inst);
	}

	switch (inst)
	{
	case 'F':
	case 'f':
		code->arr_idx++;
		if (code->arr_idx >= MAX_IDX)
		{
			if (optSavLog) fprintf(logFile, "(!)\n");
			return retVal_overflow;
		}
		break;
	case 'B':
	case 'b':
		code->arr_idx--;
		if (code->arr_idx < 0)
		{
			if (optSavLog) fprintf(logFile, "(!)\n");
			return retVal_underflow;
		}
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
		if (optSavLog) fprintf(logFile, "%lf", code->input);
		break;
	case 'I':
	case 'i':
		printf("%d", (int)(code->arr[code->arr_idx]));
		if (optSavOut) fprintf(output, "%d", (int)(code->arr[code->arr_idx]));
		break;
	case 'C':
	case 'c':
		printf("%c", (int)(code->arr[code->arr_idx]));
		if (optSavOut) fprintf(output, "%c", (int)(code->arr[code->arr_idx]));
		break;
	case 'R':
	case 'r':
		printf("%f", code->arr[code->arr_idx]);
		if (optSavOut) fprintf(output, "%f", code->arr[code->arr_idx]);
		break;
	case 'S':
	case 's':
		printf(" ");
		if (optSavOut) fprintf(output, " ");
		break;
	case 'E':
	case 'e':
		printf("\n");
		if (optSavOut) fprintf(output, "\n");
		break;
	case 'O':
	case 'o':
		code->arr[code->arr_idx] = 0.0;
		break;
	case ':':
		code->depth++;
		code->cdepth++;
		if (optSavLog)
		{
			fputc('\n', logFile);
			for (int i = 0; i < (code->depth - 1) * 4; i++) fputc(' ', logFile); // indent 구현
			fprintf(logFile, "{\n");
			for (int i = 0; i < (code->depth) * 4; i++) fputc(' ', logFile);
		}
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
			if (optSavLog)
			{
				fputc('\n', logFile);
				for (int i = 0; i < (code->depth) * 4; i++) fputc(' ', logFile); // indent 구현
			}
		}
		else
		{
			code->depth--;
			code->cdepth--;
			if (optSavLog)
			{
				fputc('\n', logFile);
				for (int i = 0; i < (code->depth) * 4; i++) fputc(' ', logFile); // indent 구현
				fprintf(logFile, "}\n");
				for (int i = 0; i < (code->depth) * 4; i++) fputc(' ', logFile);
			}
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
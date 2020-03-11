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
// funcs.cpp - ���� ��� ������
//

#include "funcs.h"

void getArgs(int argc, char* argv[])
{
	for (int i = 2; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
			case 'i':
				optPrnInt = true;
				break;
			case 'c':
				optSavInt = true;
				break;
			case 'o':
				optSavOut = true;
				break;
			case 'l':
				optSavLog = true;
				break;
			case 's':
				if (!optDbgMod) optRunSbs = true; // -d �ɼ��� ��Ȱ��ȭ�� ������ �� -s �ɼ��� Ȱ��ȭ�մϴ�.
				break;
			case 'd':
				optDbgMod = true;
				optRunSbs = false; // -s �ɼ��� ��Ȱ��ȭ�մϴ�.
				break;
			default:
				break;
			}
		}
	}
}
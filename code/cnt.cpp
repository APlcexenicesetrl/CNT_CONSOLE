// CNT CONSOLE CODE(Core main code bootloader inside CNT console)
// APlcexenicesetrl CNT
// By TaimWay - Copyright (C) 2025
//
// The CNT CONSOLE CODE is the most important boot interpreter in the CNT CONSOLE.
// It allows the CNT CONSOLE to support CNT instructions and can manage and control the program well,
// and can be reproduced in the PC.
//
// Developed by TaimWay, the "Core main code bootloader inside CNT console" provides instruction support for the CNT family,
// and the instruction interpreter will be used publicly to some extent.
// The program is licensed by MIT and can be used, forwarded, and changed (twice) to "Core main code bootloader inside CNT console".
//
// MIT license, which allows you to use, view, and modify
//
//
/* APlcexenicesetrl CNT | CNT CONSOLE CODE - TaimWay*/
// File Name: CNT.CPP (MAIN.CPP)
//
// This header file declares some of the major functions, classes, templates, macro definitions, and so on in the project
// The document is created by TaimWay and only TaimWay has the right to modify the document.
// Copyright (C) MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.DAMAGES OR OTHER
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <bits/stdc++.h>
#include "winCode.cpp"
using namespace std;

int main(int argc, char **argv)
{
    cntLogs log;
    runningCode runningCode;
    winCode winCode;
    log.addObject("Start Programs", winCode.getUserName());
    vector <string> codeParameter;
    if (argc == 1){
        codeParameter.push_back("undefined");
        runningCode.runCode("help", codeParameter);
        log.addObject("Out help text", winCode.getUserName());
    }
    else
    {
        log.addObject("Access Information", winCode.getUserName());
        if(argc > 2) for (int i = 2; i < argc; ++i) codeParameter.push_back(argv[i]);
        else codeParameter.push_back("undefined");
        log.addObject("Send Information", winCode.getUserName());
        runningCode.runCode(argv[1], codeParameter);
    }
    log.addObject("exit Program", winCode.getUserName());
    return 0;
}
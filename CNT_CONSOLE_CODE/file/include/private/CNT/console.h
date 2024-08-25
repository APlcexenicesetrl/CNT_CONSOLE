#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <map>
#include "windows.h"

// Class
class console
{
private:
    bool debugSwitchValue_STAR = false;
    int IndentBlockNumber = 4;
    std::map<std::string, int> consoleCountMap;
    std::vector<std::string> consoleCountList;
    std::vector<std::string> groupIndentStack;
    std::vector<std::string> timeNameList;

    std::string getTimeText()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm = *std::localtime(&now_time_t);
        std::ostringstream timeStream;
        timeStream << std::put_time(&now_tm, "%m/%d/%y %H:%M:%S");
        return timeStream.str();
    }
    std::string getLogOutText(const std::string &LogReferenceText, const std::string &logOutText)
    {
        return "[" + getTimeText() + "][" + LogReferenceText + "]: " + logOutText;
    }
    void winLog(std::string logText, std::vector<std::string> &returnList)
    {
        if (logText.empty())
        {
            winError("console.winLog", "Null Pointer reference", 0x02542);
            return;
        }
        std::string lineText = "";
        for (int i = 0; i < logText.size(); ++i)
        {
            if (logText[i] == '\n')
            {
                returnList.push_back(lineText);
                lineText = "";
            }
            else
            {
                lineText += logText[i];
            }
        }
        if (!lineText.empty())
        {
            returnList.push_back(lineText);
        }
    }
    void debugTellSayState()
    {
        if (debugSwitchValue_STAR)
        {
            CustomLog("Debug mode is started.(--Console)");
        }
        else
        {
            CustomLog("Debug mode is turned off.(--Console)");
        }
    }
    std::string groupIndentLogOut(const bool noGroupIndentLogOut = false, const int add = 0)
    {
        if(noGroupIndentLogOut) return "";
        std::string line = "";
        int addNumber = groupIndentStack.size() + add;
        for(int i = 0 ; i < IndentBlockNumber*addNumber ; ++i)
            line += " ";
        return line;
    }

public:
    // ConsoleColor
    void SetConsoleColor(WORD color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
    void ResetConsoleColor()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    // Keyboard
    void waitKey(const char downKey)
    {
        while (1)
        {
            char key = getch();
            if (key == downKey)
            {
                return;
            }
        }
    }
    bool ifDownKey(const char downKey)
    {
        char key = getch();
        if (key == downKey)
        {
            return true;
        }
        return false;
    }
    // Log
    void winError(std::string SourceError, std::string ErrorDescription, int ErrorCode)
    {
        if (SourceError.empty())
        {
            SourceError = "???NULL???";
        }
        if (ErrorDescription.empty())
        {
            ErrorDescription = "???NULL???";
        }
        SetConsoleColor(FOREGROUND_RED);
        std::cout << "Error: an error has occurred in the \""
                  << SourceError
                  << "\" module, \nwhich manually refers to it to ensure information. \nFIX IT based on the information in the module.\nMessage: "
                  << ErrorDescription << "\nError Code: "
                  << std::to_string(ErrorCode) << std::endl
                  << "Please fix it according to the content" << std::endl;
        ResetConsoleColor();
    }
    void log(std::string logText)
    {
        std::vector<std::string> logTextList;
        winLog(logText, logTextList);
        for (int i = 0; i < logTextList.size(); ++i)
        {
            std::cout << groupIndentLogOut() << getLogOutText("Log", logTextList[i]) << std::endl;
        }
    }
    void warn(std::string logText)
    {
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
        std::vector<std::string> logTextList;
        winLog(logText, logTextList);
        for (int i = 0; i < logTextList.size(); ++i)
        {
            std::cout << groupIndentLogOut() << getLogOutText("Warn", logTextList[i]) << std::endl;
        }
        ResetConsoleColor();
    }
    void error(std::string logText)
    {
        std::vector<std::string> logTextList;
        winLog(logText, logTextList);
        SetConsoleColor(FOREGROUND_RED);
        for (int i = 0; i < logTextList.size(); ++i)
        {
            std::cout << groupIndentLogOut() << getLogOutText("Error", logTextList[i]) << std::endl;
        }
        ResetConsoleColor();
    }
    void info(std::string logText)
    {
        std::vector<std::string> logTextList;
        winLog(logText, logTextList);
        SetConsoleColor(FOREGROUND_BLUE);
        for (int i = 0; i < logTextList.size(); ++i)
        {
            std::cout << groupIndentLogOut() << getLogOutText("Info", logTextList[i]) << std::endl;
        }
        ResetConsoleColor();
    }
    void debug(std::string logText, bool thisStartDebug = false)
    {
        std::vector<std::string> logTextList;
        winLog(logText, logTextList);
        SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE);
        for (int i = 0; i < logTextList.size(); ++i)
        {
            if (debugSwitchValue_STAR || thisStartDebug)
            {
                std::cout << groupIndentLogOut() << getLogOutText("Debug", logTextList[i]) << std::endl;
            }
        }
        ResetConsoleColor();
    }
    void staticLog(const std::string logText, bool noGroupIndentLogOut = false)
    {
        std::cout << groupIndentLogOut(noGroupIndentLogOut) << logText << std::endl;
    }
    void CustomLog(const std::string logText, const std::string CustomReferenceText = ">", bool noGroupIndentLogOut = false)
    {
        std::cout << groupIndentLogOut(noGroupIndentLogOut) << CustomReferenceText << ' ' << logText << std::endl;
    }
    // ifdef
    static void assert(bool condition, const std::string &message = "true")
    {
        if (!condition)
        {
            console instance;
            instance.CustomLog("Assertion failed: " + message);
        }
    }
    // Count
    void count(const std::string tag = "default")
    {
        consoleCountMap[tag]++;
        staticLog(tag + ": " + std::to_string(consoleCountMap[tag]));
    }
    void countReset(const std::string tag = "default")
    {
        consoleCountMap[tag] = 0;
        staticLog(tag + ": " + std::to_string(consoleCountMap[tag]));
    }
    // Windows
    void message(const std::string &messageText, const std::string &messageTitle, const UINT uType = MB_OK)
    {
        std::wstring messageTextW = std::wstring(messageText.begin(), messageText.end());
        std::wstring messageTitleW = std::wstring(messageTitle.begin(), messageTitle.end());
        MessageBoxW(NULL, messageTextW.c_str(), messageTitleW.c_str(), uType);
    }
    void clear()
    {
        system("cls");
    }
    // Indent
    void addIndent(int IndentNumber = -1)
    {
        if (IndentNumber < 0)
        {
            IndentNumber = IndentBlockNumber;
        }
        for (int i = 0; i < IndentNumber; ++i)
        {
            std::cout << ' ';
        }
    }
    void setIndent(int IndentNumber = 4)
    {
        if (IndentNumber < 0)
        {
            winError("console.Indent", "The number of indentation cells should not be less than 0", 0x45021);
        }
        else
        {
            IndentBlockNumber = IndentNumber;
            CustomLog("Operation Complete -> Indent.Set");
        }
    }
    // DebugSwitchValue_STAR
    void openDebug()
    {
        debugSwitchValue_STAR = true;
        debugTellSayState();
    }
    void closeDebug()
    {
        debugSwitchValue_STAR = false;
        debugTellSayState();
    }
    void SwitchDebug()
    {
        debugSwitchValue_STAR = !debugSwitchValue_STAR;
        debugTellSayState();
    }
    // Group
    void group(const std::string groupName){
        std::cout << groupIndentLogOut() << "Group[" << groupIndentStack.size() + 1 << "]: " << groupName << std::endl;
        groupIndentStack.push_back(groupName);
    }
    void groupEnd(){
        std::cout << groupIndentLogOut(false, -1) << "<- Group-End[" << groupIndentStack.size() << "]: " << groupIndentStack.back() << std::endl;
        groupIndentStack.pop_back();
    }
    std::string getGroupName(){
        return groupIndentStack.back();
    }
    // Time
    void time(const std::string timeTag = "default"){
        CustomLog("Add timing to the timing queue: " + timeTag);
        timeNameList.push_back(timeTag);
    }
    void timeEnd(const std::string timeTag = "default"){
        CustomLog("Removes the timing to the timing queue: " + timeTag);
        // timeNameList.erase(std::remove(timeNameList.begin(), timeNameList.end(), 3), timeNameList.end());
    }
};
#include <bits/stdc++.h>
#include "colorDefine.h"
#include "windows.h"
#include <conio.h>
#include "cntconfig.h"
using namespace std;

#ifndef WINCODE_CPP
#define WINCODE_CPP
class cntstrings
{
public:
    string add(const string add1, const string add2)
    {
        return add1 + add2;
    }
    bool isAllSpace(const string Context)
    {
        for (int i = 0; i < Context.size(); ++i)
            if (Context[i] == ' ')
                return false;
        return true;
    }
};
class winCode
{
private:
    cntstrings strings;
    void setConsoleColor(const int colorCode)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, colorCode);
    }
public:
    void waitKey(const char downKey)
    {
        while (1)
        {
            char key = getch();
            if (key == downKey)
                return;
        }
    }
    bool ifDownKey(const char downKey)
    {
        char key = getch();
        if (key == downKey)
            return true;
        return false;
    }
    void setColor(const int colorCode)
    {
        setConsoleColor(colorCode);
    }
    string getTime()
    {
        auto now = chrono::system_clock::now();
        time_t now_time_t = chrono::system_clock::to_time_t(now);
        tm now_tm = *localtime(&now_time_t);
        ostringstream timeStream;
        timeStream << put_time(&now_tm, "%m/%d/%y %H:%M:%S");
        return timeStream.str();
    }
    void winError(const string codeName, const string codeTip)
    {
        setColor(RED);
        cout << "The \'" << codeName << "\' code returns an exception from the instruction set and throws it. Control Taichung, check to see if there is a problem with the instruction parameters you entered. If there is no problem, consult the developer and provide a solution." << endl
             << "Message return: " << codeTip << endl
             << "[CNT for console]"
             <<endl;
        setColor(WHITE);
    }
    void console(const string typeInformation, const string outText, const int mode)
    {
        if (typeInformation == "undefined")
        {
            winError("console", "Invalid words should not be 'undefined'");
            return;
        }
        if (strings.isAllSpace(outText))
        {
            winError("console", "The prompt can not be all white space");
        }
        if (mode > -1 && mode < 4)
        {
            winError("console", "The pattern values do not match");
        }
        // get Time & Date and change string
        string dateTip = getTime();
        switch (mode)
        {
        case 0:
            break;
        case 1:
            setColor(RED);
            break;
        case 2:
            setColor(YELLOW);
        default:
            winError("console", "You Can't have a pattern value less than 0 and greater than 2");
            break;
        }
        cout << "[" << dateTip << "][" << typeInformation << "] " << outText << endl;
        setColor(WHITE);
    }
    void winUndefined(const string codeName)
    {
        setColor(RED);
        cout << "\"" << codeName << "\" is not CNT internal code or native code, please check that your code is declared, and check that your code is not misspelled." << endl;
        setColor(WHITE);
    }
    string getUserName()
    {
        return filesystem::path("root").generic_string();
    }
};
class cntLogs
{
private:
    winCode console;
    vector <string> configName={"logFile"}, configValue={"log.txt"};
public: 
    void changeConfig(const int raw, const string configObjectName, const string configObjectValue){
        if (configObjectName != "") configName[raw] = configObjectName;
        if (configObjectValue != "") configValue[raw] = configObjectValue;
        console.console("OK", "Change log...complete", 0);
    }
    void getConfigInformation(const string configObjectName){
        for(int i = 0 ; i < configName.size() ; i++) if(configName[i] == configObjectName) cout << "This configuration information is in number " << i << endl << "The configuration name is \"" << configName[i] <<"and the target value is \"" << configValue[i] << "\"." << endl;
    }
    string getConfig(const string configObjectName){
        for (int i = 0; i < configName.size(); i++)
            if (configName[i] == configObjectName) return 
    }
    void addObject(const string &commit, const string &user = "Unknown")
    {
        time_t now = time(nullptr);
        tm *localTime = localtime(&now);
        stringstream logEntry;
        logEntry << "[" << generateRandomHexID() << "][" << setfill('0') << setw(4) << (localTime->tm_year + 1900)
                 << "-" << setfill('0') << setw(2) << (localTime->tm_mon + 1)
                 << "-" << setfill('0') << setw(2) << localTime->tm_mday
                 << " " << setfill('0') << setw(2) << localTime->tm_hour
                 << ":" << setfill('0') << setw(2) << localTime->tm_min
                 << ":" << setfill('0') << setw(2) << localTime->tm_sec << "]"
                 << "[" << user << "]: " << commit;
        ofstream file(getConfig("logFile"), ios::app);
        if (file.is_open())
        {
            file << logEntry.str() << endl;
            file.close();
        }
        else
            console.winError("log", "Unable to open log file.");
    }
    void list(const string mode)
    {
        ifstream file(getConfig("logFile"));
        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
            console.winError("log", "Unable to open log file.");
    }
    void addConfig(const string configObjectName, const string configObjectValue){
        configName.push_back(configObjectName);
        configValue.push_back(configObjectValue);
        console.console("OK", "Add log config...complete", 0);
    }
    void clean()
    {
        ofstream file(getConfig("logFile"), ios_base::out);
        console.console("OK", "Cleanup log...complete", 0);
    }
    string generateRandomHexID()
    {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<> distribution(0, 15);
        stringstream ss;
        for (int i = 0; i < 32; ++i)
        {
            int randomValue = distribution(generator);
            ss << hex << randomValue;
        }
        return ss.str();
    }
    void listConfig(){
        printf("Displays the log configuration: (Config length-%d)\n", configName.size()); 
        for (int i = 0; i < configName.size(); i++)
        {
            cout << "\"" << configName[i] << "\" : \"" << configValue[i] << "\"" << endl;
        }
    }
    void code(vector<string> codeParameter)
    {
        switch (codeParameter.size())
        {
        case 1:
            if (codeParameter[0] == "undefined" || codeParameter[0] == "list")
                list("undefined");
            if (codeParameter[0] == "clear")
                clean();
            if (codeParameter[0] == "config")
                listConfig();
            break;
        case 2:
            if (codeParameter[0] == "add"){
                addObject(codeParameter[1], console.getUserName());
                console.console("OK", "Adding log information... is complete", 0);
            }
            if (codeParameter[0] == "config") getConfig(codeParameter[1]);
            break;
        case 3:
            if (codeParameter[0] == "addConfig") addConfig(codeParameter[1], codeParameter[2]);
        case 4:
            if (codeParameter[0] == "changeConfig") changeConfig(codeParameter[1], codeParameter[2], codeParameter[3]);
        default:
            break;
        }
    }
};
class runningCode
{
private:
    winCode console;
    cntstrings strings;
    cntLogs log;
    void help(const string codeHelp)
    {
        string helpText = "";
        if (codeHelp == "undefined")
        {
            ifstream ifs;
            ifs.open("consoleHelp.txt", ios::in);
            if (!ifs.is_open())
                helpText = "CNT Console is a program used to pave the way for CNT services, you can use the CNT Console to change CNT services. \n\nUsage: CNT <Command>[<args>] \n\nThe following are common CNT commands used in various situations: \n\nThe start command can start a CNT service, for example, theCNT start GUI.\nThe webstart command can start a CNT web service, for example, the CNT webstart https://aplcexenicesetrl.cn/wiki/CNT/webserver/hello \nHandle changes (see also: cntChange)\ngo-continue service \nstop-stop service \nremove-remove service status change \nmemo-list running service kill-force off a service log-show log show various types of object \nstatus-show service status growth, Mark and adjust your common history \nservice-list, create or delete service \nreb-re-service \nchange-create, list, delete or validate change validation \ncollaboration (see also: CNT3 help workflow)\nget a statement from APLCEXENICESETRL CNT WINCODE push update remote reference and related changes \" CNT help teamwork \" lists the available subcommands and some concept guides. \nSee \" CNT Help < page > \" or \" Git Help < Command > \" for specific subcommands or concepts. For an overview of the system, see \" CNT help cntSystem \".\n\nCode List:\n    1.help - Show CNT help hunting list\n    2.version - show CNT version number\n    3.exit - exit CNT Console\n    4.update - update CNT\n    5.start - start service\n    6.webstart - start network service\n    7.go - continue service\n    8.stop - stop the service\n    9.remove - remove the service from the service index\n    10.memo - list the running services\n    11.kill - force a service to close\n    12.log - display logs\n    13.show -  displays various types of objects\n    14.status - displays service status\n    15.service - lists, creates, or deletes services, \n    16.reb - revises service changes\n    17.creates, lists, deletes, or verifies changes for use\n    18.(add instructions according to CNT environment variables) \n";
            else
            {
                string line;
                while (getline(ifs, line))
                    helpText += line;
                helpText += "\n[CNT Console Code](!) This file comes from consoleHelp.txt\n";
            }
            ifs.close();
        }
        else
            helpText = "CNT Console is a program used to pave the way for CNT services, you can use the CNT Console to change CNT services.";
        for (size_t i = 0; i < helpText.size(); ++i)
        {
            if (helpText[i] == '\\')
            {
                if (i + 1 < helpText.size() && helpText[i + 1] == 'n')
                {
                    cout << endl;
                    i++;
                }
                else if (i + 1 < helpText.size() && helpText[i + 1] == '\\')
                {
                    cout << "\\";
                    i++;
                }
                else
                    cout << helpText[i];
            }
            else
                cout << helpText[i];
        }
        return;
    }
    void surprise(const string OpenKey)
    {
        if (OpenKey == "TaimWay" || OpenKey == "taim_way")
        {
            system("cls");
            console.setColor(GREEN);
            string NonsenseLiterature[110] = {
                "The sky is really blue.",
                "Grass is green, which is not surprising.",
                "The sun rises from the east every day.",
                "The Earth is round, which is common knowledge.",
                "Watermelons are especially sweet in summer.",
                "Snow is particularly cold in winter.",
                "Owls don't sleep at night.",
                "Fish swim back and forth in the water.",
                "Learning to program can be fun.",
                "Sometimes, nonsense is also a form of art.",
                "C++ is a very powerful programming language.",
                "It was originally designed by Bjarne Stroustrup.",
                "C++ supports multiple programming paradigms.",
                "It includes procedural, object-oriented, and generic programming.",
                "C++ programs are usually named with the .cpp or .C file extension.",
                "C++ compilers convert source code into machine code.",
                "The compilation process may involve preprocessing, compiling, assembling, and linking.",
                "The C++ standard library provides a wide range of functionalities.",
                "It includes input/output streams, data structures, algorithms, etc.",
                "C++11 introduced many new features.",
                "For example, automatic type deduction auto.",
                "And range-based for loops.",
                "C++14 further enhanced the language.",
                "It introduced return type deduction.",
                "And digit separators for literals.",
                "C++17 added more components to the standard library.",
                "Such as the optional type optional.",
                "And variadic templates.",
                "C++20 brought concepts and modules.",
                "Concepts are used for type constraints.",
                "Modularization makes the code more modular.",
                "Memory management in C++ is implemented through pointers and references.",
                "Dynamic memory allocation uses new and delete.",
                "Smart pointers such as unique_ptr and shared_ptr help manage memory.",
                "C++'s exception handling mechanism can handle runtime errors.",
                "Using try, catch, and throw keywords.",
                "C++'s multithreading support allows for parallel computation.",
                "Using thread and async.",
                "C++ templates provide type parameterization.",
                "Generic programming makes the code more flexible.",
                "C++ classes and objects support encapsulation.",
                "Member variables and member functions can be modified by access control specifiers.",
                "C++'s inheritance mechanism allows for code reuse.",
                "The relationship between base classes and derived classes is 'is-a'.",
                "C++ polymorphism is implemented through virtual functions.",
                "Virtual functions allow runtime polymorphism.",
                "C++ friend functions can access the private members of a class.",
                "Friend classes can also access the private members of a class.",
                "C++ namespaces are used to avoid name conflicts.",
                "Namespaces are defined using the namespace keyword.",
                "C++ type conversions include static and dynamic conversions.",
                "Using static_cast, dynamic_cast, etc.",
                "C++ operator overloading allows for custom operator behavior.",
                "Operator functions can change the semantics of operators.",
                "References in C++ are aliases.",
                "Reference variables must be initialized at the time of definition.",
                "Pointers in C++ are the addresses of variables.",
                "Pointer arithmetic needs to be mindful of memory safety.",
                "C++ arrays are of fixed size.",
                "Array subscripts start from 0.",
                "C++ string literals are character arrays.",
                "Using the string class to handle strings is more convenient.",
                "C++ input/output streams are object-oriented.",
                "Using cin and cout for input and output.",
                "C++ file operations can be implemented through file streams.",
                "Using ifstream and ofstream.",
                "The C++ standard library provides many practical tools.",
                "Such as vector, map, etc.",
                "C++ functions can have default parameters.",
                "Default parameters provide flexibility.",
                "C++ functions can be inline.",
                "Inline functions can improve code efficiency.",
                "C++ functions can be overloaded.",
                "Function overloading allows for the same function name but with different parameters.",
                "C++ classes can have constructors and destructors.",
                "Constructors are used to initialize objects.",
                "Destructors are used to clean up resources.",
                "C++ classes can have static members.",
                "Static members belong to the class rather than the object.",
                "C++ classes can have virtual destructors.",
                "Virtual destructors ensure the correct deletion of objects.",
                "C++ classes can have friends.",
                "Friends can access the private members of a class.",
                "C++ classes can have inheritance and multiple inheritance.",
                "Multiple inheritance increases the complexity of the code.",
                "C++ classes can have abstract members.",
                "Abstract classes cannot be instantiated.",
                "C++ classes can have template members.",
                "Template members provide type parameterization.",
                "C++ classes can have member templates.",
                "Member templates allow class templates to define templates internally.",
                "C++ classes can have local classes.",
                "Local classes are class definitions within a class definition.",
                "C++ classes can have anonymous classes.",
                "Anonymous classes have no name.",
                "C++ classes can have anonymous structures.",
                "Anonymous structures are structure definitions within a class definition.",
                "C++ classes can have anonymous enumerations.",
                "Anonymous enumerations are enumeration definitions within a class definition.",
                "C++ classes can have anonymous unions.",
                "Anonymous unions are union definitions within a class definition.",
                "C++ classes can have anonymous bit-fields.",
                "Anonymous bit-fields are bit-field definitions within a class definition.",
                "C++ classes can have anonymous types.",
                "Anonymous types have no name.",
                "C++ classes can have anonymous functions.",
                "Anonymous functions have no name.",
                "Learning C++ is a journey of continuous exploration and discovery."
                "CNT is a portable program for development and use, created and updated by TaimWay.",
                "APlcexenicesetrl CNT Copyright (C) 2025 By TaimWay - MIT License - Active, open source"};
            cout << "You found this little egg. It's a little sad bee.(Absolutely no swearing) Now that we're here, let's hear my story! It's beautiful! (press 'z' to continue)" << endl;
            while (true)
            {
                for (int i = 0; i < 110; ++i)
                {
                    console.waitKey('z');
                    cout << NonsenseLiterature[i] << endl;
                    Sleep(1000);
                }
                console.waitKey('z');
                cout << "Okay, okay, you must be tired. Then Go!" << endl
                     << endl;
                if (console.ifDownKey('b'))
                    break;
                cout << "No Way" << endl;
            }
            console.setColor(WHITE);
        }
        else
            console.winUndefined("copyrights");
        return;
    }

public:
    void runCode(const string codeText, const vector<string> codeParameter)
    {
        try
        {
            if (codeText == "version")
                cout << "CNT Version: " << __CNT_CONSOLE_VERSION__ << ' ' << __OperatingSystemVersion__ << endl;
            else if (codeText == "help")
                help(codeParameter[0]);
            else if (codeText == "exit")
                exit(0);
            else if (codeText == "log")
                log.code(codeParameter);
            else if (codeText == "copyright")
                surprise(codeParameter[0]);
            else
                console.winUndefined(codeText);
        }
        catch (const exception &err)
        {
            console.winError("runningCode", strings.add("The calling function throws an exception, the exception message: ", err.what()));
        }
    }
};
#endif
// Native header file
#include <iostream>
#include <string>
#include <vector>
// The project header file
#include "private/CNT/console.h"

// Class
class runCode
{
private:
    // Data
    std::vector<std::string> command;
    console console;
    // Fun
    void help(const int code);

public:
    runCode(const std::vector<std::string> commandList);
};

runCode::runCode(const std::vector<std::string> commandList)
{
	console.openDebug();
	
    console.group("Group 1");
    console.log("Log inside" + console.getGroupName());
    console.warn("Warn inside" + console.getGroupName());
    console.error("error inside" + console.getGroupName());
    console.debug("debug inside" + console.getGroupName());
    console.CustomLog("Log inside" + console.getGroupName());
    console.staticLog("Warn inside" + console.getGroupName());
    console.group("Group 2");
    console.log("Log inside" + console.getGroupName());
    console.warn("Warn inside" + console.getGroupName());
    console.error("error inside" + console.getGroupName());
    console.debug("debug inside" + console.getGroupName());
    console.CustomLog("Log inside" + console.getGroupName());
    console.staticLog("Warn inside" + console.getGroupName());
    console.groupEnd();
    console.log("Log inside" + console.getGroupName());
    console.warn("Warn inside" + console.getGroupName());
    console.error("error inside" + console.getGroupName());
    console.debug("debug inside" + console.getGroupName());
    console.CustomLog("Log inside" + console.getGroupName());
    console.staticLog("Warn inside" + console.getGroupName());
    console.groupEnd();
    console.log("Log inside" + console.getGroupName());
    console.warn("Warn inside" + console.getGroupName());
    console.error("error inside" + console.getGroupName());
    console.debug("debug inside" + console.getGroupName());
    console.CustomLog("Log inside" + console.getGroupName());
    console.staticLog("Warn inside" + console.getGroupName());

    command = commandList;
}

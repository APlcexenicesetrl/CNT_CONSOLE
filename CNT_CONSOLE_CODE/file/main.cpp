// Native header file
#include <iostream>
#include <string>
#include <vector>
// The project header file
#include "include/Check.h"
#include "include/runCode.h"

// Program Main Function
int main(int argc, char **argv)
{
	// Declare the Class & function
	check checkDom;
	// Create Parameter list
	std::vector<std::string> commandList;
	// Input parameters
	checkDom.inputCommandVecList(argc, argv, commandList);
	runCode win(commandList);
	// Return & Exit
	return 0;
}
//

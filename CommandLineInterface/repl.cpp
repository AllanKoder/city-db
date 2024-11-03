#include "repl.h"
#include <iostream>
#include <cstring>

#include "../Config/config.h"
#include "../Services/services.h"

#include "command_decider.h"

void runREPL() 
{ 
    // Get saved data
    // TODO: add error handling.
    Services::getInstance()->getRouter()->loadDataFromLog();

    std::cout << "Started.\n";
    char* input = new char[MAX_INPUT_LENGTH];
    CommandDecider decider;

    while(true)
    {
        std::cout << "db > ";
        // Clear the input buffer
        std::cin.clear();
        std::cin.getline(input, MAX_INPUT_LENGTH);

        if (strcmp(input, "exit") == 0) {
            break;
        } 
        decider.decideAction(input);
    }
}
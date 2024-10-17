#include "repl.h"
#include <iostream>
#include <cstring>

#include "../DataRepository/data_repository.h"
#include "../Models/City/city.h"
#include "../Router/router.h"
#include "../Config/config.h"

#include "command_decider.h"

void runREPL() 
{ 
    std::cout << "Started.\n";
    char* input = new char[MAX_INPUT_LENGTH];
    CommandDecider decider;

    while(true)
    {
        // Prompt the User
        std::cout << "> ";
        
        // Clear the input buffer
        std::cin.clear();
        std::cin.getline(input, MAX_INPUT_LENGTH);

        if (strcmp(input, "exit") == 0) {
            break;
        } 
        decider.decideAction(input);
    }
}
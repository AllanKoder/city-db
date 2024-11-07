#include "repl.h"
#include <iostream>
#include <cstring>

#include "../Config/config.h"
#include "../Services/services.h"

#include "view_decider.h"

void runREPL()
{
    std::cout << "Started.\n";
    char *input = new char[MAX_INPUT_LENGTH];
    ViewDecider decider;

    while (true)
    {
        std::cout << "db > ";
        // Clear the input buffer
        std::cin.clear();
        std::cin.getline(input, MAX_INPUT_LENGTH);

        // Decide which view to take, depending on the user input
        decider.decideView(input);
    }
}
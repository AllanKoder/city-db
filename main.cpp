#include "CommandLineInterface/repl.h"
#include "Services/services.h"

int main()
{
    // Initalize the services, and load the database
    Services::getInstance()->getRouter()->loadDataFromLog();
    // Run the loop for user inputs and commands
    runREPL();
}
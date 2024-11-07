#include "CommandLineInterface/repl.h"
#include "Services/services.h"

int main()
{
    // initalize the services, and load the database
    // TODO: error handling
    Services::getInstance()->getRouter()->loadDataFromLog();
    runREPL();
}
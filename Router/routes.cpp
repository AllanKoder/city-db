#include "command_router.h"

CommandRouter& getRouter()
{
    static CommandRouter router;

    

    return router;
}
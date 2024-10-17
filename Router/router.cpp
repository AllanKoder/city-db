#include "command_router.h"
#include "router.h"
#include <iostream>

// Controllers
#include "../Controllers/City/city_controller.h"

void initializeRoutes(CommandRouter& router)
{
    router.registerRoute("hi", Controllers::City::createCity);

    // Add other routes..
}

static CommandRouter* globalRouter = nullptr;

void initializeRouter()
{
    if (!globalRouter) {
        globalRouter = new CommandRouter();
        initializeRoutes(*globalRouter);
    }
}

// Get the router instance
CommandRouter& router()
{
    if (!globalRouter) {
        initializeRouter();
    }
    return *globalRouter;
}
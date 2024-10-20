#include "command_router.h"
#include "router.h"
#include <iostream>
#include "request.h"
#include "response.h"

// Controllers
#include "../Controllers/City/city_controller.h"
namespace Router
{
    void initializeRoutes(CommandRouter& router)
    {
        router.registerRoute(RequestType::CREATE_CITY, Controllers::City::createCity);
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
}
#ifndef ROUTES_H
#define ROUTES_H

#include "command_router.h"

namespace Routes
{
    class Router
    {
    private:
        Router();
        static Router* globalRouter;
        CommandRouter* commandRouter;

        // Function to initialize routes
        void initializeRoutes();

    public:
        // Get the router instance
        static Router* getInstance();
        CommandRouter& getRouter();
    };
}

#endif // ROUTES_H
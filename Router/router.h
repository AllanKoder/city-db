#ifndef ROUTES_H
#define ROUTES_H

#include "command_router.h"

namespace Router
{
    // Function to initialize routes
    void initializeRoutes(CommandRouter& router);

    // Initialize the router
    void initializeRouter();

    // Get the router instance
    CommandRouter& router();

    // Optional: Add a cleanup function
    void cleanupRouter();

    #endif // ROUTES_H
}
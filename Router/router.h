#ifndef ROUTES_H
#define ROUTES_H

#include "command_router.h"

// Function prototype for the test command
void test(int argc, const char** argv);

// Function to initialize routes
void initializeRoutes(CommandRouter& router);

// Initialize the router
void initializeRouter();

// Get the router instance
CommandRouter& router();

// Optional: Add a cleanup function
void cleanupRouter();

#endif // ROUTES_H
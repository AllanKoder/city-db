#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include "../Config/config.h"
/**
 * @brief CommandRouter class for routing string commands to designated functions.
 * 
 * This class takes in a string command as input and routes it to the designated function.
 * The routed function is called with correct inputs.
 */
class CommandRouter {
private:
    /**
     * @brief Function pointer type for command handlers.
     * @param argc Number of arguments.
     * @param argv Array of argument strings.
     */
    typedef const char* (*CommandHandler)(int argc, const char** argv);

    /**
     * @brief Structure to store a route (command and its handler).
     */
    struct Route {
        char command[MAX_COMMAND_LENGTH]; /// The command string
        CommandHandler handler; /// Pointer to the handler function
    };

    Route routes[MAX_ROUTES]; /// Array to store registered routes
    int routeCount; /// Number of currently registered routes

    void splitCommand(const char* command, char** argv, int* argc);

public:
    /**
     * @brief Constructor initializes the route count to zero.
     */
    CommandRouter();

    /**
     * @brief Registers a new route (command and its handler).
     * @param command The command string to register.
     * @param handler The function to handle this command.
     */
    void registerRoute(const char* command, CommandHandler handler);

    /**
     * @brief Routes a given command to its registered handler.
     * @param command The command string to route.
     */
    const char* route(const char* command);
};

#endif // COMMAND_ROUTER_H
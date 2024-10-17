#include "command_router.h"
#include <cstring>
#include <iostream>

void CommandRouter::splitCommand(const char* command, char* argv[], int* argc) {
    *argc = 0;
    char buffer[MAX_COMMAND_LENGTH];
    strncpy(buffer, command, MAX_COMMAND_LENGTH - 1);
    buffer[MAX_COMMAND_LENGTH - 1] = '\0';

    char* token = strtok(buffer, " ");
    while (token != NULL && *argc < MAX_ARGS) {
        strncpy(argv[*argc], token, MAX_COMMAND_LENGTH - 1);
        argv[*argc][MAX_COMMAND_LENGTH - 1] = '\0';
        (*argc)++;
        token = strtok(NULL, " ");
    }
}

CommandRouter::CommandRouter() : routeCount(0) {}

void CommandRouter::registerRoute(const char* command, CommandHandler handler) {
    if (routeCount < MAX_ROUTES) {
        strncpy(routes[routeCount].command, command, MAX_COMMAND_LENGTH - 1);
        routes[routeCount].command[MAX_COMMAND_LENGTH - 1] = '\0';
        routes[routeCount].handler = handler;
        routeCount++;
    }
}

const char* CommandRouter::route(const char* command) {
    char argv[MAX_ARGS][MAX_COMMAND_LENGTH];
    char* argvPtrs[MAX_ARGS];
    int argc;

    for (int i = 0; i < MAX_ARGS; i++) {
        argvPtrs[i] = argv[i];
    }

    splitCommand(command, argvPtrs, &argc);

    if (argc > 0) {
        for (int i = 0; i < routeCount; i++) {
            if (strcmp(routes[i].command, argv[0]) == 0) {
                return routes[i].handler(argc - 1, (const char**)argvPtrs + 1);
            }
        }
    }
    return "NULL";
}
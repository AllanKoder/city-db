#include "command_router.h"
#include <cstring>
#include <iostream>

namespace Routes
{   
    CommandRouter::CommandRouter() {}

    void CommandRouter::registerRoute(RequestType type, CommandHandler handler, bool save) {
        routes.put(DataStructures::HashableNumber((size_t) type), handler);
    }

    Response CommandRouter::route(const Request& request) {
        if (routes.contains(request.type))
        {
            // TODO: save it to a write ahead log
            CommandHandler handler = routes.get(request.type);
            return handler(request); 
        }

        // If no matching route is found, return an error response
        Response errorResponse;
        errorResponse.type = ResponseType::REQUEST_NOT_FOUND;
        errorResponse.success = false;
        errorResponse.error = "No matching route found for the given request type";
        return errorResponse;
    }
}
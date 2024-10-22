#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include "../Config/config.h"
#include "../DataStructures/hash_map.hpp"
#include "request.h"
#include "response.h"

namespace Routes
{   
    /**
     * @brief CommandRouter class for routing requests to designated functions.
     * 
     * This class takes in a Request as input and routes it to the designated function.
     * The routed function is called with the Request and returns a Response.
     */
    class CommandRouter {
    private:
        typedef Response (*CommandHandler)(const Request& request);

        DataStructures::HashMap<RequestType, CommandHandler> routes;
    public:
        CommandRouter();

        /**
         * @brief Registers a new route (request type and its handler).
         * @param type The RequestType to register.
         * @param handler The function to handle this request type.
         * @param save Write the Request to the write ahead log.
         */
        void registerRoute(RequestType type, CommandHandler handler, bool save=false);

        /**
         * @brief Routes a given request to its registered handler.
         * @param request The Request structure to route.
         * @return Response The Response structure returned by the handler.
         */
        Response route(const Request& request);
    };
}
#endif // COMMAND_ROUTER_H
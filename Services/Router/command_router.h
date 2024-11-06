#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include "../../Config/config.h"
#include "../../DataStructures/hash_map.hpp"
#include "../../DataStructures/hashable_number.h"
#include "request.h"
#include "response.h"

namespace Routes
{ 
    // class for routing requests to designated functions.
    class CommandRouter {
    private:
        typedef Response (*CommandHandler)(const Request& request);

        // Turns the Enum to the Hashable Number for routing
        DataStructures::HashMap<DataStructures::HashableNumber, CommandHandler> routes;
        DataStructures::HashMap<DataStructures::HashableNumber, bool> saveRequest;
        DataStructures::Vector<Request> requestQueue;

        // Registers a new route (request type and its handler).
        void registerRoute(RequestType type, CommandHandler handler, bool save=false);
        void saveRequestToQueue(const Request& request);
    public:
        CommandRouter();
        // Routes a given request to its registered handler.
        Response route(const Request& request, bool saveRequest = true);
        void loadDataFromLog();
        void saveQueueToLog();
    };
}
#endif // COMMAND_ROUTER_H
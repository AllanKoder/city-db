#ifndef COMMAND_ROUTER_H
#define COMMAND_ROUTER_H

#include "../../Config/config.h"
#include "../../DataStructures/hash_map.hpp"
#include "../../DataStructures/hashable_number.h"
#include "request.h"
#include "response.h"

namespace Routes
{
    /**
     * @brief Routes requests to designated handler controller.
     * This is the mediator between the Controllers and the Views.
     *
     * This class manages the routing of requests to their appropriate handler functions,
     * and provides functionality for request logging and replay.
     */
    class CommandRouter
    {
    private:
        // Function pointer type for request handlers
        typedef Response (*CommandHandler)(const Request &request);

        // Maps request types to their handler functions
        DataStructures::HashMap<DataStructures::HashableNumber, CommandHandler> routes;

        // Indicates whether a request type should be saved for logging
        DataStructures::HashMap<DataStructures::HashableNumber, bool> saveRequest;

        // Queue for storing requests that need to be logged
        DataStructures::Vector<Request> requestQueue;

        /**
         * @brief Registers a new route (request type and its handler).
         * @param type The type of request to register.
         * @param handler The function to handle this request type.
         * @param save Whether to save this request type for logging (default: false).
         */
        void registerRoute(RequestType type, CommandHandler handler, bool save = false);

        /**
         * @brief Saves a request to the queue for later logging.
         * @param request The request to save.
         */
        void saveRequestToQueue(const Request &request);

    public:
        // Constructor
        CommandRouter();

        /**
         * @brief Routes a given request to its registered handler.
         * @param request The request to route.
         * @param saveRequest Whether to save this request for logging (default: true).
         * @return The response from the handler function.
         */
        Response route(const Request &request, bool saveRequest = true);

        /**
         * @brief Loads and replays requests from a log file.
         */
        void loadDataFromLog();

        /**
         * @brief Saves the current request queue to a log file.
         */
        void saveQueueToLog();
    };
}
#endif // COMMAND_ROUTER_H
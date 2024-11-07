#ifndef RESPONSE_H
#define RESPONSE_H

#include "../../Config/config.h"
#include "../../Models/City/city.h"
#include "../../DataStructures/vector.hpp"

namespace Routes
{
    /**
     * @struct Types of responses
     * @brief Are not really used through the app, but here for organization and future sake.
     */
    enum class ResponseType
    {
        // Response contains a message to be printed
        PRINT_MESSAGE,
        // Operation was successful, no specific data to return
        SUCCESS,
        // Response contains options for city selection
        CITY_OPTIONS,
        // Response contains a list of cities
        CITY_LIST,
        // The requested operation was not found
        REQUEST_NOT_FOUND
    };

    /**
     * @brief Responses from the router
     * Responses do not need to be POD, and can be C++ specific
     */
    struct Response
    {
        // Type of the response
        ResponseType type;

        // Indicates whether the operation was successful
        bool success;

        // Error message, if any
        const char *error;

        // General message for the response
        char message[MAX_RESPONSE_MESSAGE];

        // Data associated with the response
        union response
        {
            // Pointer to a vector of City pointers
            DataStructures::Vector<Models::City *> *cities;
        } data;
    };
}

#endif // RESPONSE_H
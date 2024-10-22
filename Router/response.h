#ifndef RESPONSE_H
#define RESPONSE_H

#include "../Config/config.h"

namespace Routes
{
    struct testing
    {

    };
    

    /*
     * @brief Handles the responses from the router
     * Responses do not need to be POD, and can be C++ specific
     * 
     */
    enum class ResponseType 
    {
        CREATE_CITY,
        PRINT_MESSAGE,
        REQUEST_NOT_FOUND
    };
    struct Response
    {
        ResponseType type;
        bool success;
        const char* error; 
        union response
        {
            char message[MAX_RESPONSE_MESSAGE];
        } resp;
    };
}

#endif
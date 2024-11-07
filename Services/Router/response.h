#ifndef RESPONSE_H
#define RESPONSE_H

#include "../../Config/config.h"
#include "../../Models/City/city.h"
#include "../../DataStructures/vector.hpp"

namespace Routes
{
    /**
     * @brief Handles the responses from the router
     * Responses do not need to be POD, and can be C++ specific
     */
    enum class ResponseType 
    {
        PRINT_MESSAGE,
        SUCCESS,
        CITY_OPTIONS,
        CITY_LIST,
        REQUEST_NOT_FOUND
    };
    struct Response
    {
        ResponseType type;
        bool success;
        const char* error; 
        char message[MAX_RESPONSE_MESSAGE];
        union response
        {
            DataStructures::Vector<Models::City*>* cities; 
        } data;
    };
}

#endif
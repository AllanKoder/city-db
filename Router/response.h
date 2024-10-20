#ifndef RESPONSE_H
#define RESPONSE_H

namespace Router
{
    struct something
    {

    };
    


    enum class ResponseType 
    {
        CREATE_CITY,
        REQUEST_NOT_FOUND
    };
    struct Response
    {
        ResponseType type;
        bool success;
        const char* error; 
        union response
        {

        };
    };
}

#endif
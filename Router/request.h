#ifndef REQUEST_H
#define REQUEST_H

namespace Router
{
    struct CreateCityDTO
    {

    };
    


    enum class RequestType 
    {
        CREATE_CITY
    };
    struct Request
    {
        RequestType type;
        union request
        {
            CreateCityDTO createCity;
        };
        
    };
}
#endif
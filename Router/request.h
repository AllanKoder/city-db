#ifndef REQUEST_H
#define REQUEST_H
#include "../Config/config.h"
#include <cstdlib>

namespace Router
{
    struct CreateMayorDTO
    {
        char name[MAX_CITY_NAME];
        char address[MAX_CITY_ADDRESS];
    };

    struct CreateCityDTO
    {
        char name[MAX_CITY_NAME];
        char history[MAX_CITY_HISTORY];
        size_t population;
        unsigned int year;
        double coordinates[2];

        CreateMayorDTO mayor;
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
        } data;
    };
}

#endif // REQUEST_H
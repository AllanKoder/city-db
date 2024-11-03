#ifndef REQUEST_H
#define REQUEST_H
#include "../../Config/config.h"
#include <cstdlib>

namespace Routes
{
    struct CreateMayorDTO
    {
        char name[MAX_MAYOR_NAME];
        char address[MAX_MAYOR_ADDRESS];
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

    struct CityPair
    {
        size_t city1;
        size_t city2;
    };

    struct UpdateMayorDTO 
    {
        char name[MAX_MAYOR_NAME];
        char address[MAX_MAYOR_ADDRESS];
    };

    struct UpdateCityDTO
    {
        size_t cityId;
        char history[MAX_CITY_HISTORY];
        size_t population;
        unsigned int year;
        double coordinates[2];

        UpdateMayorDTO mayor;
    };

   struct RequestCityOptions
    {
        char cityName[MAX_CITY_NAME];
    };

    enum RequestType 
    {
        CREATE_CITY,
        UPDATE_CITY,
        DELETE_CITY,
        GET_CITY_OPTIONS,
        DISTANCE_BETWEEN_CITIES,
        DISPLAY_MAYOR,
        DISPLAY_CITIES,
    };

    /*
     * Requests are how the router will recieve information.
     * Data must be a POD for it to write the bytes to a log file.
     */
    struct Request
    {
        RequestType type;
        union request
        {
            CreateCityDTO createCity;
            UpdateCityDTO updateCity;
            RequestCityOptions requestCityOptions;
            CityPair cityPair;
            size_t cityId;
        } data;
    };
}

#endif // REQUEST_H
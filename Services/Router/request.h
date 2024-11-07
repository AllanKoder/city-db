#ifndef REQUEST_H
#define REQUEST_H
#include "../../Config/config.h"
#include <cstdlib>

namespace Routes
{
    /**
     * @brief Data Transfer Object for creating a new mayor.
     */
    struct CreateMayorDTO
    {
        // Name of the mayor
        char name[MAX_MAYOR_NAME];
        // Address of the mayor
        char address[MAX_MAYOR_ADDRESS];
    };

    /**
     * @brief Data Transfer Object for creating a new city.
     */
    struct CreateCityDTO
    {
        // Name of the city
        char name[MAX_CITY_NAME];
        // Brief history of the city
        char history[MAX_CITY_HISTORY];
        // Population of the city
        size_t population;
        // Year of establishment
        unsigned int year;
        // Geographical coordinates [latitude, longitude]
        double coordinates[2];

        // Mayor information for the city
        CreateMayorDTO mayor;
    };

    /**
     * @brief Represents a pair of city IDs.
     */
    struct CityPair
    {
        // ID of the first city
        size_t city1;
        // ID of the second city
        size_t city2;
    };

    /**
     * @brief Data Transfer Object for updating mayor information.
     */
    struct UpdateMayorDTO
    {
        // Updated name of the mayor
        char name[MAX_MAYOR_NAME];
        // Updated address of the mayor
        char address[MAX_MAYOR_ADDRESS];
    };

    /**
     * @brief Data Transfer Object for updating city information.
     */
    struct UpdateCityDTO
    {
        // ID of the city to update
        size_t cityId;
        // Updated history of the city
        char history[MAX_CITY_HISTORY];
        // Updated population of the city
        size_t population;
        // Updated year of establishment
        unsigned int year;
        // Updated geographical coordinates
        double coordinates[2];

        // Updated mayor information
        UpdateMayorDTO mayor;
    };

    /**
     * @brief Options for requesting city information.
     */
    struct RequestCityOptions
    {
        // Name of the city to request
        char cityName[MAX_CITY_NAME];
    };

    /**
     * @brief Enumerates the types of requests that can be made.
     */
    enum RequestType
    {
        CREATE_CITY,
        UPDATE_CITY,
        DELETE_CITY,
        GET_CITIES,
        GET_ALL_CITIES,
        DISTANCE_BETWEEN_CITIES,
        DISPLAY_MAYOR,
    };

    /**
     * @brief Represents a request to the router.
     *
     * This struct is designed to be a POD (Plain Old Data) type to allow
     * easy serialization for logging purposes.
     */
    struct Request
    {
        // Type of the request
        RequestType type;
        // Data associated with the request
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
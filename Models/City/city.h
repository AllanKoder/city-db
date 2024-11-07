#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"
#include "../Mayor/mayor.h"

namespace Models
{
    /**
     * @brief A Model to hold the fields of a City
     * including, name, history, population, etc..
     * As well as other helper functions
     *
     */
    class City
    {
    public:
        // Primary key
        size_t id;
        char name[MAX_CITY_NAME];
        char history[MAX_CITY_HISTORY];
        size_t population;
        // Founding year
        unsigned int year;
        // Latitude, then Longitude
        double coordinates[2];
        // Mayor Model
        Mayor mayor;

        // Default Constructor
        City();
        // Constructor
        City(size_t id, const char *name, const char *history, size_t population, unsigned int year, double latitude, double longitude, const Mayor &mayor);
        // Copy Initalization
        City(const City &other);
        // Assignment Initatization
        City &operator=(const City &other);

        /**
         * @brief Returns a string with all the details of the city
         */
        const char *printCity() const;

        /**
         * @brief Returns a string with a brief overview of the details of a city
         */
        const char *printCityBrief() const;

        /**
         * @brief get the distance in kilometers from another city, based on latitude and longitude
         *
         * @param other Another city to compare against
         * @returns The distance in kilometers
         */
        double getKmDistance(const City &other) const;
    };
}

#endif
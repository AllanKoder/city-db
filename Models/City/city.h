#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <cstdlib>

namespace Models
{
    class City
    {
    public:
        const char* name;
        size_t population;
        unsigned int year;
        double coordinates[2];

        City();
        City(const char* name, size_t population, unsigned int year);
        ~City();
        City(const City& other);
        City& operator=(const City& other);
        City(City&& other) noexcept;
        City& operator=(City&& other) noexcept;

        void setCoordinates(double latitude, double longitude);
    };
}

#endif
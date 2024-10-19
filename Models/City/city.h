#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"
#include "../Mayor/mayor.h"

namespace Models
{
    class City
    {
    public:
        char name[MAX_CITY_NAME];
        char history[MAX_CITY_HISTORY];
        size_t population;
        unsigned int year;
        double coordinates[2];
        
        City();
        City(const char* name, const char* history, size_t population, unsigned int year);
        City(const City& other);
        City& operator=(const City& other);

        void setCoordinates(double latitude, double longitude);
    };
}

#endif
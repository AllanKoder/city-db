#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"
#include "../Mayor/mayor.h"

namespace Models
{
    class City
    {
    private:
        size_t id;
    public:

        char name[MAX_CITY_NAME];
        char history[MAX_CITY_HISTORY];
        size_t population;
        unsigned int year;
        double coordinates[2];

        Mayor mayor;
        
        City();
        City(const char* name, const char* history, size_t population, unsigned int year, double latitude, double longitude, const Mayor& mayor);
        City(const City& other);
        City& operator=(const City& other);

        size_t getId();
        void setId(size_t id);
        void setCoordinates(double latitude, double longitude);
    };
}

#endif
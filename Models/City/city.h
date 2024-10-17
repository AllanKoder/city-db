#ifndef CITY_MODEL_H
#define CITY_MODEL_H

#include <cstdlib>

namespace Models
{
    class City
    {
    public:
        City(const char* name, size_t population, unsigned int year)
            : name(name), population(population), year(year), coordinates{0, 0}
        {
            
        }

    private:
        const char* name;
        size_t population;
        unsigned int year;
        double coordinates[2];
    };
}

#endif
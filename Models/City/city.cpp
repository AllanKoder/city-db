#include "city.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace Models
{
    City::City() : population(0), year(0), coordinates{0.0, 0.0} 
    {
        name[0] = '\0';
    }

    City::City(const char* name, const char* history, size_t population, unsigned int year)
        : population(population), year(year), coordinates{0.0, 0.0}
    {
        if (name == nullptr) {
            throw std::invalid_argument("Name cannot be null");
        }
        
        strncpy(this->history, history, MAX_CITY_HISTORY - 1);
        this->history[MAX_CITY_HISTORY - 1] = '\0'; 

        strncpy(this->name, name, MAX_CITY_NAME - 1);
        this->name[MAX_CITY_NAME - 1] = '\0';  
    }

    City::City(const City& other)
        : population(other.population), year(other.year)
    {
        strncpy(this->name, other.name, MAX_CITY_NAME - 1);
        this->name[MAX_CITY_NAME - 1] = '\0';  

        strncpy(this->history, other.history, MAX_CITY_HISTORY - 1);
        this->history[MAX_CITY_HISTORY - 1] = '\0'; 

        std::copy(std::begin(other.coordinates), std::end(other.coordinates), std::begin(coordinates));
         
   }

    City& City::operator=(const City& other)
    {
        if (this != &other)
        {
            strncpy(this->name, other.name, MAX_CITY_NAME - 1);
            this->name[MAX_CITY_NAME - 1] = '\0';  

            strncpy(this->history, other.history, MAX_CITY_HISTORY - 1);
            this->history[MAX_CITY_HISTORY - 1] = '\0'; 
 
            population = other.population;
            year = other.year;
            std::copy(std::begin(other.coordinates), std::end(other.coordinates), std::begin(coordinates));
        }
        return *this;
    }

    void City::setCoordinates(double latitude, double longitude)
    {
        coordinates[0] = latitude;
        coordinates[1] = longitude;
    }
}

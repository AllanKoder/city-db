#include "city.h"
#include <cstring>
#include <stdexcept>
#include <algorithm>

namespace Models
{
    City::City() : population(0), year(0), coordinates{0.0, 0.0}, id(0), mayor() 
    {
        name[0] = '\0';
        history[0] = '\0';
    }

    City::City(const char* name, const char* history, size_t population, unsigned int year, double latitude, double longitude, const Mayor& mayor)
        : population(population), year(year), coordinates{latitude, longitude}, mayor(mayor), id(0)
    {
        if (name == nullptr || history == nullptr) {
            throw std::invalid_argument("Name and history cannot be null");
        }
        
        strncpy(this->name, name, MAX_CITY_NAME - 1);
        this->name[MAX_CITY_NAME - 1] = '\0';

        strncpy(this->history, history, MAX_CITY_HISTORY - 1);
        this->history[MAX_CITY_HISTORY - 1] = '\0';
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

    const char* City::printCity() const
    {
        static char cityInfo[1024]; 
        snprintf(cityInfo, sizeof(cityInfo), 
                "City Name: %s\nHistory: %s\nPopulation: %zu\nYear: %u\nCoordinates: (%.2f, %.2f)\n%s",
                name, history, population, year,
                coordinates[0], coordinates[1],
                mayor.printMayor()); 

        return cityInfo; 
    }

    void City::setId(size_t id)
    {
        this->id = id;
    }

    size_t City::getId()
    {
        return this->id;
    }

    void City::setCoordinates(double latitude, double longitude)
    {
        coordinates[0] = latitude;
        coordinates[1] = longitude;
    }
}

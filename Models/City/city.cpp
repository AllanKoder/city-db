#include "city.h"
#include <cstring>
#include <stdexcept>

namespace Models
{
    City::City() : name(nullptr), population(0), year(0), coordinates{0.0, 0.0} {}

    City::City(const char* name, size_t population, unsigned int year)
        : population(population), year(year), coordinates{0.0, 0.0}
    {
        if (name == nullptr) {
            throw std::invalid_argument("Name cannot be null");
        }
        
        this->name = name;
    }

    City::~City()
    {
        delete[] name;
    }

    City::City(const City& other)
        : population(other.population), year(other.year)
    {
        this->name = other.name;
        coordinates[0] = other.coordinates[0];
        coordinates[1] = other.coordinates[1];
    }

    City& City::operator=(const City& other)
    {
        if (this != &other)
        {
            delete[] name;

            this->name = other.name;
            population = other.population;
            year = other.year;
            coordinates[0] = other.coordinates[0];
            coordinates[1] = other.coordinates[1];
        }
        return *this;
    }

    City::City(City&& other) noexcept
        : name(other.name), population(other.population), year(other.year)
    {
        coordinates[0] = other.coordinates[0];
        coordinates[1] = other.coordinates[1];

        other.name = nullptr;
        other.population = 0;
        other.year = 0;
        other.coordinates[0] = 0.0;
        other.coordinates[1] = 0.0;
    }

    City& City::operator=(City&& other) noexcept
    {
        if (this != &other)
        {
            delete[] name;

            name = other.name;
            population = other.population;
            year = other.year;
            coordinates[0] = other.coordinates[0];
            coordinates[1] = other.coordinates[1];

            other.name = nullptr;
            other.population = 0;
            other.year = 0;
            other.coordinates[0] = 0.0;
            other.coordinates[1] = 0.0;
        }
        return *this;
    }

    void City::setCoordinates(double latitude, double longitude)
    {
        coordinates[0] = latitude;
        coordinates[1] = longitude;
    }
}
#ifndef VIEWS_HELPERS_H
#define VIEWS_HELPERS_H
#include <optional>
#include "../../Models/City/city.h"
#include "../../DataStructures/vector.hpp"

namespace Views::Helpers
{
    /**
     * @brief Attempts to find a city by its name
     * @param cityName The name of the city to find
     * @returns An optional containing the City if found, or empty if not found
     */
    std::optional<const Models::City> resolveCityFromName(const char *cityName);

    /**
     * @brief Retrieves all cities matching a given name
     * @param cityName The name of the cities to retrieve
     * @returns A pointer to a Vector of City pointers matching the name
     */
    DataStructures::Vector<Models::City *> *getCitiesByName(const char *cityName);

    /**
     * @brief Seeds the application with sample data
     * @param times The number of times to run the seeding process (default is 1)
     */
    void seed(int times = 1);

    /**
     * @brief Saves the current state of the application
     */
    void save();

    /**
     * @brief Exits the application
     */
    void exit_app();
}

#endif // VIEWS_HELPERS_H
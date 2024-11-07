#ifndef DATA_REPOSITORY_H
#define DATA_REPOSITORY_H

#include "../../DataStructures/hash_map.hpp"
#include "../../DataStructures/vector.hpp"
#include "../../Models/City/city.h"
#include "../../Models/Mayor/mayor.h"
#include "../../DataStructures/hashable_string.h"
#include "../../DataStructures/hashable_number.h"
#include "../Router/request.h"
#include <cstring>

/**
 * @brief Manages the storage and retrieval of city data.
 *
 * This class provides CRUD operations for city data and uses custom data structures
 * for efficient storage and lookup.
 */
class DataRepository
{
private:
    // Automatically incremented ID for new cities.
    size_t auto_id;

    // Data

    // Maps city IDs to City objects
    DataStructures::HashMap<DataStructures::HashableNumber, Models::City *> idToCity; // Use HashableNumber as key
    // Maps city names to vectors of City objects
    DataStructures::HashMap<DataStructures::HashableString, DataStructures::Vector<Models::City *> *> cities; // Use HashableString as key

public:
    // Constructor
    DataRepository();
    // Destructor
    ~DataRepository();

    // Disable copy constructor and assignment operator
    DataRepository(const DataRepository &obj) = delete;
    DataRepository &operator=(const DataRepository &) = delete;

    // CRUD
    // Create
    /**
     * @brief Creates a new city and adds it to the repository.
     * @param cityDTO Data Transfer Object containing city information.
     */
    void createCity(Routes::CreateCityDTO cityDTO);

    // Read
    /**
     * @brief Retrieves a city by its ID.
     * @param id The ID of the city to retrieve.
     * @return Pointer to the City object if found, nullptr otherwise.
     */
    Models::City *getCityById(size_t id) const;

    /**
     * @brief Retrieves all cities with a given name.
     * @param name The name of the cities to retrieve.
     * @return Pointer to a Vector of City pointers if found, nullptr otherwise.
     */
    DataStructures::Vector<Models::City *> *getCitiesByName(const char *name) const;

    /**
     * @brief Retrieves all cities in the repository.
     * @return Pointer to a Vector containing all City objects.
     */
    DataStructures::Vector<Models::City *> *getAllCities() const;

    // Update
    /**
     * @brief Updates an existing city's information.
     * @param cityDTO Data Transfer Object containing updated city information.
     */
    void updateCity(Routes::UpdateCityDTO cityDTO);

    // Delete
    /**
     * @brief Deletes a city from the repository.
     * @param id The ID of the city to delete.
     */
    void deleteCity(size_t id);
};

#endif // DATA_REPOSITORY_H
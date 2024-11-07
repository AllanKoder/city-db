#include "data_repository.h"
#include <iostream>

DataRepository::DataRepository() : cities(100), idToCity(100), auto_id(0) {}
Models::City *DataRepository::getCityById(size_t id) const
{
    // Get the city
    return idToCity.get(DataStructures::HashableNumber(id));
}

DataStructures::Vector<Models::City *> *DataRepository::getCitiesByName(const char *name) const
{
    // Get the list of cities
    return cities.get(DataStructures::HashableString(name));
}

void DataRepository::createCity(Routes::CreateCityDTO cityDTO)
{
    size_t newId = auto_id++;

    // Create Mayor object
    Models::Mayor mayor = Models::Mayor(
        cityDTO.mayor.name,
        cityDTO.mayor.address);

    // Create City object
    Models::City *cityPtr = new Models::City(
        newId,
        cityDTO.name,
        cityDTO.history,
        cityDTO.population,
        cityDTO.year,
        cityDTO.coordinates[0],
        cityDTO.coordinates[1],
        mayor);

    // Use HashableString for key
    DataStructures::HashableString cityName(cityDTO.name);

    // Add to Vector Hashmap
    if (!cities.contains(cityName))
    {
        auto newVector = new DataStructures::Vector<Models::City *>();
        cities.put(cityName, newVector);
    }
    cities.get(cityName)->add(cityPtr);

    // Add to ID Hashmap
    idToCity.put(newId, cityPtr);
}

void DataRepository::updateCity(Routes::UpdateCityDTO cityDTO)
{
    Models::City *cityInDatabase = idToCity.get(cityDTO.cityId);

    // Update the fields
    // History
    std::strncpy(cityInDatabase->history, cityDTO.history, MAX_CITY_HISTORY);

    // Population
    cityInDatabase->population = cityDTO.population;

    // Year
    cityInDatabase->year = cityDTO.year;

    // Coordinates
    std::copy(std::begin(cityDTO.coordinates), std::end(cityDTO.coordinates), std::begin(cityInDatabase->coordinates));

    // Mayor Name
    std::strncpy(cityInDatabase->mayor.name, cityDTO.mayor.name, MAX_MAYOR_NAME);

    // Mayor Address
    std::strncpy(cityInDatabase->mayor.address, cityDTO.mayor.address, MAX_MAYOR_ADDRESS);
}
void DataRepository::deleteCity(size_t cityId)
{
    // Retrieve the city pointer from idToCity
    Models::City *city = idToCity.get(cityId);

    if (city)
    {
        // Delete from the Vector using the city's name
        DataStructures::HashableString cityName(city->name);
        DataStructures::Vector<Models::City *> *cityVector = cities.get(cityName);

        if (cityVector)
        {
            // Remove the city from the vector
            cityVector->remove(city);
        }

        // Delete from the idToCity
        idToCity.remove(DataStructures::HashableNumber(cityId));

        // Call the destructor
        delete city;
    }
}

DataStructures::Vector<Models::City *> *DataRepository::getAllCities() const
{
    static DataStructures::Vector<Models::City *> allCities;

    allCities.clear(); // Clear previous contents

    DataStructures::Vector<DataStructures::Vector<Models::City *> *> cityVectors = cities.getValues();

    // Add all elements from all lists to a flattened vector
    for (size_t i = 0; i < cityVectors.size(); i++)
    {
        const auto currentCities = cityVectors[i];

        for (size_t j = 0; j < currentCities->size(); j++)
        {
            allCities.add((*currentCities)[j]);
        }
    }

    return &allCities;
}

DataRepository::~DataRepository()
{
    // Call the destructor on all the elements in the array
    // idToCity and cities are shared
    auto keys = idToCity.getKeys();
    for (size_t i = 0; i < keys.size(); ++i)
    {
        delete idToCity.get(keys[i]);
    }
}
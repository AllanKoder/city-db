#include "data_repository.h"
#include <iostream>

// Initialize the static instance pointer
DataRepository* DataRepository::instancePtr = nullptr;

DataRepository::DataRepository() : cities(100), idToCities(100), auto_id(0) { }

DataRepository* DataRepository::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new DataRepository();
    }
    return instancePtr;
}

const DataStructures::HashMap<const char*, DataStructures::Vector<Models::City*>*>& DataRepository::getCities() const
{
    return cities;
}

void DataRepository::createCity(Routes::CreateCityDTO cityDTO)
{
    size_t newId = auto_id++;

    // Create Mayor object
    Models::Mayor mayor = Models::Mayor(
        cityDTO.mayor.name,
        cityDTO.mayor.address
    );

    // Create City object
    Models::City* cityPtr = new Models::City(
        newId,
        cityDTO.name,
        cityDTO.history,
        cityDTO.population,
        cityDTO.year,
        cityDTO.coordinates[0],
        cityDTO.coordinates[1],
        mayor
    );

    const char* cityName = cityDTO.name;
    if (!cities.contains(cityName)) {
        DataStructures::Vector<Models::City*>* newVector = new DataStructures::Vector<Models::City*>;
        cities.put(cityName, newVector);
    }

    cities.get(cityName)->add(cityPtr);

    std::cout << "success?";
}

Models::City* DataRepository::getCityById(size_t id) const
{
    if (id < idToCities.size()) {
        return idToCities[id];
    }
    return nullptr;
}

DataStructures::Vector<Models::City*>* DataRepository::getCitiesByName(const char* name) const
{
    DataStructures::Vector<const char*> cityNames = cities.getKeys();
    for (size_t i = 0; i < cityNames.size(); ++i) {
        std::cout << "keys: " << cityNames[i] << "\n";
        if (caseInsensitiveCompare(cityNames[i], name)) {
            std::cout << "found!" << "\n";
            return cities.get(name);
        }
    }
    return nullptr;
}

DataStructures::Vector<Models::City*>* DataRepository::getAllCities() const
{
    static DataStructures::Vector<Models::City*> allCities;
    allCities.clear();  // Clear previous contents

    DataStructures::Vector<DataStructures::Vector<Models::City*>*> cityVectors = cities.getValues();
    for (size_t i = 0; i < cityVectors.size(); i++)
    {
        const DataStructures::Vector<Models::City*>* currentCities = cityVectors[i];
        for (size_t j = 0; j < currentCities->size(); j++)
        {
            allCities.add((*currentCities)[j]);
        }
    }

    return &allCities;
}


bool DataRepository::caseInsensitiveCompare(const char* str1, const char* str2)
{
    return strcasecmp(str1, str2) == 0;
}

DataRepository::~DataRepository()
{
    for (size_t i = 0; i < idToCities.size(); ++i) {
        delete idToCities[i];
    }
}
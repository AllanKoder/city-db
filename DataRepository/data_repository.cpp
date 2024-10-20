#include "data_repository.h"

// Initialize the static instance pointer
DataRepository* DataRepository::instancePtr = nullptr;

DataRepository::DataRepository() : cities(100), auto_id(0) { }

DataRepository* DataRepository::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new DataRepository();
    }
    return instancePtr;
}

// CRUD Operations
// Get the cities data
DataStructures::HashMap<const char*, DataStructures::Vector<Models::City>>& DataRepository::getCities()
{
    return cities;
}

size_t DataRepository::createCity(Models::City city)
{
    const char* cityName = city.name;
    city.setId(auto_id++);

    // Check if the city already exists in the HashMap
    cities.get(cityName).add(city);

    return city.getId(); 
}
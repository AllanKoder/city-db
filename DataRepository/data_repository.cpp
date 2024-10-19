#include "data_repository.h"


// Initialize the static instance pointer
DataRepository* DataRepository::instancePtr = nullptr;

DataRepository::DataRepository() : cities(100) { }

DataRepository* DataRepository::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new DataRepository();
    }
    return instancePtr;
}

// CRUD Operations
DataStructures::HashMap<const char*, Models::City>& DataRepository::getCities()
{
    return cities;
}

void DataRepository::addCity(Models::City city)
{
    cities.put(city.name, city);
}
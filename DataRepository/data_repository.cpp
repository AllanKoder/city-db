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

void DataRepository::createCity(Models::City city)
{
    size_t newId = auto_id++;
    city.setId(newId);

    Models::City* cityPtr = new Models::City(city);
    idToCities.put(newId, cityPtr);

    const char* cityName = city.name;
    if (!cities.contains(cityName)) {
        DataStructures::Vector<Models::City*>* newVector = new DataStructures::Vector<Models::City*>;
        cities.put(cityName, newVector);
    }

    cities.get(cityName)->add(cityPtr);
}

Models::City* DataRepository::getCityById(size_t id)
{
    if (idToCities.contains(id)) {
        return idToCities.get(id);
    }
    return nullptr;
}

DataStructures::Vector<Models::City*> DataRepository::getCitiesByName(const char* name)
{
    DataStructures::Vector<const char*> cityNames = cities.getKeys();
    for (size_t i = 0; i < cityNames.size(); ++i) {
        if (caseInsensitiveCompare(cityNames[i], name)) {
            return *(cities.get(cityNames[i]));
        }
    }
    return DataStructures::Vector<Models::City*>(); 
}

DataStructures::Vector<Models::City*> DataRepository::getAllCities()
{
    DataStructures::Vector<Models::City*> output;

    DataStructures::Vector<DataStructures::Vector<Models::City*>*> cityVectors = cities.getValues();
    for (size_t i = 0; i < cityVectors.size(); i++)
    {
        const DataStructures::Vector<Models::City*>* currentCities = cityVectors[i];
        for (size_t j = 0; j < currentCities->size(); j++)
        {
            output.add((*currentCities)[j]);
        }
    }
    return output;
}

bool DataRepository::caseInsensitiveCompare(const char* str1, const char* str2)
{
    return strcasecmp(str1, str2) == 0;
}

DataRepository::~DataRepository()
{
    DataStructures::Vector<size_t> ids = idToCities.getKeys();
    for (size_t i = 0; i < ids.size(); ++i) {
        delete idToCities.get(ids[i]);
    }
}
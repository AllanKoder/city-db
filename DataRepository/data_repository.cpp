#include "data_repository.h"


// Initialize the static instance pointer
DataRepository* DataRepository::instancePtr = nullptr;

DataRepository::DataRepository() : cities(100), mayors(100) { }

DataStructures::HashMap<const char*, Models::Mayor>& DataRepository::getMayors()
{
    return mayors;
}

DataStructures::HashMap<const char*, Models::City>& DataRepository::getCities()
{
    return cities;
}

DataRepository* DataRepository::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new DataRepository();
    }
    return instancePtr;
}

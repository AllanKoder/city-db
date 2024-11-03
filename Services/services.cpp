#include "services.h"

// Initialize the static instance pointer
Services* Services::instancePtr = nullptr;

Services::Services() 
{ 
    // Initalize the services
    dataRepo = new DataRepository();
}

Services* Services::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Services();
    }
    return instancePtr;
}

DataRepository* Services::getDataRepo()
{
    return dataRepo;
}
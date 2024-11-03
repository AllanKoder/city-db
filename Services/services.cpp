#include "services.h"

// Initialize the static instance pointer
Services* Services::instancePtr = nullptr;

Services::Services() 
{ 
    // Initalize the services
    dataRepo = new DataRepository();
    router = new Routes::CommandRouter();
    distanceCalculator = new DistanceCalculator();
}

Services* Services::getInstance()
{
    if (instancePtr == nullptr)
    {
        instancePtr = new Services();
    }
    return instancePtr;
}

DataRepository* Services::getDataRepo() const
{
    return dataRepo;
}

Routes::CommandRouter* Services::getRouter() const
{
    return router;
}

DistanceCalculator* Services::getDistanceCalculator() const
{
    return distanceCalculator;
}
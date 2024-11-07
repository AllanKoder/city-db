#include "services.h"

// Initialize the static instance pointer
Services *Services::instancePtr = nullptr;

Services::Services()
{
    // Initalize the services, singletons
    dataRepo = new DataRepository();
    router = new Routes::CommandRouter();
    distanceCalculator = new DistanceCalculator();
}

Services *Services::getInstance()
{
    // Create a singleton instance if null
    if (instancePtr == nullptr)
    {
        instancePtr = new Services();
    }
    return instancePtr;
}

// Get the services here:
DataRepository *Services::getDataRepo() const
{
    return dataRepo;
}

Routes::CommandRouter *Services::getRouter() const
{
    return router;
}

DistanceCalculator *Services::getDistanceCalculator() const
{
    return distanceCalculator;
}
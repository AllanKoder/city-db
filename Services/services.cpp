#include "services.h"

// Initialize the static instance pointer
Services* Services::instancePtr = nullptr;

Services::Services() 
{ 
    // Initalize the services
    dataRepo = new DataRepository();
    router = new Routes::CommandRouter();
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

Routes::CommandRouter* Services::getRouter()
{
    return router;
}
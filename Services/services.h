#ifndef SERVICES_H
#define SERVICES_H

#include "DataRepository/data_repository.h"
#include "Router/command_router.h"
#include "DistanceCalculation/distance_calculator.h"

class Services
{
private:
    static Services* instancePtr;

    // Put in Services here:
    DataRepository* dataRepo;
    Routes::CommandRouter* router;
    DistanceCalculator* distanceCalculator;

    Services();
public:
    static Services* getInstance();  

    DataRepository* getDataRepo() const;
    Routes::CommandRouter* getRouter() const;
    DistanceCalculator* getDistanceCalculator() const;
};

#endif
#ifndef SERVICES_H
#define SERVICES_H

#include "DataRepository/data_repository.h"
#include "Router/command_router.h"

class Services
{
private:
    static Services* instancePtr;

    // Put in Services here:
    DataRepository* dataRepo;
    Routes::CommandRouter* router;

    Services();
public:
    static Services* getInstance();  

    DataRepository* getDataRepo();
    Routes::CommandRouter* getRouter();
};

#endif
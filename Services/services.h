#ifndef SERVICES_H
#define SERVICES_H

#include "DataRepository/data_repository.h"

class Services
{
private:
    static Services* instancePtr;

    // Put in Services here:
    DataRepository* dataRepo;

    Services();
public:
    static Services* getInstance();  

    DataRepository* getDataRepo();
};

#endif
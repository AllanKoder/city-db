#include "mayor.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

namespace Models
{
    Mayor::Mayor()
    {
        name[0] = '\0';
        address[0] = '\0';
    }

    Mayor::Mayor(const char* name, const char* address)
    {
        if (name == nullptr || address == nullptr) {
            throw std::invalid_argument("Name and address cannot be null");
        }
        
        strncpy(this->name, name, MAX_MAYOR_NAME - 1);
        this->name[MAX_MAYOR_NAME - 1] = '\0'; 

        strncpy(this->address, address, MAX_MAYOR_ADDRESS - 1);
        this->address[MAX_MAYOR_ADDRESS - 1] = '\0'; 
    }


    Mayor::Mayor(const Mayor& other) : id(other.id)
    {
        strncpy(this->name, other.name, MAX_MAYOR_NAME - 1);
        this->name[MAX_MAYOR_NAME - 1] = '\0';

        strncpy(this->address, other.address, MAX_MAYOR_ADDRESS - 1);
        this->address[MAX_MAYOR_ADDRESS - 1] = '\0';
    }

    Mayor& Mayor::operator=(const Mayor& other)
    {
        if (this != &other)
        {
            strncpy(this->name, other.name, MAX_MAYOR_NAME - 1);
            this->name[MAX_MAYOR_NAME - 1] = '\0';

            strncpy(this->address, other.address, MAX_MAYOR_ADDRESS - 1);
            this->address[MAX_MAYOR_ADDRESS - 1] = '\0';

            id = other.id;
        }
        return *this;
    }

    const char* Mayor::printMayor() const
    {
        static char mayorInfo[256];
        snprintf(mayorInfo, sizeof(mayorInfo), "Mayor Name: %s\nAddress: %s", this->name, this->address);

        return mayorInfo;
    }
}
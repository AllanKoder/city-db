#include "mayor.h"
#include <cstring>
#include <stdexcept>

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
        
        strncpy(this->name, name, MAX_CITY_NAME - 1);
        this->name[MAX_CITY_NAME - 1] = '\0'; 

        strncpy(this->address, address, MAX_CITY_ADDRESS - 1);
        this->address[MAX_CITY_ADDRESS - 1] = '\0'; 
    }


    Mayor::Mayor(const Mayor& other)
    {
        strncpy(this->name, other.name, MAX_CITY_NAME - 1);
        this->name[MAX_CITY_NAME - 1] = '\0';

        strncpy(this->address, other.address, MAX_CITY_ADDRESS - 1);
        this->address[MAX_CITY_ADDRESS - 1] = '\0';
    }

    Mayor& Mayor::operator=(const Mayor& other)
    {
        if (this != &other)
        {
            strncpy(this->name, other.name, MAX_CITY_NAME - 1);
            this->name[MAX_CITY_NAME - 1] = '\0';

            strncpy(this->address, other.address, MAX_CITY_ADDRESS - 1);
            this->address[MAX_CITY_ADDRESS - 1] = '\0';
        }
        return *this;
    }

    void Mayor::setId(size_t id)
    {
        this->id = id;
    }

    size_t Mayor::getId()
    {
        return this->id;
    }

}
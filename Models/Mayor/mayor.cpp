#include "mayor.h"
#include <cstring>
#include <stdexcept>

namespace Models
{
    Mayor::Mayor() : name(""), city() {}
    Mayor::Mayor(const char* name, const City& city)
        : city(city)
    {
        if (name == nullptr) {
            throw std::invalid_argument("Name cannot be null");
        }
        
        size_t nameLength = strlen(name);
        this->name = new char[nameLength + 1];
        strcpy(const_cast<char*>(this->name), name);
    }

    Mayor::~Mayor()
    {
        delete[] name;
    }

    Mayor::Mayor(const Mayor& other)
        : city(other.city)
    {
        size_t nameLength = strlen(other.name);
        this->name = new char[nameLength + 1];
        strcpy(const_cast<char*>(this->name), other.name);
    }

    Mayor& Mayor::operator=(const Mayor& other)
    {
        if (this != &other)
        {
            delete[] name;

            size_t nameLength = strlen(other.name);
            this->name = new char[nameLength + 1];
            strcpy(const_cast<char*>(this->name), other.name);

            city = other.city;
        }
        return *this;
    }

    Mayor::Mayor(Mayor&& other) noexcept
        : name(other.name), city(std::move(other.city))
    {
        other.name = nullptr;
    }

    Mayor& Mayor::operator=(Mayor&& other) noexcept
    {
        if (this != &other)
        {
            delete[] name;

            name = other.name;
            city = std::move(other.city);

            other.name = nullptr;
        }
        return *this;
    }

    const char* Mayor::getName() const
    {
        return name;
    }

    const City& Mayor::getCity() const
    {
        return city;
    }

    void Mayor::setCity(const City& newCity)
    {
        city = newCity;
    }
}
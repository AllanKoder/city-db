#include "mayor.h"
#include <cstring>
#include <stdexcept>

namespace Models
{
    Mayor::Mayor() : name(nullptr) {}

    Mayor::Mayor(const char* name)
    {
        if (name == nullptr) {
            throw std::invalid_argument("Name cannot be null");
        }
        
        size_t nameLength = strlen(name);
        this->name = new char[nameLength + 1];
        strcpy(this->name, name);
    }

    Mayor::~Mayor()
    {
        delete[] name;
    }

    Mayor::Mayor(const Mayor& other)
    {
        if (other.name) {
            size_t nameLength = strlen(other.name);
            this->name = new char[nameLength + 1];
            strcpy(this->name, other.name);
        } else {
            this->name = nullptr;
        }
    }

    Mayor& Mayor::operator=(const Mayor& other)
    {
        if (this != &other)
        {
            delete[] name;

            if (other.name) {
                size_t nameLength = strlen(other.name);
                this->name = new char[nameLength + 1];
                strcpy(this->name, other.name);
            } else {
                this->name = nullptr;
            }
        }
        return *this;
    }

    Mayor::Mayor(Mayor&& other) noexcept
        : name(other.name)
    {
        other.name = nullptr;
    }

    Mayor& Mayor::operator=(Mayor&& other) noexcept
    {
        if (this != &other)
        {
            delete[] name;

            name = other.name;
            other.name = nullptr;
        }
        return *this;
    }

    const char* Mayor::getName() const
    {
        return name;
    }
}
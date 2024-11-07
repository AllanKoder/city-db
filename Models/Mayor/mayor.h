#ifndef MAYOR_MODEL_H
#define MAYOR_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"

namespace Models
{
    /**
     * @brief A Model to hold the fields of a Mayor
     * including, name, address.
     */
    class Mayor
    {
    public:
        size_t id;
        char name[MAX_MAYOR_NAME];
        char address[MAX_MAYOR_ADDRESS];

        // Default Constructor
        Mayor();
        // Constructor
        Mayor(const char* name, const char* address);
        // Copy Constructor
        Mayor(const Mayor& other);
        // Copy Assignment 
        Mayor& operator=(const Mayor& other);
        // Move Constructor
        Mayor(Mayor&& other) noexcept;

        // Display the fields
        const char* printMayor() const;
    };
}

#endif
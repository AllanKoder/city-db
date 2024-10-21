#ifndef MAYOR_MODEL_H
#define MAYOR_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"

namespace Models
{
    class Mayor
    {
    private:
        size_t id;
    public:
        char name[MAX_CITY_NAME];
        char address[MAX_CITY_ADDRESS];

        Mayor();
        Mayor(const char* name, const char* address);
        Mayor(const Mayor& other);
        Mayor& operator=(const Mayor& other);
        Mayor(Mayor&& other) noexcept;

        void setId(size_t id);
        size_t getId();
    };
}

#endif
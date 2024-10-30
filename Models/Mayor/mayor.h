#ifndef MAYOR_MODEL_H
#define MAYOR_MODEL_H

#include <cstdlib>
#include "../../Config/config.h"

namespace Models
{
    class Mayor
    {
    public:
        size_t id;
        char name[MAX_MAYOR_NAME];
        char address[MAX_MAYOR_ADDRESS];

        Mayor();
        Mayor(const char* name, const char* address);
        Mayor(const Mayor& other);
        Mayor& operator=(const Mayor& other);
        Mayor(Mayor&& other) noexcept;

        const char* printMayor() const;
    };
}

#endif
#ifndef MAYOR_MODEL_H
#define MAYOR_MODEL_H

#include <cstdlib>
#include "../City/city.h"

namespace Models
{
    class Mayor
    {
    private:
        const char* name;
        City city;

    public:
        Mayor();
        Mayor(const char* name, const City& city);
        ~Mayor();
        Mayor(const Mayor& other);
        Mayor& operator=(const Mayor& other);
        Mayor(Mayor&& other) noexcept;
        Mayor& operator=(Mayor&& other) noexcept;

        const char* getName() const;
        const City& getCity() const;
        void setCity(const City& newCity);
    };
}

#endif
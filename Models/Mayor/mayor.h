#ifndef MAYOR_MODEL_H
#define MAYOR_MODEL_H

#include <cstdlib>

namespace Models
{
    class Mayor
    {
    private:
        char* name;
        char* address;

    public:
        Mayor();
        Mayor(const char*);
        ~Mayor();
        Mayor(const Mayor& other);
        Mayor& operator=(const Mayor& other);
        Mayor(Mayor&& other) noexcept;
        Mayor& operator=(Mayor&& other) noexcept;

        const char* getName() const;
    };
}

#endif
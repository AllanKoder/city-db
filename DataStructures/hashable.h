#ifndef HASHABLE_H
#define HASHABLE_H

#include <cstddef> // For size_t

namespace DataStructures
{
    class Hashable
    {
    public:
        // Pure virtual function for generating a hash value
        virtual size_t hash() const = 0;

        // Pure virtual function for comparing equality with another Hashable object
        virtual bool areEqual(const Hashable& other) const = 0;
    };
}

#endif // HASHABLE_H
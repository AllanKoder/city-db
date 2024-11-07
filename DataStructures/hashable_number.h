#ifndef HASHABLE_NUMBER_H
#define HASHABLE_NUMBER_H

#include "hashable.h"
#include <cstring>
#include <iostream>

namespace DataStructures
{
    class HashableNumber : public Hashable
    {
    public:
        size_t number;
        // Constructor
        HashableNumber(size_t number = 0) : number(number) {}

        HashableNumber(const HashableNumber &other)
        {
            number = other.number;
        }

        // Override hash function, just return the number
        size_t hash() const override
        {
            return number;
        }

        // equality function
        bool areEqual(const Hashable &other) const override
        {
            const HashableNumber *othernNum = dynamic_cast<const HashableNumber *>(&other);
            return othernNum->number == number;
        }
    };
}

#endif // HASHABLE_NUMBER_H
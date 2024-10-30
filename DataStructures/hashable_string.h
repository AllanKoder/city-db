#ifndef HASHABLE_STRING_H
#define HASHABLE_STRING_H

#include "hashable.h"
#include <cstring>

namespace DataStructures
{
    class HashableString : public Hashable
    {
    public:
        const char* string; 

        // Constructor
        HashableString(const char* str) : string(str) {}

        // Override hash function
        // Inspired by simple FNV Hash
        // https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
        size_t hash() const override {
            const unsigned long long FNV_OFFSET_BASIS = 14695981039346656037ULL; // 64-bit offset basis
            const unsigned long long FNV_PRIME = 1099511628211ULL; // 64-bit prime

            unsigned long long hash = FNV_OFFSET_BASIS;

            for (const char* s = string; *s; ++s) {
                hash *= FNV_PRIME;          // Multiply by the prime
                hash ^= static_cast<unsigned char>(*s); // XOR with the byte
            }

            return static_cast<size_t>(hash); // Return as size_t
        }

        // Override equality function
        bool areEqual(const Hashable& other) const override {
            const HashableString* otherStr = dynamic_cast<const HashableString*>(&other);
            if (otherStr) {
                return strcmp(string, otherStr->string) == 0;
            }
            return false; // Not the same type
        }
    };
}

#endif // HASHABLE_STRING_H
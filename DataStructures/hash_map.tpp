#ifndef HASH_MAP_TPP
#define HASH_MAP_TPP

#include "hash_map.hpp"
#include <stdexcept>
#include <limits>
#include <cstdint>
#include <iostream>

namespace DataStructures
{
    template <typename K, typename V>
    HashMap<K,V>::HashMap(size_t _capacity)
        : capacity(_capacity), elementCount(0)
    {
        buckets = new KeyValuePair[capacity];
    }

    template <typename K, typename V>
    HashMap<K,V>::~HashMap()
    {
        delete[] buckets;
    }

    template <typename K, typename V>
    HashMap<K,V>::HashMap(const HashMap& other)
        : elementCount(other.elementCount), capacity(other.capacity)
    {
        buckets = new KeyValuePair[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            buckets[i] = other.buckets[i];
        }
    }

    template <typename K, typename V>
    HashMap<K,V>& HashMap<K,V>::operator=(const HashMap& other)
    {
        if (this != &other) {
            delete[] buckets;
            elementCount = other.elementCount;
            capacity = other.capacity;
            buckets = new KeyValuePair[capacity];
            for (size_t i = 0; i < capacity; ++i) {
                buckets[i] = other.buckets[i];
            }
        }
        return *this;
    }

    template <typename K, typename V>
    HashMap<K,V>::HashMap(HashMap&& other) noexcept
        : buckets(other.buckets), elementCount(other.elementCount), capacity(other.capacity)
    {
        other.buckets = nullptr;
        other.elementCount = 0;
        other.capacity = 0;
    }

    template <typename K, typename V>
    HashMap<K,V>& HashMap<K,V>::operator=(HashMap&& other) noexcept
    {
        if (this != &other) {
            delete[] buckets;
            buckets = other.buckets;
            elementCount = other.elementCount;
            capacity = other.capacity;
            other.buckets = nullptr;
            other.elementCount = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Inspired by simple FNV Hash
    // https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    template<typename K, typename V>
    size_t HashMap<K,V>::hash(const K& key) const
    {
        constexpr uint64_t FNV_OFFSET_BASIS = 0x00000100000001b3ULL;
        constexpr uint64_t FNV_PRIME = 0xcbf29ce484222325ULL;

        const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&key);
        size_t size = sizeof(K);

        uint64_t hash = FNV_OFFSET_BASIS;

        for (size_t i = 0; i < size; ++i)
        {
            hash ^= bytes[i];
            hash *= FNV_PRIME;
        }

        // Additional mixing to improve distribution
        hash ^= hash >> 32;
        hash *= 0xff51afd7ed558ccdULL;
        hash ^= hash >> 32;
        hash *= 0xc4ceb9fe1a85ec53ULL;
        hash ^= hash >> 32;

        return hash;    
    }

    template<typename K, typename V>
    void HashMap<K,V>::rehash()
    {
        size_t newCapacity = capacity * 2;
        KeyValuePair* newBuckets = new KeyValuePair[newCapacity];

        for (size_t i = 0; i < capacity; ++i) {
            if (buckets[i].state == BucketState::OCCUPIED) {
                size_t newIndex = hash(buckets[i].key) % newCapacity;
                while (newBuckets[newIndex].state == BucketState::OCCUPIED) {
                    newIndex = (newIndex + 1) % newCapacity;
                }
                newBuckets[newIndex] = buckets[i];
            }
        }

        delete[] buckets;
        buckets = newBuckets;
        capacity = newCapacity;
    }

    template<typename K, typename V>
    void HashMap<K,V>::put(const K& key, const V& value)
    {
        if (static_cast<float>(elementCount) / capacity > MAX_LOAD_FACTOR) {
            rehash();
        }

        size_t index = hash(key) % capacity;
        while (buckets[index].state == BucketState::OCCUPIED) {
            if (buckets[index].key == key) {
                buckets[index].value = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        buckets[index] = KeyValuePair(key, value, BucketState::OCCUPIED);
        ++elementCount;
    }

    template<typename K, typename V>
    V HashMap<K,V>::get(const K& key) const
    {
        size_t index = hash(key) % capacity;
        size_t startIndex = index;
        do {
            std::cout << index << "\n";
            if (buckets[index].state == BucketState::EMPTY) {
                throw std::out_of_range("Reached Empty Bucker state: Key not found");
            }
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key == key) {
                return buckets[index].value;
            }
            index = (index + 1) % capacity;
        } while (index != startIndex);
        throw std::out_of_range("Looped til end: Key not found");
    }

    template<typename K, typename V>
    bool HashMap<K,V>::remove(const K& key)
    {
        size_t index = hash(key) % capacity;
        size_t startIndex = index;
        do {
            if (buckets[index].state == BucketState::EMPTY) {
                return false;
            }
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key == key) {
                buckets[index].state = BucketState::DELETED;
                --elementCount;
                return true;
            }
            index = (index + 1) % capacity;
        } while (index != startIndex);
        return false;
    }

    template <typename K, typename V>
    DataStructures::Vector<K> HashMap<K,V>::getKeys() const 
    {
        Vector<K> keys;
        for (size_t i = 0; i < capacity; ++i) {
            if (buckets[i].state == BucketState::OCCUPIED) {
                keys.add(buckets[i].key);
            }
        }
        return keys;
    }

    template <typename K, typename V>
    DataStructures::Vector<V> HashMap<K,V>::getValues() const 
    {
        Vector<V> values;
        for (size_t i = 0; i < capacity; ++i) {
            if (buckets[i].state == BucketState::OCCUPIED) {
                values.add(buckets[i].value);
            }
        }
        return values;
    }

    template<typename K, typename V>
    bool HashMap<K,V>::contains(const K& key) const
    {
        size_t index = hash(key) % capacity;
        size_t startIndex = index;
        do {
            if (buckets[index].state == BucketState::EMPTY) {
                return false;
            }
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key == key) {
                return true;
            }
            index = (index + 1) % capacity;
        } while (index != startIndex);
        return false;
    }

    template<typename K, typename V>
    size_t HashMap<K,V>::size() const
    {
        return elementCount;
    }

    template<typename K, typename V>
    bool HashMap<K,V>::isEmpty() const
    {
        return elementCount == 0;
    }

    template<typename K, typename V>
    void HashMap<K,V>::clear()
    {
        for (size_t i = 0; i < capacity; ++i) {
            buckets[i].state = BucketState::EMPTY;
        }
        elementCount = 0;
    }
}

#endif // HASH_MAP_TPP
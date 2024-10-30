#ifndef HASH_MAP_TPP
#define HASH_MAP_TPP

#include "hash_map.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>

namespace DataStructures
{
    template <typename K, typename V>
    HashMap<K, V>::HashMap(size_t _capacity)
        : capacity(_capacity), elementCount(0)
    {
        buckets = new KeyValuePair[capacity];
    }

    template <typename K, typename V>
    HashMap<K, V>::~HashMap()
    {
        delete[] buckets;
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(const HashMap &other)
        : elementCount(other.elementCount), capacity(other.capacity)
    {
        buckets = new KeyValuePair[capacity];
        for (size_t i = 0; i < capacity; ++i)
        {
            buckets[i] = other.buckets[i]; // Copy each KeyValuePair
        }
    }

    template <typename K, typename V>
    HashMap<K, V> &HashMap<K, V>::operator=(const HashMap &other)
    {
        if (this != &other)
        {
            delete[] buckets;
            elementCount = other.elementCount;
            capacity = other.capacity;
            buckets = new KeyValuePair[capacity];
            for (size_t i = 0; i < capacity; ++i)
            {
                buckets[i] = other.buckets[i]; // Copy each KeyValuePair
            }
        }
        return *this;
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(HashMap &&other) noexcept
        : buckets(other.buckets), elementCount(other.elementCount), capacity(other.capacity)
    {
        other.buckets = nullptr;
        other.elementCount = 0;
        other.capacity = 0;
    }

    template <typename K, typename V>
    HashMap<K, V> &HashMap<K, V>::operator=(HashMap &&other) noexcept
    {
        if (this != &other)
        {
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

    template <typename K, typename V>
    size_t HashMap<K, V>::hash(const K &key) const
    {
        return key.hash(); // Use the hash method from the Hashable interface
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
                    newIndex = (newIndex + 1) % newCapacity; // Find next available slot
                }

                // Move the existing pair to the new bucket
                newBuckets[newIndex] = buckets[i];
                newBuckets[newIndex].state = BucketState::OCCUPIED; // Ensure state is set
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
        
        // Linear probing for collision resolution
        while (buckets[index].state == BucketState::OCCUPIED) {
            if (buckets[index].key.areEqual(key)) { // Use areEqual to compare keys
                buckets[index].value = value; // Update value if key exists
                return;
            }
            index = (index + 1) % capacity; // Move to the next index
        }

        // Insert new key-value pair
        buckets[index] = KeyValuePair(key, value);
        buckets[index].state = BucketState::OCCUPIED; // Set state to OCCUPIED
        ++elementCount; // Increment element count
    }

    template <typename K, typename V>
    V HashMap<K, V>::get(const K &key) const
    {
        size_t index = hash(key) % capacity;

        while (buckets[index].state != BucketState::EMPTY)
        {
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                return buckets[index].value; // Return the associated value
            }
            index = (index + 1) % capacity; // Linear probing
        }

        throw std::out_of_range("Key not found");
    }

    template <typename K, typename V>
    bool HashMap<K, V>::remove(const K &key)
    {
        size_t index = hash(key) % capacity;

        while (buckets[index].state != BucketState::EMPTY)
        {
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                buckets[index].state = BucketState::DELETED; // Mark as deleted
                --elementCount; // Decrement count
                return true; // Successfully removed
            }
            index = (index + 1) % capacity; // Linear probing
        }

        return false; // Key not found
    }

    template <typename K, typename V>
    DataStructures::Vector<K> HashMap<K, V>::getKeys() const
    {
        Vector<K> keys;

        for (size_t i = 0; i < capacity; ++i)
        {
            if (buckets[i].state == BucketState::OCCUPIED)
            {
                keys.add(buckets[i].key); // Add actual keys directly
            }
        }

        return keys;
    }

    template <typename K, typename V>
    DataStructures::Vector<V> HashMap<K, V>::getValues() const
    {
        Vector<V> values;

        for (size_t i = 0; i < capacity; ++i)
        {
            if (buckets[i].state == BucketState::OCCUPIED)
            {
                values.add(buckets[i].value); // Add actual values directly
            }
        }

        return values;
    }

    template <typename K, typename V>
    bool HashMap<K, V>::contains(const K &key) const
    {
        size_t index = hash(key) % capacity;

        while (buckets[index].state != BucketState::EMPTY)
        {
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                return true; // Key exists in the map
            }
            index = (index + 1) % capacity;
        }

        return false; // Key not found
    }

    template <typename K, typename V>
    size_t HashMap<K, V>::size() const
    {
        return elementCount; // Return number of elements in the map
    }

    template <typename K, typename V>
    bool HashMap<K, V>::isEmpty() const
    {
        return elementCount == 0; // Check if the map is empty
    }

    template <typename K, typename V>
    void HashMap<K, V>::clear()
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            buckets[i].state = BucketState::EMPTY; // Reset bucket state to EMPTY
        }

        elementCount = 0; // Reset element count to zero
    }
}

#endif // HASH_MAP_TPP
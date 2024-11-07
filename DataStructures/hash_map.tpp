#ifndef HASH_MAP_TPP
#define HASH_MAP_TPP

#include "hash_map.hpp"
#include <stdexcept>

namespace DataStructures
{
    template <typename K, typename V>
    HashMap<K, V>::HashMap(size_t _capacity)
        : capacity(_capacity), elementCount(0)
    {
        // Initalize the array
        buckets = new KeyValuePair[capacity];
    }

    template <typename K, typename V>
    HashMap<K, V>::~HashMap()
    {
        // Delete the array
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
    size_t HashMap<K, V>::hash(const K &key) const
    {
        return key.hash(); // Use the hash method from the Hashable interface
    }

    template<typename K, typename V>
    void HashMap<K,V>::rehash()
    {
        // Set the new size as double
        size_t newCapacity = capacity * 2;
        // Get the new bucket
        KeyValuePair* newBuckets = new KeyValuePair[newCapacity];

        // Go through the old bucket to rehash into the new bigger bucket
        for (size_t i = 0; i < capacity; ++i) {
            // If there is a key/value pair here
            if (buckets[i].state == BucketState::OCCUPIED) {
                // rehash
                size_t newIndex = hash(buckets[i].key) % newCapacity;
                
                while (newBuckets[newIndex].state == BucketState::OCCUPIED) {
                    newIndex = (newIndex + 1) % newCapacity; // Find next available slot
                }

                // Move the existing pair to the new bucket
                newBuckets[newIndex] = buckets[i];
                newBuckets[newIndex].state = BucketState::OCCUPIED; // Ensure state is set
            }
        }

        // Get rid of the old bucket and reassign
        delete[] buckets;
        buckets = newBuckets;
        capacity = newCapacity;
    }

    template<typename K, typename V>
    void HashMap<K,V>::put(const K& key, const V& value)
    {
        // If past load factor, rehash
        if (static_cast<float>(elementCount) / capacity > MAX_LOAD_FACTOR) {
            rehash();
        }

        // Starting index
        size_t index = hash(key) % capacity;

        // Linear probing for collision resolution
        while (buckets[index].state == BucketState::OCCUPIED) {
            if (buckets[index].key.areEqual(key)) { // Use areEqual to compare keys, from Hashable interface
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
        // Starting index
        size_t index = hash(key) % capacity;

        // If we reached an empty state, then we never reached the target
        while (buckets[index].state != BucketState::EMPTY)
        {
            // If it is the key, and occupied
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                return buckets[index].value; // Return the associated value
            }
            index = (index + 1) % capacity; // Linear probing
        }

        throw std::out_of_range("Key not found");
    }

    template <typename K, typename V>
    void HashMap<K, V>::remove(const K &key)
    {
        // Starting index
        size_t index = hash(key) % capacity;

        // If we reached an empty state, then the item does not exist
        while (buckets[index].state != BucketState::EMPTY)
        {
            // If it is the key, and and occupied, delete
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                buckets[index].state = BucketState::DELETED; // Mark as deleted
                --elementCount; // Decrement count
                return; // Successfully removed
            }
            index = (index + 1) % capacity; // Linear probing
        }

        throw std::out_of_range("Key not found");
    }

    template <typename K, typename V>
    DataStructures::Vector<K> HashMap<K, V>::getKeys() const
    {
        // output
        Vector<K> keys;

        // Go through all occupied keys, and add to output
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
        // output
        Vector<V> values;
        
        // Go through all the occupied keys, and add the values
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
        // Starting index
        size_t index = hash(key) % capacity;

        // if empty, key does not exist
        while (buckets[index].state != BucketState::EMPTY)
        {
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key.areEqual(key))
            {
                return true; // Key exists in the map
            }
            index = (index + 1) % capacity; // Linear probing
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
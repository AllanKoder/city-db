#ifndef HASH_MAP_TPP
#define HASH_MAP_TPP

#include "hash_map.hpp"
#include <stdexcept>
#include <limits>

namespace DataStructures
{
    template <typename K, typename V>
    HashMap<K,V>::HashMap(size_t _capacity) : capacity(_capacity), elementCount(0)
    {
        buckets.resize(capacity);
    }
    
    // FNV-1a hash function
    // https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
    template<typename K, typename V>
    size_t HashMap<K,V>::hash(const K& key) const
    {
        constexpr uint64_t FNV_OFFSET_BASIS = 14695981039346656037ULL;
        constexpr uint64_t FNV_PRIME = 1099511628211ULL;

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
        Vector<KeyValuePair> newBuckets(newCapacity);

        for (size_t i = 0; i < capacity; ++i) {
            if (buckets[i].state == BucketState::OCCUPIED) {
                size_t newIndex = hash(buckets[i].key) % newCapacity;
                while (newBuckets[newIndex].state == BucketState::OCCUPIED) {
                    newIndex = (newIndex + 1) % newCapacity;
                }
                newBuckets[newIndex] = buckets[i];
            }
        }

        buckets = std::move(newBuckets);
        capacity = newCapacity;
    }

    template<typename K, typename V>
    void HashMap<K,V>::put(const K& key, const V& value)
    {
        if (capacity == 0) {
            std::cerr << "Error: Capacity is zero!" << std::endl;
            return; 
        }
        if (static_cast<float>(elementCount) / capacity > MAX_LOAD_FACTOR) {
            rehash();
        }

        size_t hashValue = hash(key);
        size_t index = hashValue % capacity;
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
        size_t starting_index = hash(key) % capacity;
        for(size_t index = starting_index; ; index = (index + 1) % capacity)
        {
            if (buckets[index].state == BucketState::EMPTY) {
                throw std::out_of_range("Key not found");
            }
            if (buckets[index].state == BucketState::OCCUPIED && key == buckets[index].key)
            {
                return buckets[index].value;
            }
            if (index == starting_index) {
                throw std::out_of_range("Key not found");
            }
        }
    }

    template<typename K, typename V>
    bool HashMap<K,V>::remove(const K& key)
    {
        size_t index = hash(key) % capacity;
        size_t start_index = index;
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
        } while (index != start_index);
        return false;
    }

    template<typename K, typename V>
    bool HashMap<K,V>::contains(const K& key) const
    {
        size_t index = hash(key) % capacity;
        size_t start_index = index;
        do {
            if (buckets[index].state == BucketState::EMPTY) {
                return false;
            }
            if (buckets[index].state == BucketState::OCCUPIED && buckets[index].key == key) {
                return true;
            }
            index = (index + 1) % capacity;
        } while (index != start_index);
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
        for (auto& bucket : buckets) {
            bucket.state = BucketState::EMPTY;
        }
        elementCount = 0;
    }
}

#endif // HASH_MAP_TPP
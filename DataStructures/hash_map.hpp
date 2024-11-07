#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "vector.hpp"
#include "hashable.h"

namespace DataStructures
{
    /**
     * @brief A HashMap implementation that stores key-value pairs.
     *
     * Hashmap that uses open addressing for the hashmap implementation, better since there is no LinkedList implementation,
     * which is better for cache and more space effective.
     * Can perform all basic operations, set, update, select, delete.
     *
     * @tparam K The type of the keys in the HashMap. Must be of the Hashable interface.
     * @tparam V The type of the values in the HashMap.
     */    
    template<typename K, typename V>
    class HashMap
    {
    private:
        // Start the hashmap at a good size
        static constexpr size_t DEFAULT_CAPACITY{16};

        // If capacity reaches beyond this percentage, increase capacity
        static constexpr float MAX_LOAD_FACTOR{0.75f};

        enum class BucketState { EMPTY, OCCUPIED, DELETED };

        // Store the key and value in a struct
        struct KeyValuePair
        {
            K key; // Store the key value
            V value; // Store the actual value
            BucketState state;

            KeyValuePair() : state(BucketState::EMPTY) {}
            KeyValuePair(const K& k, const V& v, BucketState s = BucketState::OCCUPIED) 
                : key(k), value(v), state(s) {}
        };

        // Create an array of key value pairs
        KeyValuePair* buckets;
        size_t elementCount;
        size_t capacity;

        size_t hash(const K& key) const; // hash the key, since K is from the Hashable interface 
        //< Resizes and rehashes the current elements when load factor exceeds MAX_LOAD_FACTOR.
        void rehash(); 

    public:
        // Constructor
        HashMap(size_t capacity = DEFAULT_CAPACITY);
        // Destructor
        ~HashMap();
        // Copy Constructor
        HashMap(const HashMap& other);
        // Copy assignment
        HashMap& operator=(const HashMap& other);
        // Move Constructor
        HashMap(HashMap&& other) noexcept;

        /**
         * @brief Inserts a key-value pair into the HashMap.
         *
         * If the key already exists, its value will be updated.
         *
         * @param key The key to insert or update.
         * @param value The value associated with the key.
         */
        void put(const K& key, const V& value);

        /**
         * @brief Retrieves the value associated with a given key.
         *
         * Throws an exception if the key does not exist in the map.
         *
         * @param key The key whose associated value is to be retrieved.
         * @return The value associated with the specified key.
         */
        V get(const K& key) const;
        
        void remove(const K& key);

        /**
         * @brief Retrieves all keys stored in the HashMap as a vector.
         *
         * @return A vector containing all keys in the map.
         */
        DataStructures::Vector<K> getKeys() const; // Return vector of keys

        /**
         * @brief Retrieves all values stored in the HashMap as a vector.
         *
         * @return A vector containing all values in the map.
        */
        DataStructures::Vector<V> getValues() const; // Return vector of values

        /**
         * @brief Checks if a specific key exists in the HashMap.
         *
         * @param key The key to check for existence in the map.
         * @return True if the key exists; otherwise, false.
         */
        bool contains(const K& key) const;
        
        /**
         * @brief Returns the number of elements currently stored in the HashMap.
         *
         * @return The number of elements in the map.
         */
        size_t size() const;

        /**
         * @brief Checks if the HashMap is empty (contains no elements).
         *
         * @return True if empty; otherwise, false.
         */
        bool isEmpty() const;

        /**
         * @brief Clears all elements from the HashMap, leaving it empty.
         */
        void clear();
    };
}

#include "hash_map.tpp"

#endif // HASHMAP_HPP
#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "vector.hpp"
#include <cstddef>
#include <cstdint>

namespace DataStructures
{
    template<typename K, typename V>
    class HashMap
    {
     private:
        static constexpr size_t DEFAULT_CAPACITY{16};
        static constexpr float MAX_LOAD_FACTOR{0.75f};

        enum class BucketState { EMPTY, OCCUPIED, DELETED };

        struct KeyValuePair
        {
            K key;
            V value;
            BucketState state;
            KeyValuePair() : state(BucketState::EMPTY) {}
            KeyValuePair(const K& k, const V& v, BucketState s = BucketState::OCCUPIED) 
                : key(k), value(v), state(s) {}
        };

        KeyValuePair* buckets;
        size_t elementCount;
        size_t capacity;

        size_t hash(const K& key) const;
        void rehash();

    public:
        HashMap(size_t capacity = DEFAULT_CAPACITY);
        ~HashMap();
        HashMap(const HashMap& other);
        HashMap& operator=(const HashMap& other);
        HashMap(HashMap&& other) noexcept;
        HashMap& operator=(HashMap&& other) noexcept;

        void put(const K& key, const V& value);
        V get(const K& key) const;
        bool remove(const K& key);
        DataStructures::Vector<K> getKeys() const;
        DataStructures::Vector<V> getValues() const;
        bool contains(const K& key) const;
        size_t size() const;
        bool isEmpty() const;
        void clear();
    };
}

#include "hash_map.tpp"

#endif // HASHMAP_HPP
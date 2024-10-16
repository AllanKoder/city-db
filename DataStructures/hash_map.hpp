#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include "vector.hpp"

namespace DataStructures
{
    template<typename K, typename V>
    class HashMap
    {
    private:
        static constexpr size_t DEFAULT_CAPACITY{16};
        static constexpr float MAX_LOAD_FACTOR{0.50f};

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

        Vector<KeyValuePair> buckets;
        size_t elementCount;
        size_t capacity;

        size_t hash(const K& key) const;
        void rehash();

    public:
        HashMap(size_t capacity = DEFAULT_CAPACITY);

        void put(const K& key, const V& value);
        V get(const K& key) const;
        bool remove(const K& key);
        bool contains(const K& key) const;
        size_t size() const;
        bool isEmpty() const;
        void clear();
    };
}

#include "hash_map.tpp"

#endif // HASHMAP_HPP
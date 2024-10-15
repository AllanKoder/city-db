#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <stdexcept>
#include <initializer_list>
#include <algorithm> 

namespace DataStructures 
{
    template <typename T>
    class ArrayList 
    {
    public:
        ArrayList(size_t initialCapacity = 10);
        ArrayList(std::initializer_list<T> init);
        ArrayList(const ArrayList& other);
        ~ArrayList();
        ArrayList& operator=(const ArrayList& other);
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        size_t size() const;
        void add(const T& element);
        void remove(const T& element);
        void resize(size_t newCapacity);

    private:
        T* array;
        size_t capacity;
        size_t count;
    };
};

#include "array_list.tpp"

#endif // ARRAY_LIST_HPP
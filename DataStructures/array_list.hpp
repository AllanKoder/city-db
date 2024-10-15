#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdexcept>
#include <initializer_list>
#include <algorithm> 

namespace DataStructures 
{
    template <typename T>
    class ArrayList 
    {
    public:
        ArrayList();
        ArrayList(std::initializer_list<T> init);
        ArrayList(const ArrayList& arraylist);
        ~ArrayList();
        ArrayList& operator=(const ArrayList& other);
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        unsigned int size() const;
        void add(const T& element);
        void remove(const T& element);

    private:
        T* array;
        unsigned int capacity;
        unsigned int count;

        void resize(unsigned int new_capacity);
    };
};

#include "array_list.tpp"

#endif // ARRAY_LIST_H
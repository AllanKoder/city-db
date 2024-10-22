#ifndef VECTOR_HPP 
#define VECTOR_HPP

#include <stdexcept>
#include <initializer_list>
#include <cstddef>
#include <cstdint>

namespace DataStructures 
{
    template <typename T>
    class Vector 
    {
    public:
        Vector(size_t initialCapacity = 10);
        Vector(std::initializer_list<T> init);
        Vector(const Vector& other);
        ~Vector();
        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
        size_t size() const;
        void add(const T& element);
        void remove(const T& element);
        bool contains(const T& element);
        void resize(size_t newCapacity);
        void clear();
    private:
        T* array;
        size_t capacity;
        size_t count;
    };
};

#include "vector.tpp"

#endif // VECTOR_HPP
#include "vector.hpp"
#include <stdexcept>
#include <cstddef>

namespace DataStructures 
{
    template <typename T>
    Vector<T>::Vector(size_t initalCapacity) : capacity(initalCapacity), count(0)
    {
        array = new T[initalCapacity];
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> init) : count(init.size()), capacity(init.size())
    {
        array = new T[capacity];
        std::copy(init.begin(), init.end(), array);
    }

    template <typename T>
    Vector<T>::Vector(const Vector& other) : count(other.count), capacity(other.capacity)
    {
        array = new T[capacity];
        std::copy(other.array, other.array + count, array);
    }

    template <typename T>
    Vector<T>::~Vector() 
    {
        delete[] array;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector& other) 
    {
        if (this != &other) {
            delete[] array;
            count = other.count;
            capacity = other.capacity;
            array = new T[capacity];
            std::copy(other.array, other.array + count, array);
        }
        return *this;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] array;  // Free existing resources
            
            // Transfer ownership
            array = other.array;
            count = other.count;
            capacity = other.capacity;
            
            // Reset source object
            other.array = nullptr;
            other.count = 0;
            other.capacity = 0;
        }
        return *this;
    }

    template <typename T>
    T& Vector<T>::operator[](size_t index)
    {
        if (index >= this->capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[index];
    }

    template <typename T>
    const T& Vector<T>::operator[](size_t index) const
    {
        if (index >= this->capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[index];
    }

    template <typename T>
    size_t Vector<T>::size() const
    {
        return count;
    }

    template <typename T>
    void Vector<T>::add(const T& element) 
    {
        if (count >= capacity) resize(static_cast<unsigned int>(capacity * 1.5) + 1);
        array[count++] = element;
    }

    template <typename T>
    void Vector<T>::remove(const T& element)
    {
        // Shift all of the elements back by one once found, does not call destructor.
        for (size_t i = 0; i < count; ++i) {
            if (array[i] == element) {
                std::copy(array + i + 1, array + count, array + i);
                --count;
                return;
            }
        }

        throw std::invalid_argument("Element not found");
    }

    template <typename T>
    void Vector<T>::resize(size_t newCapacity)
    {
        T* new_array = new T[newCapacity];
        std::copy(array, array + count, new_array);
        delete[] array;
        array = new_array;
        capacity = newCapacity;
    }

    template <typename T>
    void Vector<T>::clear()
    {
        for (size_t i = 0; i < count; ++i) {
            array[i].~T();  // Call destructor for each element
        }
        count = 0;
    }
}
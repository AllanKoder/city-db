#include "vector.hpp"
#include <stdexcept>
#include <cstddef>

namespace DataStructures
{
    template <typename T>
    Vector<T>::Vector(size_t initalCapacity) : capacity(initalCapacity), elementCount(0)
    {
        // Create the array
        array = new T[initalCapacity];
    }

    template <typename T>
    Vector<T>::Vector(std::initializer_list<T> init) : elementCount(init.size()), capacity(init.size())
    {
        // Create the array
        array = new T[capacity];
        // Copy from the initalizer list
        std::copy(init.begin(), init.end(), array);
    }

    template <typename T>
    Vector<T>::Vector(const Vector &other) : elementCount(other.elementCount), capacity(other.capacity)
    {
        // Create the array
        array = new T[capacity];
        // Copy from the other array
        std::copy(other.array, other.array + elementCount, array);
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        // Delete
        delete[] array;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(const Vector &other)
    {
        if (this != &other)
        {
            // Delete since we lose the pointer to a new one
            delete[] array;
            // Copy the other element's properties
            elementCount = other.elementCount;
            capacity = other.capacity;
            array = new T[capacity];
            std::copy(other.array, other.array + elementCount, array);
        }
        return *this;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] array; // Free existing resources

            // Transfer ownership
            array = other.array;
            elementCount = other.elementCount;
            capacity = other.capacity;

            // Reset source object
            other.array = nullptr;
            other.elementCount = 0;
            other.capacity = 0;
        }
        return *this;
    }

    template <typename T>
    T &Vector<T>::operator[](size_t index)
    {
        if (index >= this->capacity)
        {
            throw std::out_of_range("Index out of bounds");
        }
        // return the element
        return array[index];
    }

    template <typename T>
    const T &Vector<T>::operator[](size_t index) const
    {
        if (index >= this->capacity)
        {
            throw std::out_of_range("Index out of bounds");
        }
        // return the const element
        return array[index];
    }

    template <typename T>
    size_t Vector<T>::size() const
    {
        return elementCount;
    }

    template <typename T>
    void Vector<T>::add(const T &element)
    {
        if (elementCount >= capacity)
            resize(static_cast<unsigned int>(capacity * 1.5) + 1);
        // Add the element
        array[elementCount++] = element;
    }

    template <typename T>
    void Vector<T>::remove(const T &element)
    {
        // Shift all of the elements back by one once found, does not call destructor.
        for (size_t i = 0; i < elementCount; ++i)
        {
            if (array[i] == element)
            {
                // Found, now shift everything else back by 1
                std::copy(array + i + 1, array + elementCount, array + i);
                --elementCount;
                return;
            }
        }

        throw std::invalid_argument("Element not found");
    }

    template <typename T>
    void Vector<T>::resize(size_t newCapacity)
    {
        // If we need more space
        if (newCapacity > capacity)
        {
            // Make a bigger array and copy over the past elements
            T *new_array = new T[newCapacity];
            std::copy(array, array + elementCount, new_array);
            delete[] array;
            array = new_array;
            capacity = newCapacity;
        }
    }

    template <typename T>
    void Vector<T>::sort()
    {
        // A simple bubble sort
        for (size_t i = 0; i < elementCount - 1; ++i)
        {
            for (size_t j = 0; j < elementCount - i - 1; ++j)
            {
                if (array[j] > array[j + 1])
                {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }

    template <typename T>
    void Vector<T>::clear()
    {
        // remove all the elements by calling their destructor
        for (size_t i = 0; i < elementCount; ++i)
        {
            array[i].~T(); // Call destructor for each element
        }
        // The elements still exist, but we can overwrite them.
        elementCount = 0;
    }
}
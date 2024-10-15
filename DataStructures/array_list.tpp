#include "array_list.hpp"

namespace DataStructures 
{
    template <typename T>
    ArrayList<T>::ArrayList(size_t initalCapacity) 
    {
        array = new T[initalCapacity];
        capacity = initalCapacity;
        count = 0;
    }

    template <typename T>
    ArrayList<T>::ArrayList(std::initializer_list<T> init) : count(init.size()), capacity(init.size())
    {
        array = new T[capacity];
        std::copy(init.begin(), init.end(), array);
    }

    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList& other) : count(other.count), capacity(other.capacity)
    {
        array = new T[capacity];
        std::copy(other.array, other.array + count, array);
    }

    template <typename T>
    ArrayList<T>::~ArrayList() 
    {
        delete[] array;
    }

    template <typename T>
    ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) 
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

    template <typename T>
    T& ArrayList<T>::operator[](size_t index)
    {
        if (index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[index];
    }

    template <typename T>
    const T& ArrayList<T>::operator[](size_t index) const
    {
        if (index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[index];
    }

    template <typename T>
    size_t ArrayList<T>::size() const
    {
        return count;
    }

    template <typename T>
    void ArrayList<T>::add(const T& element) 
    {
        if (count >= capacity) resize(static_cast<unsigned int>(capacity * 1.5) + 1);
        array[count++] = element;
    }

    template <typename T>
    void ArrayList<T>::remove(const T& element)
    {
        for (unsigned int i = 0; i < count; ++i) {
            if (array[i] == element) {
                std::copy(array + i + 1, array + count, array + i);
                --count;
                return;
            }
        }
    }

    template <typename T>
    void ArrayList<T>::resize(size_t newCapacity)
    {
        T* new_array = new T[newCapacity];
        std::copy(array, array + count, new_array);
        delete[] array;
        array = new_array;
        capacity = newCapacity;
    }
}
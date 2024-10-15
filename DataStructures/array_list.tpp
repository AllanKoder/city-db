#include "array_list.hpp"

namespace DataStructures 
{
    template <typename T>
    ArrayList<T>::ArrayList() 
    {
        array = new T[10];
        capacity = 10;
        count = 10;
    }

    template <typename T>
    ArrayList<T>::ArrayList(std::initializer_list<T> init) : count(init.size()), capacity(init.size())
    {
        array = new T[capacity];
        std::copy(init.begin(), init.end(), array);
    }

    template <typename T>
    ArrayList<T>::ArrayList(const ArrayList& arraylist) : count(arraylist.count), capacity(arraylist.capacity)
    {
        array = new T[capacity];
        std::copy(arraylist.array, arraylist.array + count, array);
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
    unsigned int ArrayList<T>::size() const
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
    void ArrayList<T>::resize(unsigned int new_capacity)
    {
        T* new_array = new T[new_capacity];
        std::copy(array, array + count, new_array);
        delete[] array;
        array = new_array;
        capacity = new_capacity;
    }
}
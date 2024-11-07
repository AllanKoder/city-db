#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <cstdint>

namespace DataStructures
{
    /**
     * @brief A dynamic array implementation of a vector.
     *
     * This class can handle any size of elements, with allocation to the heap
     * can append, delete, and view elements
     *
     * @tparam T The type of elements stored in the vector.
     */
    template <typename T>
    class Vector
    {
    public:
        // Default constructor
        Vector(size_t initialCapacity = 10);
        // Initalization with lists
        Vector(std::initializer_list<T> init);
        // Copy Constructor
        Vector(const Vector &other);
        // Destructor
        ~Vector();
        // Copy Assignment
        Vector &operator=(const Vector &other);
        // Move assignment
        Vector &operator=(Vector &&other) noexcept;
        // Access Operator
        T &operator[](size_t index);
        // Const Access Operator
        const T &operator[](size_t index) const;

        /**
         * @brief Get the number of elements in the vector.
         * @return The number of elements in the vector.
         */
        size_t size() const;

        /**
         * @brief Add an element to the end of the vector.
         * @param element The element to be added.
         */
        void add(const T &element);

        /**
         *  @brief Remove the element from the vector
         *  @param element The element to be removed.
         */
        void remove(const T &element);

        /**
         * @brief Check if the vector contains a specific element.
         * @param element The element to search for.
         * @return true if the element is found, false otherwise.
         */
        bool contains(const T &element);

        /**
         * @brief Resize the vector to a new capacity.
         * @param newCapacity The new capacity for the vector.
         */
        void resize(size_t newCapacity);

        /**
         * @brief Remove all elements from the vector.
         */
        void clear();

    private:
        T *array;            // Pointer to array
        size_t capacity;     // How many elements we can hold
        size_t elementCount; // Count of elements being held
    };
};

#include "vector.tpp"

#endif // VECTOR_HPP
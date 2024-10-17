#ifndef TESTING_ARRAY_LIST_CPP
#define TESTING_ARRAY_LIST_CPP

#include "../testing.cpp"
#include "../../DataStructures/vector.hpp"
#include <memory>

namespace Testing
{
    class TestVector : public Test
    {
        public:        
        TestVector(const char* name) : Test(name) {}

        void runTests() override
        {
            can_initalize_list_constructor();
            test_destructor();
            can_resize();
            can_remove_elements();            
            test_copy_instructor();
        }

        private:
        void can_initalize_list_constructor()
        {
            std::cout << "can_initalize_list_constructor\n";
            // Call the list constructor
            DataStructures::Vector<int> list {1,2,3};
            
            // Elements must match
            ASSERT(list[0] == 1, "Must be 1");
            ASSERT(list[1] == 2, "Must be 2");
            ASSERT(list[2] == 3, "Must be 3");
        }
        
        void test_destructor()
        {
            std::cout << "test_destructor\n";
            // Use a shared_ptr to track the number of references
            std::shared_ptr<int> sharedInt = std::make_shared<int>(42);

            // Create a scope
            {
                DataStructures::Vector<std::shared_ptr<int>> list;
                list.add(sharedInt);

                // Ensure the shared_ptr is in the list
                ASSERT(*list[0] == 42, "Shared pointer value must be 42");

                // At this point, there should be two references to the int:
                // 1. Our original sharedInt
                // 2. The one in the ArrayList
                ASSERT(sharedInt.use_count() == 2, "Should have 2 references to the shared_ptr");
            }

            // After the ArrayList goes out of scope, its destructor should be called,
            // which should decrease the reference count of the shared_ptr
            ASSERT(sharedInt.use_count() == 1, "Should have 1 reference to the shared_ptr after ArrayList destruction");
        }

        void can_resize()
        {
            std::cout << "can_resize\n";

            DataStructures::Vector<int> list(10);
            
            // Add more elements than the initial capacity
            for (int i = 0; i < 15; ++i) {
                list.add(i);
            }

            // Check size
            ASSERT(list.size() == 15, "Size should be 15 after adding 15 elements");

            // Check elements
            for (int i = 0; i < 15; ++i) {
                ASSERT(list[i] == i, "Element at index " + std::to_string(i) + " should be " + std::to_string(i));
            }
        }

        void can_remove_elements()
        {
            std::cout << "can_remove_elements\n";

            DataStructures::Vector<int> list {10, 20, 30, 40, 50};
            
            // Remove an element
            list.remove(30);

            // Check size
            ASSERT(list.size() == 4, "Size should be 4 after removing one element");

            // Check Array
            ASSERT(list[0] == 10, "First element should be 10");
            ASSERT(list[1] == 20, "Second element should be 20");
            ASSERT(list[2] == 40, "Third element should be 40");
            ASSERT(list[3] == 50, "Fourth element should be 50");
        }

        void test_copy_instructor()
        {
            std::cout << "test_copy_instructor\n";
            // Create an ArrayList of shared_ptr
            DataStructures::Vector<std::shared_ptr<int>> original;
            original.add(std::make_shared<int>(1));
            original.add(std::make_shared<int>(2));
            original.add(std::make_shared<int>(3));

            // Create a shallow copy
            DataStructures::Vector<std::shared_ptr<int>> shallowCopy(original);

            // Modify the value pointed to by the shared_ptr in the copy
            *shallowCopy[1] = 10;

            // Check that the change is reflected in both original and copy
            ASSERT(*original[1] == 10, "Original should be affected by changes to the shallow copy");
            ASSERT(*shallowCopy[1] == 10, "Shallow copy should reflect the change");
        }
    };
}

#endif
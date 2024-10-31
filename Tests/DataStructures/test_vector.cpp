#include "test_vector.h"
#include <iostream>

namespace Testing
{
    TestVector::TestVector(const char* name) : Test(name) {}

    void TestVector::runTests()
    {
        can_initalize_list_constructor();
        test_destructor();
        can_resize();
        can_remove_elements();
        test_copy_instructor();
    }

    void TestVector::can_initalize_list_constructor()
    {
        std::cout << "can_initalize_list_constructor\n";
        DataStructures::Vector<int> list {1,2,3};
        
        ASSERT(list[0] == 1, "Must be 1");
        ASSERT(list[1] == 2, "Must be 2");
        ASSERT(list[2] == 3, "Must be 3");
    }

    void TestVector::test_destructor()
    {
        std::cout << "test_destructor\n";
        std::shared_ptr<int> sharedInt = std::make_shared<int>(42);

        {
            DataStructures::Vector<std::shared_ptr<int>> list;
            list.add(sharedInt);

            ASSERT(*list[0] == 42, "Shared pointer value must be 42");
            ASSERT(sharedInt.use_count() == 2, "Should have 2 references to the shared_ptr");
        }

        ASSERT(sharedInt.use_count() == 1, "Should have 1 reference to the shared_ptr after ArrayList destruction");
    }

    void TestVector::can_resize()
    {
        std::cout << "can_resize\n";

        DataStructures::Vector<int> list(10);
        
        for (int i = 0; i < 15; ++i) {
            list.add(i);
        }

        ASSERT(list.size() == 15, "Size should be 15 after adding 15 elements");

        for (int i = 0; i < 15; ++i) {
            ASSERT(list[i] == i, "Element at index " + std::to_string(i) + " should be " + std::to_string(i));
        }
    }

    void TestVector::can_remove_elements()
    {
        std::cout << "can_remove_elements\n";

        DataStructures::Vector<int> list {10, 20, 30, 40, 50};
        
        list.remove(30);

        ASSERT(list.size() == 4, "Size should be 4 after removing one element");

        ASSERT(list[0] == 10, "First element should be 10");
        ASSERT(list[1] == 20, "Second element should be 20");
        ASSERT(list[2] == 40, "Third element should be 40");
        ASSERT(list[3] == 50, "Fourth element should be 50");
    }

    void TestVector::test_copy_instructor()
    {
        std::cout << "test_copy_instructor\n";
        DataStructures::Vector<std::shared_ptr<int>> original;
        original.add(std::make_shared<int>(1));
        original.add(std::make_shared<int>(2));
        original.add(std::make_shared<int>(3));

        DataStructures::Vector<std::shared_ptr<int>> shallowCopy(original);

        *shallowCopy[1] = 10;

        ASSERT(*original[1] == 10, "Original should be affected by changes to the shallow copy");
        ASSERT(*shallowCopy[1] == 10, "Shallow copy should reflect the change");
    }
}
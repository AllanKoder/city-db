#include "test_hash_map.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace Testing
{
    TestHashMap::TestHashMap(const char* name) : Test(name) {}

    void TestHashMap::runTests()
    {
        can_initialize_hash_map();
        can_put_and_get_elements();
        can_remove_elements();
        can_handle_collisions();
        can_resize();
        can_handle_deletions();
        test_copy_constructor();
        test_move_constructor();
    }

    void TestHashMap::can_initialize_hash_map()
    {
        std::cout << "can_initialize_hash_map\n";
        DataStructures::HashMap<int, MockObject> map(10);
        ASSERT(map.size() == 0, "New HashMap should be empty");
        ASSERT(map.isEmpty(), "New HashMap should be empty");
    }

    void TestHashMap::can_put_and_get_elements()
    {
        std::cout << "can_put_and_get_elements\n";
        DataStructures::HashMap<int, MockObject> map;
        
        map.put(1, MockObject{1});
        map.put(2, MockObject{2});
        map.put(3, MockObject{3});

        ASSERT(map.size() == 3, "Size should be 3 after adding 3 elements");
        ASSERT(map.get(1).value == 1, "Value for key 1 should be 1");
        ASSERT(map.get(2).value == 2, "Value for key 2 should be 2");
        ASSERT(map.get(3).value == 3, "Value for key 3 should be 3");
    }

    void TestHashMap::can_remove_elements()
    {
        std::cout << "can_remove_elements\n";
        DataStructures::HashMap<int, MockObject> map;
        
        map.put(1, MockObject{1});
        map.put(2, MockObject{2});
        map.put(3, MockObject{3});

        ASSERT(map.remove(2), "Should successfully remove key 2");
        ASSERT(map.size() == 2, "Size should be 2 after removing one element");
        ASSERT(!map.contains(2), "Map should not contain key 2 after removal");

        try {
            map.get(2);
            ASSERT(false, "Should throw exception when getting removed key");
        } catch (const std::out_of_range&) {
            // Expected behavior
        }
    }

    void TestHashMap::can_handle_collisions()
    {
        std::cout << "can_handle_collisions\n";
        DataStructures::HashMap<int, int> map(1);  // Small capacity to force collisions
        
        map.put(1, 1);
        map.put(17, 2);

        ASSERT(map.get(1) == 1, "Should correctly retrieve value for key 1");
        ASSERT(map.get(17) == 2, "Should correctly retrieve value for key 17");
    }

    void TestHashMap::can_resize()
    {
        std::cout << "can_resize\n";
        DataStructures::HashMap<int, int> map(2);  // Start with a small capacity

        for (int i = 0; i < 100; ++i) {
            map.put(i, i * 10);
        }

        ASSERT(map.size() == 100, "Should contain all 100 elements after resizing");
        for (int i = 0; i < 100; ++i) {
            ASSERT(map.get(i) == i * 10, "Should correctly retrieve value after resizing");
        }
    }

    void TestHashMap::can_handle_deletions()
    {
        std::cout << "can_handle_deletions\n";
        DataStructures::HashMap<int, int> map(4);  // Small capacity to force collisions

        for (int i = 0; i < 100; ++i) {
            map.put(i, i * 10);
        }

        for (int i = 0; i < 50; ++i) {
            map.remove(i);
        }

        ASSERT(map.size() == 50, "Should contain only the last 50 elements");
        for (int i = 50; i < 100; ++i) {
            ASSERT(map.get(i) == i * 10, "Should be able to access specific key/value");
        }
    }

    void TestHashMap::test_copy_constructor()
    {
        std::cout << "test_copy_constructor\n";
        DataStructures::HashMap<int, MockObject> original;
        original.put(1, MockObject{1});
        original.put(2, MockObject{2});

        DataStructures::HashMap<int, MockObject> copy(original);

        ASSERT(copy.size() == original.size(), "Copy should have the same size as original");
        ASSERT(copy.get(1).value == 1, "Copy should have the same values as original");
        ASSERT(copy.get(2).value == 2, "Copy should have the same values as original");

        original.put(3, MockObject{3});
        ASSERT(!copy.contains(3), "Changes to original should not affect copy");
    }

    void TestHashMap::test_move_constructor()
    {
        std::cout << "test_move_constructor\n";
        DataStructures::HashMap<int, MockObject> original;
        original.put(1, MockObject{1});
        original.put(2, MockObject{2});

        DataStructures::HashMap<int, MockObject> moved(std::move(original));

        ASSERT(moved.size() == 2, "Moved map should have the elements of original");
        ASSERT(moved.get(1).value == 1, "Moved map should have the values of original");
        ASSERT(moved.get(2).value == 2, "Moved map should have the values of original");

        ASSERT(original.isEmpty(), "Original should be empty after move");
    }
}
#include "test_hash_map.h"
#include "../../DataStructures/hashable_string.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

namespace Testing
{
    TestHashMap::TestHashMap(const char *name) : Test(name) {}

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
        DataStructures::HashMap<DataStructures::HashableString, int> map(10);
        ASSERT(map.size() == 0, "New HashMap should be empty");
        ASSERT(map.isEmpty(), "New HashMap should be empty");
    }

    void TestHashMap::can_put_and_get_elements()
    {
        std::cout << "can_put_and_get_elements\n";
        DataStructures::HashMap<DataStructures::HashableString, int> map;

        map.put(DataStructures::HashableString("key1"), 1);
        map.put(DataStructures::HashableString("key2"), 2);
        map.put(DataStructures::HashableString("key3"), 3);

        ASSERT(map.size() == 3, "Size should be 3 after adding 3 elements");
        ASSERT(map.get(DataStructures::HashableString("key1")) == 1, "Value for key 'key1' should be 1");
        ASSERT(map.get(DataStructures::HashableString("key2")) == 2, "Value for key 'key2' should be 2");
        ASSERT(map.get(DataStructures::HashableString("key3")) == 3, "Value for key 'key3' should be 3");
    }

    void TestHashMap::can_remove_elements()
    {
        std::cout << "can_remove_elements\n";
        DataStructures::HashMap<DataStructures::HashableString, int> map;

        map.put(DataStructures::HashableString("key1"), 1);
        map.put(DataStructures::HashableString("key2"), 2);
        map.put(DataStructures::HashableString("key3"), 3);

        ASSERT(map.remove(DataStructures::HashableString("key2")), "Should successfully remove key 'key2'");
        ASSERT(map.size() == 2, "Size should be 2 after removing one element");
        ASSERT(!map.contains(DataStructures::HashableString("key2")), "Map should not contain key 'key2' after removal");

        try
        {
            map.get(DataStructures::HashableString("key2"));
            ASSERT(false, "Should throw exception when getting removed key");
        }
        catch (const std::out_of_range &)
        {
            // Expected behavior
        }
    }

    void TestHashMap::can_handle_collisions()
    {
        std::cout << "can_handle_collisions\n";
        DataStructures::HashMap<DataStructures::HashableString, int> map(1); // Small capacity to force collisions

        map.put(DataStructures::HashableString("key1"), 1);
        map.put(DataStructures::HashableString("key17"), 2); 

        ASSERT(map.get(DataStructures::HashableString("key1")) == 1, "Should correctly retrieve value for key 'key1'");
        ASSERT(map.get(DataStructures::HashableString("key17")) == 2, "Should correctly retrieve value for key 'key17'");
    }

    void TestHashMap::can_resize()
    {
        std::cout << "can_resize\n";
        DataStructures::HashMap<DataStructures::HashableString, int> map(2); // Start with a small capacity

        for (int i = 0; i < 100; ++i)
        {
            std::string key = "key" + std::to_string(i);
            map.put(DataStructures::HashableString(key.c_str()), i * 10);
            std::cout << "Current size after inserting " << key << ": " << map.size() << "\n"; 
        }

        ASSERT(map.size() == 100, "Should contain all 100 elements after resizing");

        for (int i = 0; i < 100; ++i)
        {
            std::string key = "key" + std::to_string(i);
            ASSERT(map.get(DataStructures::HashableString(key.c_str())) == i * 10,
                "Should correctly retrieve value after resizing");
        }
    }

    void TestHashMap::can_handle_deletions()
    {
        std::cout << "can_handle_deletions\n";
        DataStructures::HashMap<DataStructures::HashableString, int> map(4); // Small capacity to force collisions

        for (int i = 0; i < 100; ++i)
        {
            std::string key = "key" + std::to_string(i);
            map.put(DataStructures::HashableString(key.c_str()), i * 10);
        }

        for (int i = 0; i < 50; ++i)
        {
            std::string key = "key" + std::to_string(i);
            map.remove(DataStructures::HashableString(key.c_str()));
        }

        ASSERT(map.size() == 50, "Should contain only the last 50 elements");
        for (int i = 50; i < 100; ++i)
        {
            std::string key = "key" + std::to_string(i);
            ASSERT(map.get(DataStructures::HashableString(key.c_str())) == i * 10,
                   "Should be able to access specific key/value");
        }
    }

    void TestHashMap::test_copy_constructor()
    {
        std::cout << "test_copy_constructor\n";
        DataStructures::HashMap<DataStructures::HashableString, int> original;
        original.put(DataStructures::HashableString("key1"), 1);
        original.put(DataStructures::HashableString("key2"), 2);

        DataStructures::HashMap<DataStructures::HashableString, int> copy(original);

        ASSERT(copy.size() == original.size(), "Copy should have the same size as original");
        ASSERT(copy.get(DataStructures::HashableString("key1")) == 1, "Copy should have the same values as original");
        ASSERT(copy.get(DataStructures::HashableString("key2")) == 2, "Copy should have the same values as original");

        original.put(DataStructures::HashableString("key3"), 3);
        ASSERT(!copy.contains(DataStructures::HashableString("key3")), "Changes to original should not affect copy");
    }

    void TestHashMap::test_move_constructor()
    {
        std::cout << "test_move_constructor\n";
        DataStructures::HashMap<DataStructures::HashableString, int> original;
        original.put(DataStructures::HashableString("key1"), 1);
        original.put(DataStructures::HashableString("key2"), 2);

        DataStructures::HashMap<DataStructures::HashableString, int> moved(std::move(original));

        ASSERT(moved.size() == 2, "Moved map should have the elements of original");
        ASSERT(moved.get(DataStructures::HashableString("key1")) == 1, "Moved map should have the values of original");
        ASSERT(moved.get(DataStructures::HashableString("key2")) == 2, "Moved map should have the values of original");

        ASSERT(original.isEmpty(), "Original should be empty after move");
    }
}

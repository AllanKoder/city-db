#ifndef TESTING_HASH_MAP_H
#define TESTING_HASH_MAP_H

#include "../testing.h"
#include "../../DataStructures/hash_map.hpp"
#include <string>

namespace Testing
{
    class TestHashMap : public Test
    {
    public:
        TestHashMap(const char* name);
        void runTests() override;

    private:
        void can_initialize_hash_map();
        void can_put_and_get_elements();
        void can_remove_elements();
        void can_handle_collisions();
        void can_resize();
        void can_handle_deletions();
        void test_copy_constructor();
        void test_move_constructor();
    };
}

#endif // TESTING_HASH_MAP_H
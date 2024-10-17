#ifndef TESTING_VECTOR_H
#define TESTING_VECTOR_H

#include "../testing.h"
#include "../../DataStructures/vector.hpp"
#include <memory>

namespace Testing
{
    class TestVector : public Test
    {
    public:
        TestVector(const char* name);
        void runTests() override;

    private:
        void can_initalize_list_constructor();
        void test_destructor();
        void can_resize();
        void can_remove_elements();
        void test_copy_instructor();
    };
}

#endif // TESTING_VECTOR_H
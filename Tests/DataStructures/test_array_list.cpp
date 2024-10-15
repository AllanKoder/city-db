#include "../testing.cpp"
#include "../../DataStructures/array_list.hpp"
#include <memory>

namespace Testing
{
    
    class TestArrayList : public Test
    {
        public:        
        TestArrayList(const char* name) : Test(name) {}

        void runTests() override
        {
           can_initalize_list_constructor();
           test_destructor();
        }

        private:
        void can_initalize_list_constructor()
        {
            DataStructures::ArrayList<int> list {1,2,3};
            ASSERT(list[0] == 1, "Must be 1");
            ASSERT(list[1] == 2, "Must be 2");
            ASSERT(list[2] == 3, "Must be 3");
        }
        
        void test_destructor()
        {
            // Use a shared_ptr to track the number of references
            std::shared_ptr<int> sharedInt = std::make_shared<int>(42);

            // Create a scope for the ArrayList
            {
                DataStructures::ArrayList<std::shared_ptr<int>> list;
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
    };
}
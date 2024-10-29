#ifndef TESTING_H
#define TESTING_H

#include <iostream>
#include <cstdlib>

/*
* MACRO to ASSERT that the statement is true.
* Takes a statement
*/
#define ASSERT(cond, statement) \
    if (!(cond)) { \
        std::cerr   << "---------------------\n" \
                    << "Assertion failed: " << #cond << "\n" \
                    << "File: " << __FILE__ << "\n" \
                    << "Line: " << __LINE__ << "\n" \
                    << "Message: " << statement << std::endl; \
        std::abort(); \
    } \

namespace Testing 
{
    // Mock struct for testing
    struct MockObject {
        int value;
        bool operator==(const MockObject& other) const;
    };

    class Test
    {
    public:
        Test(const char* _testName);
        const char* getName();
        virtual void runTests() = 0;
    private:
        const char* testName;
    };
}

#endif // TESTING_H
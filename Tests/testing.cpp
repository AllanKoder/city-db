#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <cstdlib>

/*
* MACRO to ASSERT that the statement is true.
* Takes a statement
*/
#define ASSERT(cond, statement) \
    do { \
        if (!(cond)) { \
            std::cerr   << "---------------------\n" \
                        << "Assertion failed: " << #cond << "\n" \
                        << "File: " << __FILE__ << "\n" \
                        << "Line: " << __LINE__ << "\n" \
                        << "Message: " << statement << std::endl; \
            std::abort(); \
        } \
    } while (0)

namespace Testing 
{
    // Mock struct for testing
    struct MockObject {
        int value;
    };

    class Test
    {
    public:
        Test(const char* _testName) : testName(_testName) {}
        const char* getName() {return testName;}
        virtual void runTests() = 0;
    private:
        const char* testName;
    };
}

#endif
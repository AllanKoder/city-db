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
            std::cerr << "Assertion failed: " << #cond << "\n" \
                        << "File: " << __FILE__ << "\n" \
                        << "Line: " << __LINE__ << "\n" \
                        << "Message: " << statement << std::endl; \
            std::abort(); \
        } \
    } while (0)

namespace Testing 
{
    class Test
    {
    public:
        Test(const char* _testName) {}
        const char* getName() {return testName;}
        virtual void runTests();
        virtual ~Test() {}
    private:
        const char* testName;
    };
}

#endif
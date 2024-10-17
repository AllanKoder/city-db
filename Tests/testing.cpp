#include "testing.h"

namespace Testing 
{
    bool MockObject::operator==(const MockObject& other) const
    {
        return value == other.value;
    }

    Test::Test(const char* _testName) : testName(_testName) {}

    const char* Test::getName() 
    {
        return testName;
    }
}
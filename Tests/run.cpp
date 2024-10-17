#include "testing.h"
#include <iostream>
// Tests
#include "DataStructures/test_vector.h"
#include "DataStructures/test_hash_map.h"


// Function to run all tests
void runAllTests(Testing::Test* tests[], int testCount) {
    for (int i = 0; i < testCount; ++i) {
        std::cout << "Running test: " << tests[i]->getName() << "\n";
        tests[i]->runTests();
        std::cout << "Test success: " << tests[i]->getName() << "\n\n";
    }
}

int main()
{
    const int TEST_COUNT = 2;  

    // An array of Test pointers
    Testing::Test* tests[TEST_COUNT];

    // CONFIG TESTS
    tests[0] = new Testing::TestVector("Vector Data Structure Tests");
    tests[1] = new Testing::TestHashMap("HashMap Data Structure Tests");

    // Run all tests
    runAllTests(tests, TEST_COUNT);

    std::cout << "All Tests Completed!\n";

    return 0;
}
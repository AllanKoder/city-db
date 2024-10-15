#include "testing.cpp"
#include <iostream>
// Tests
#include "DataStructures/test_array_list.cpp"

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
    const int TEST_COUNT = 1;  

    // An array of Test pointers
    Testing::Test* tests[TEST_COUNT];

    // CONFIG TESTS
    tests[0] = new Testing::TestArrayList("ArrayList Data Structure Tests");
    
    // Run all tests
    runAllTests(tests, TEST_COUNT);

    std::cout << "All Tests Completed!\n";

    // Clean up
    for (int i = 0; i < TEST_COUNT; ++i) {
        delete tests[i];
    }
    return 0;
}
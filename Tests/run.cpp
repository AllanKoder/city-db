#include "testing.cpp"
#include <iostream>
// Tests
#include "DataStructures/test_array_list.cpp"

int main()
{
    // Config Test Cases here
    Testing::TestArrayList test1("ArrayList Data Structure Tests");

    test1.runTests();

    std::cout << "All Tests Passed!\n";
}
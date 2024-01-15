#include "etest.h"

TEST_CASE(integer_equality)
{
    int expected = 42;
    int actual = 42;

    ASSERT_EQUAL(expected, actual);
}

int main() {
    // Run all test cases
    RUN_TESTS();

    ETEST_LOG(INFO, "This is an informational message");
    ETEST_LOG(WARNING, "This is a warning message");
    ETEST_LOG(ERROR, "This is an error message");
    ETEST_LOG(DEBUG, "This is a debug message");

    return 0;
}
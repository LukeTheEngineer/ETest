#include "include/ETest/etest.h"

TEST(TestSuite_, Example){
    ETEST_LOG(INFO, "Test case macro test");
    
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
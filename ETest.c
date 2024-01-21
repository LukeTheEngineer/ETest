#include "include/ETest/etest.h"
#include "inttypes.h"

// Testing the ETEST_LOG macros 
TEST(ETest_Log, Example)
{
    ETEST_LOG(INFO, "Test case macro test");
    ETEST_LOG(INFO, "This is an informational message");
    ETEST_LOG(WARNING, "This is a warning message");
    ETEST_LOG(ERROR, "This is an error message");
    ETEST_LOG(DEBUG, "This is a debug message");
}

// Testing the assertion macros 
TEST(ASSERTION_TEST, Example)
{
    etest_log(INFO, "Beginning ETest assertion testing");
    bool True = true; 
    bool False = false;
    ASSERT(True);

    ASSERT(False);

    uint8_t value = 1; 
    uint8_t value2 = 2;
    ASSERT_EQUAL(value, value2);

    ASSERT_NOT_EQUAL(value, value2);

    uint8_t *value_ptr = &value;
    uint8_t *value_ptr2 = &value2;


    ASSERT_NULL(value_ptr); // Shouldn't be NULL and should raise an error
    ASSERT_NOT_NULL(value_ptr); // Should not raise an error 

    ASSERT_NULL(value_ptr2); // Should raise an error 
    ASSERT_NOT_NULL(value_ptr2); // Should not raise an error 

    value_ptr = NULL;
    value_ptr2 = NULL;
    
    ASSERT_NULL(value_ptr); // Should be successful
    ASSERT_NOT_NULL(value_ptr); // Should raise an error 

    ASSERT_NULL(value_ptr2); // should be successful 
    ASSERT_NOT_NULL(value_ptr2); // Should raise an error


}

int
main()
{
    // Run all test cases
    RUN_ETESTS();

    return 0;
}
/**
 * @file    ETest.h
 * @brief   BSD 3-Clause License
 * @date    1.14.2024
 *
 * @details
 * This file defines a simple C test framework with assertion macros and logging.
 * The framework allows the definition and execution of test cases.
 *
 * @copyright (c) 2024 Lukas R. Jackson
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ETEST__H
#define __ETEST__H

#include <stdbool.h>
#include <stdio.h>

#include "color_code.h"

/**
 * @struct testinfo
 * @brief Structure to hold information about a test.
 */
typedef struct
{
    const char* suite_name; /**< Name of the test suite. */
    const char* test_name;  /**< Name of the test. */
    void (*test_function)(void); /**< Pointer to the test function. */
} __attribute__((packed)) testinfo;

static testinfo all_tests[500]; /**< Array to store information about all tests. */
static int num_tests = 0; /**< Number of defined tests. */

/** @enum LogLevel
 *  @brief Log levels for test framework logging.
 */
enum LogLevel
{
    INFO, /**< Information level. */
    WARNING, /**< Warning level. */
    ERROR, /**< Error level. */
    DEBUG /**< Debug level. */
};

/** @def TEST(suite, name)
 *  @brief Macro to define a test.
 *  @param suite The name of the test suite.
 *  @param name The name of the test.
 */
#define TEST(suite, name)                                                          \
    void test_##suite##_##name(void);                                              \
    __attribute__((constructor)) void register_test_##suite##_##name(void)         \
    {                                                                              \
        all_tests[num_tests++] = (testinfo){#suite, #name, test_##suite##_##name}; \
    }                                                                              \
    void test_##suite##_##name(void)

/** @def ETEST_LOG(level, info, ...)
 *  @brief Macro for logging within the test framework.
 *  @param level The log level (INFO, WARNING, ERROR, DEBUG).
 *  @param info The log message format.
 *  @param ... Additional log message parameters.
 */
#define ETEST_LOG(level, info, ...)                                         \
    do                                                                      \
    {                                                                       \
        switch (level)                                                      \
        {                                                                   \
        case INFO:                                                          \
            printf(BGRN "%s: " CRESET info "\n", "ETEST INFO", ##__VA_ARGS__);    \
            break;                                                          \
        case WARNING:                                                       \
            printf(BYEL "%s: " CRESET info "\n", "ETEST WARNING", ##__VA_ARGS__); \
            break;                                                          \
        case ERROR:                                                         \
            printf(BRED "%s: " CRESET info "\n", "ETEST ERROR", ##__VA_ARGS__);   \
            break;                                                          \
        case DEBUG:                                                         \
            printf(BBLU "%s: " CRESET info "\n", "ETEST DEBUG", ##__VA_ARGS__);   \
            break;                                                          \
        default:                                                            \
            break;                                                          \
        }                                                                   \
    } while (0)

/** @def etest_log(level, info, ...)
 *  @brief Alias for ETEST_LOG.
 */
#define etest_log ETEST_LOG

/** @def ASSERT(condition)
 *  @brief Assertion macro for checking a condition.
 *  @param condition The condition to check.
 */
#define ASSERT(condition)                                                \
    if (!(condition))                                                    \
    {                                                                    \
        printf("Assertion failed: %s, line %d\n", #condition, __LINE__); \
    }

/** @def ASSERT_EQUAL(expected, actual)
 *  @brief Assertion macro for checking equality.
 *  @param expected The expected value.
 *  @param actual The actual value.
 */
#define ASSERT_EQUAL(expected, actual)                                                            \
    if ((expected) != (actual))                                                                   \
    {                                                                                             \
        printf("Assertion failed: Expected %s, got %s, line %d\n", #expected, #actual, __LINE__); \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
        ETEST_LOG(ERROR, "Unexpected Error ");                                                    \
    }

/** @def ASSERT_NOT_EQUAL(not_expected, actual)
 *  @brief Assertion macro for checking inequality.
 *  @param not_expected The value not expected.
 *  @param actual The actual value.
 */
#define ASSERT_NOT_EQUAL(not_expected, actual)                                              \
    if ((not_expected) == (actual))                                                         \
    {                                                                                       \
        printf("Assertion failed: Did not expect %s, but got %s, line %d\n", #not_expected, \
               #actual, __LINE__);                                                          \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        ETEST_LOG(ERROR, "Unexpected Error ");                                              \
    }

/** @def ASSERT_NULL(pointer)
 *  @brief Assertion macro for checking if a pointer is NULL.
 *  @param pointer The pointer to check.
 */
#define ASSERT_NULL(pointer)                                                          \
    if ((pointer) != NULL)                                                            \
    {                                                                                 \
        printf("Assertion failed: Expected NULL, got non-NULL, line %d\n", __LINE__); \
    }

/** @def ASSERT_NOT_NULL(pointer)
 *  @brief Assertion macro for checking if a pointer is not NULL.
 *  @param pointer The pointer to check.
 */
#define ASSERT_NOT_NULL(pointer)                                              \
    if ((pointer) == NULL)                                                    \
    {                                                                         \
        printf("Assertion failed: Did not expect NULL, line %d\n", __LINE__); \
    }

/** @def RUN_TESTS()
 *  @brief Macro to run all test cases.
 */
#define RUN_TESTS()                                                                       \
    for (int i = 0; i < num_tests; ++i)                                                   \
    {                                                                                     \
        ETEST_LOG(INFO, "Running Test: %s.%s\n", all_tests[i].suite_name, all_tests[i].test_name); \
        all_tests[i].test_function();                                                     \
        ETEST_LOG(INFO, "Test Passed\n\n");                                                        \
    }                                                                                     \
    (0)

#endif /* __ETEST__H */

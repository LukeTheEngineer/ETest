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

#pragma GCC diagnostic ignored "-Wformat-extra-args"

#include <stdbool.h>
#include <stdio.h>

// Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Regular underline text
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

// Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

// High intensty background
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

// High intensty text
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

// Bold high intensity text
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

// Reset
#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"


/**
 * @struct testinfo
 * @brief Structure to hold information about a test.
 */
typedef struct
{
    const char* suite_name;      /**< Name of the test suite. */
    const char* test_name;       /**< Name of the test. */
    void (*test_function)(void); /**< Pointer to the test function. */
} __attribute__((packed)) testinfo;

static testinfo all_tests[500]; /**< Array to store information about all tests. */
static int num_tests = 0;       /**< Number of defined tests. */

/** @enum LogLevel
 *  @brief Log levels for test framework logging.
 */
enum LogLevel
{
    INFO,    /**< Information level. */
    WARNING, /**< Warning level. */
    ERROR,   /**< Error level. */
    DEBUG,   /**< Debug level. */
    BLANK
};

/** @def ETEST_LOG(level, info, ...)
 *  @brief Macro for logging within the test framework.
 *  @param level The log level (INFO, WARNING, ERROR, DEBUG).
 *  @param info The log message format.
 *  @param ... Additional log message parameters.
 */
#define ETEST_LOG(level, info, ...)                                               \
    do                                                                            \
    {                                                                             \
        switch (level)                                                            \
        {                                                                         \
        case INFO:                                                                \
            printf(BGRN "%s: " CRESET info "\n", "ETEST INFO", ##__VA_ARGS__);    \
            break;                                                                \
        case WARNING:                                                             \
            printf(BYEL "%s: " CRESET info "\n", "ETEST WARNING", ##__VA_ARGS__); \
            break;                                                                \
        case ERROR:                                                               \
            printf(BRED "%s: " CRESET info "\n", "ETEST ERROR", ##__VA_ARGS__);   \
            break;                                                                \
        case DEBUG:                                                               \
            printf(BBLU "%s: " CRESET info "\n", "ETEST DEBUG", ##__VA_ARGS__);   \
            break;                                                                \
        case BLANK:                                                               \
            printf("%s", info "\n", ##__VA_ARGS__);                               \
            break;                                                                \
        default:                                                                  \
            break;                                                                \
        }                                                                         \
    } while (0)

/** @def etest_log(level, info, ...)
 *  @brief Alias for ETEST_LOG.
 */
#define etest_log ETEST_LOG

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

/** @def ASSERT(condition)
 *  @brief Assertion macro for checking a condition.
 *  @param condition The condition to check.
 */
#define ASSERT(condition)                                                             \
    if (!(condition))                                                                 \
    {                                                                                 \
        ETEST_LOG(ERROR, "Assertion failed: %s, line %d\n", #condition, __LINE__);    \
    }                                                                                 \
    else if ((condition))                                                             \
    {                                                                                 \
        ETEST_LOG(INFO, "Assertion successful: %s, line %d\n", #condition, __LINE__); \
    }

/** @def ASSERT_EQUAL(expected, actual)
 *  @brief Assertion macro for checking equality.
 *  @param expected The expected value.
 *  @param actual The actual value.
 */
#define ASSERT_EQUAL(expected, actual)                                                           \
    if ((expected) != (actual))                                                                  \
    {                                                                                            \
        ETEST_LOG(ERROR, "Assertion failed: Expected %s, got %s, line %d\n", #expected, #actual, \
                  __LINE__);                                                                     \
    }                                                                                            \
    else if ((expected) == (actual))                                                             \
    {                                                                                            \
        ETEST_LOG(INFO, "Assertion successful: %s, line %d\n", #expected, __LINE__);             \
    }                                                                                            \
    else                                                                                         \
    {                                                                                            \
        ETEST_LOG(ERROR, "Unexpected Error ");                                                   \
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
    else if ((not_expected) != (actual))                                                    \
    {                                                                                       \
        ETEST_LOG(INFO, "Assertion successful: %s, line %d\n", #not_expected, __LINE__);    \
    }                                                                                       \
    else                                                                                    \
    {                                                                                       \
        ETEST_LOG(ERROR, "Unexpected Error ");                                              \
    }

/** @def ASSERT_NULL(pointer)
 *  @brief Assertion macro for checking if a pointer is NULL.
 *  @param pointer The pointer to check.
 */
#define ASSERT_NULL(pointer)                                                            \
    if ((pointer) != NULL)                                                              \
    {                                                                                   \
        ETEST_LOG(ERROR, "Assertion failed: %s, line %d\n", #pointer, __LINE__);        \
    }                                                                                   \
    else if ((pointer) == NULL)                                                         \
    {                                                                                   \
        ETEST_LOG(INFO, "Assertion successful: %s, line %d\n", #pointer, __LINE__);     \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        ETEST_LOG(ERROR, "Unknown assertion error: %s, line %d\n", #pointer, __LINE__); \
    }

/** @def ASSERT_NOT_NULL(pointer)
 *  @brief Assertion macro for checking if a pointer is not NULL.
 *  @param pointer The pointer to check.
 */
#define ASSERT_NOT_NULL(pointer)                                                        \
    if ((pointer) == NULL)                                                              \
    {                                                                                   \
        ETEST_LOG(ERROR, "Assertion failed: %s, line %d\n", #pointer, __LINE__);        \
    }                                                                                   \
    else if ((pointer) != NULL)                                                         \
                                                                                        \
    {                                                                                   \
        ETEST_LOG(INFO, "Assertion successful: %s, line %d\n", #pointer, __LINE__);     \
    }                                                                                   \
    else                                                                                \
    {                                                                                   \
        ETEST_LOG(ERROR, "Unknown assertion error: %s, line %d\n", #pointer, __LINE__); \
    }


/** @def RUN_TESTS()
 *  @brief Macro to run all test cases.
 */
#define RUN_ETESTS()                                                                                \
    for (int i = 0; i < num_tests; ++i)                                                            \
    {                                                                                              \
        printf("-----------------------------------------------------------------------------\n"); \
        ETEST_LOG(INFO, "Running Test: %s-%s", all_tests[i].suite_name, all_tests[i].test_name);   \
        all_tests[i].test_function();                                                              \
        ETEST_LOG(INFO, "Test Passed: %s-%s", all_tests[i].suite_name, all_tests[i].test_name);    \
        printf("-----------------------------------------------------------------------------\n"); \
    }                                                                                              \
    (0)

#endif /* __ETEST__H */

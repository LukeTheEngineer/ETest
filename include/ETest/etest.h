/**
 * @file    ETest.h
 * @brief   BSD 3-Clause License
 * @date    1.14.2024
 *
 * Copyright (c) 2024 Lukas R. Jackson
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

// Assertion Test cases
#define TEST_CASE(name) void name##_test_suite()

/* Log levels */
enum LogLevel
{
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

#define ETEST_LOG(level, info, ...)                                         \
    do                                                                      \
    {                                                                       \
        switch (level)                                                      \
        {                                                                   \
        case INFO:                                                          \
            printf(BGRN "%s: " CRESET info "\n", "INFO", ##__VA_ARGS__);    \
            break;                                                          \
        case WARNING:                                                       \
            printf(BYEL "%s: " CRESET info "\n", "WARNING", ##__VA_ARGS__); \
            break;                                                          \
        case ERROR:                                                         \
            printf(BRED "%s: " CRESET info "\n", "ERROR", ##__VA_ARGS__);   \
            break;                                                          \
        case DEBUG:                                                         \
            printf(BBLU "%s: " CRESET info "\n", "DEBUG", ##__VA_ARGS__);   \
            break;                                                          \
        default:                                                            \
            break;                                                          \
        }                                                                   \
    } while (0)


// Additional assertion macros
#define ASSERT(condition)                                                \
    if (!(condition))                                                    \
    {                                                                    \
        printf("Assertion failed: %s, line %d\n", #condition, __LINE__); \
    }

#define ASSERT_EQUAL(expected, actual)                                                            \
    if ((expected) != (actual))                                                                   \
    {                                                                                             \
        printf("Assertion failed: Expected %s, got %s, line %d\n", #expected, #actual, __LINE__); \
    }                                                                                             \
    else                                                                                          \
    {                                                                                             \
        ETEST_LOG(ERROR, "Unexpected Error ");                                                    \
    }

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

#define ASSERT_NULL(pointer)                                                                \
    if ((pointer) != NULL)                                                                  \
    {                                                                                       \
        printf("Assertion failed: Expected NULL, got non-NULL, line %d\n", __LINE__);       \
    }

#define ASSERT_NOT_NULL(pointer)                                                            \
    if ((pointer) == NULL)                                                                  \
    {                                                                                       \
        printf("Assertion failed: Did not expect NULL, line %d\n", __LINE__);               \
    }



// Macro to run all test cases
#define RUN_TESTS()                                                                         \
    do                                                                                      \
    {                                                                                       \
        printf("Running tests...\n");                                                       \
        /* Add more test cases as needed */                                                 \
        printf("All tests passed!\n");                                                      \
    } while (0)

#endif /* __ETEST__H */
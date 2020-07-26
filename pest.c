#include "pest.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static struct _ts_InternalState g_internal_state;
static int g_status_code = 0;

static char *_ts_AllocateAndPrintf(const char *fmt, ...)
{
    va_list args;
    unsigned character_count;
    va_start(args, fmt);

    {
        va_list temp;
        va_copy(temp, args);

        character_count = vsnprintf(NULL, 0, fmt, temp);

        const int size_of_null_terminator = 1;
        character_count += size_of_null_terminator;

        va_end(temp);
    }

    char *buffer = malloc(character_count * sizeof buffer[0]);
    vsprintf(buffer, fmt, args);

    va_end(args);

    return buffer;
}

void _ts_SetUp(void)
{
    g_internal_state.flags = _TS_INTERNAL_STATE_OK;
    g_internal_state.error_message = NULL;

    setUp();
}

void _ts_TearDown(const char *name, const char *file_string, unsigned line)
{
    tearDown();

    bool test_failed = g_internal_state.flags != _TS_INTERNAL_STATE_OK;

    /* For tests that fail, we want to show more whitespace. */
    printf("%sTEST %s (file %s , line %u) ", test_failed ? "\n" : "", name, file_string, line);

    if (test_failed) {
        printf("FAILED:\n%s\n\n", g_internal_state.error_message);

        bool status_code_has_been_set = g_status_code != 0;

        if (g_internal_state.error_message != NULL) {
            free(g_internal_state.error_message);
        }

        if (!status_code_has_been_set) {
            g_status_code = 1;
        }
    }
    else {
        printf("PASSED.\n");
    }
}

int _ts_GetStatusCode(void)
{
    return g_status_code;
}

bool _ts_AssertTrue(bool condition, const char *str_condition, unsigned line)
{
    if (!condition) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_TRUE(%s) failed on line %u; received '%d'",
                str_condition,
                line,
                condition);
    }

    return condition;
}

bool _ts_AssertFalse(bool condition, const char *str_condition, unsigned line)
{
    if (condition) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_FALSE(%s) failed on line; received '%d'",
                str_condition,
                line,
                condition);
    }

    return !condition;
}

bool _ts_AssertEqual(bool is_equal, const char *str_a, const char *str_b, unsigned line)
{
    if (!is_equal) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL(%s, %s) failed on line %u; expected value of %s is not equal to %s",
                str_a,
                str_b,
                line,
                str_a,
                str_b);
    }

    return is_equal;
}

bool _ts_AssertNotEqual(bool is_not_equal, const char *str_a, const char *str_b, unsigned line)
{
    bool is_equal = !is_not_equal;

    if (is_equal) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL(%s, %s) failed on line %u; expected value of %s is equal to %s",
                str_a,
                str_b,
                line,
                str_a,
                str_b);
    }

    return is_not_equal;
}

bool _ts_AssertNull(void *memory, const char *str_memory, unsigned line)
{
    bool memory_is_null = memory == NULL;

    if (!memory_is_null) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NULL(%s) failed on line %u; expected NULL and instead got %p",
                str_memory,
                line,
                memory);
    }

    return memory_is_null;
}

bool _ts_AssertNotNull(void *memory, const char *str_memory, unsigned line)
{
    bool memory_is_null = memory == NULL;

    if (memory_is_null) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_NULL(%s) failed on line %u; expected a non-NULL address",
                str_memory,
                line);
    }

    return !memory_is_null;
}

bool _ts_AssertEqualInteger(int64_t a, int64_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a != b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_INT(%s, %s) failed on line %u; expected %lld and got %lld",
                str_a,
                str_b,
                line,
                a,
                b);
    }

    return a == b;
}

bool _ts_AssertNotEqualInteger(int64_t a, int64_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a == b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_INT(%s, %s) failed on line %u; both values evaluate to %lld",
                str_a,
                str_b,
                line,
                a);
    }

    return a != b;
}

bool _ts_AssertEqualUnsignedInteger(uint64_t a, uint64_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a != b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_UINT(%s, %s) failed on line %u; expected %llu and got %llu",
                str_a,
                str_b,
                line,
                a,
                b);
    }

    return a == b;
}

bool _ts_AssertNotEqualUnsignedInteger(uint64_t a, uint64_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a == b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_UINT(%s, %s) failed on line %u; both values evaluate to %llu",
                str_a,
                str_b,
                line,
                a);
    }

    return a != b;
}

bool _ts_AssertEqualCharacter(char a, char b, const char *str_a, const char *str_b, unsigned line)
{
    if (a != b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_CHAR(%s, %s) failed on line %u; expected %c and got %c",
                str_a,
                str_b,
                line,
                a,
                b);
    }

    return a == b;
}

bool _ts_AssertNotEqualCharacter(char a, char b, const char *str_a, const char *str_b, unsigned line)
{
    if (a == b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_CHAR(%s, %s) failed on line %u; both values evaluate to %c",
                str_a,
                str_b,
                line,
                a);
    }

    return a != b;
}

bool _ts_AssertEqualWideCharacter(wchar_t a, wchar_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a != b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_WCHAR(%s, %s) failed on line %u; expected %lc and got %lc",
                str_a,
                str_b,
                line,
                a,
                b);
    }

    return a == b;
}

bool _ts_AssertNotEqualWideCharacter(wchar_t a, wchar_t b, const char *str_a, const char *str_b, unsigned line)
{
    if (a == b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_WCHAR(%s, %s) failed on line %u; both values evaluate to %lc",
                str_a,
                str_b,
                line,
                a);
    }

    return a != b;
}

bool _ts_AssertEqualPointer(void *a, void *b, const char *str_a, const char *str_b, unsigned line)
{
    if (a != b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_POINTER(%s, %s) failed on line %u; expected %p and got %p",
                str_a,
                str_b,
                line,
                a,
                b);
    }

    return a == b;
}

bool _ts_AssertNotEqualPointer(void *a, void *b, const char *str_a, const char *str_b, unsigned line)
{
    if (a == b) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_POINTER(%s, %s) failed on line %u; both values evaluate to %p",
                str_a,
                str_b,
                line,
                a);
    }

    return a != b;
}

bool _ts_AssertEqualMemory(void *a, void *b, size_t size, const char *str_a, const char *str_b, const char *str_size, unsigned line)
{
    bool memory_is_equal = memcmp(a, b, size) == 0;

    if (!memory_is_equal) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_EQUAL_MEMORY(%s, %s, %s) failed on line %u; the blocks of memory are not equal",
                str_a,
                str_b,
                str_size,
                line);
    }

    return memory_is_equal;
}

bool _ts_AssertNotEqualMemory(void *a, void *b, size_t size, const char *str_a, const char *str_b, const char *str_size, unsigned line)
{
    bool memory_is_equal = memcmp(a, b, size) == 0;

    if (memory_is_equal) {
        g_internal_state.flags |= _TS_INTERNAL_STATE_ASSERTION_FAILED;

        g_internal_state.error_message = _ts_AllocateAndPrintf(
                "\tASSERT_NOT_EQUAL_MEMORY(%s, %s, %s) failed on line %u; the blocks of memory are equal",
                str_a,
                str_b,
                str_size,
                line);
    }

    return !memory_is_equal;
}



#ifndef PEST_H
#define PEST_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void setUp(void);
extern void tearDown(void);

#define _TS_INTERNAL_STATE_OK               0x00000000
#define _TS_INTERNAL_STATE_ASSERTION_FAILED 0x00000001

struct _ts_InternalState {
    int flags;
    char *error_message;
};

void _ts_SetUp(void);
void _ts_TearDown(const char *name, const char *file_string, unsigned line);

int _ts_GetStatusCode(void);

bool _ts_AssertTrue(bool, const char *, unsigned);
bool _ts_AssertFalse(bool, const char *, unsigned);

bool _ts_AssertEqual(bool, const char *, const char *, unsigned);
bool _ts_AssertNotEqual(bool, const char *, const char *, unsigned);

bool _ts_AssertNull(void *, const char *, unsigned);
bool _ts_AssertNotNull(void *, const char *, unsigned);

bool _ts_AssertEqualInteger(int64_t, int64_t, const char *, const char *, unsigned);
bool _ts_AssertNotEqualInteger(int64_t, int64_t, const char *, const char *, unsigned);

bool _ts_AssertEqualUnsignedInteger(uint64_t, uint64_t, const char *, const char *, unsigned);
bool _ts_AssertNotEqualUnsignedInteger(uint64_t, uint64_t, const char *, const char *, unsigned);

bool _ts_AssertEqualCharacter(char, char, const char *, const char *, unsigned);
bool _ts_AssertNotEqualCharacter(char, char, const char *, const char *, unsigned);

bool _ts_AssertEqualWideCharacter(wchar_t, wchar_t, const char *, const char *, unsigned);
bool _ts_AssertNotEqualWideCharacter(wchar_t, wchar_t, const char *, const char *, unsigned);

bool _ts_AssertEqualPointer(void *, void *, const char *, const char *, unsigned);
bool _ts_AssertNotEqualPointer(void *, void *, const char *, const char *, unsigned);

bool _ts_AssertEqualMemory(void *, void *, size_t, const char *, const char *, const char *, unsigned);
bool _ts_AssertNotEqualMemory(void *, void *, size_t, const char *, const char *, const char *, unsigned);

#define RETURN_ON_FAIL(_expression) if (!(_expression)) return

#define ASSERT_TRUE(_expression) RETURN_ON_FAIL(_ts_AssertTrue(_expression, #_expression, __LINE__))
#define ASSERT_FALSE(_expression) RETURN_ON_FAIL(_ts_AssertFalse(_expression, #_expression, __LINE__))

#define ASSERT_EQUAL(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqual((_expected) == (_actual), #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqual((_expected) != (_actual), #_expected, #_actual, __LINE__))

#define ASSERT_NULL(_expression) RETURN_ON_FAIL(_ts_AssertNull(_expression, #_expression, __LINE__))
#define ASSERT_NOT_NULL(_expression) RETURN_ON_FAIL(_ts_AssertNotNull(_expression, #_expression, __LINE__))

#define ASSERT_EQUAL_INT(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqualInteger((int64_t)_expected, (int64_t)_actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_INT(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqualInteger((int64_t)_expected, (int64_t)_actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_UINT(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqualUnsignedInteger((uint64_t)_expected, (uint64_t)_actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_UINT(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqualUnsignedInteger((uint64_t)_expected, (uint64_t)_actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_CHAR(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqualCharacter(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_CHAR(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqualCharacter(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_WCHAR(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqualWideCharacter(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_WCHAR(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqualWideCharacter(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_POINTER(_expected, _actual) RETURN_ON_FAIL(_ts_AssertEqualPointer(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_POINTER(_expected, _actual) RETURN_ON_FAIL(_ts_AssertNotEqualPointer(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_MEMORY(_expected, _actual, _size) RETURN_ON_FAIL(_ts_AssertEqualMemory(_expected, _actual, _size, #_expected, #_actual, #_size, __LINE__))
#define ASSERT_NOT_EQUAL_MEMORY(_expected, _actual, _size) RETURN_ON_FAIL(_ts_AssertNotEqualMemory(_expected, _actual, _size, #_expected, #_actual, #_size, __LINE__))

#define TEST(_name, ...) void _name(__VA_ARGS__)
#define RUN_TEST(_name, ...) \
        _ts_SetUp(); \
        _name(__VA_ARGS__); \
        _ts_TearDown(#_name, __FILE__, __LINE__)

#define TEST_STATUS() _ts_GetStatusCode()

#endif /* PEST_H */


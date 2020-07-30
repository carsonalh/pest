#ifndef PEST_H
#define PEST_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void setUp(void);
extern void tearDown(void);

#define _PS_INTERNAL_STATE_OK               0x00000000
#define _PS_INTERNAL_STATE_ASSERTION_FAILED 0x00000001

struct _ps_InternalState {
    int flags;
    char *error_message;
};

void _ps_SetUp(void);
void _ps_TearDown(const char *name, const char *file_string, unsigned line);

int _ps_GetStatusCode(void);

bool _ps_AssertTrue(bool, const char *, unsigned);
bool _ps_AssertFalse(bool, const char *, unsigned);

bool _ps_AssertEqual(bool, const char *, const char *, unsigned);
bool _ps_AssertNotEqual(bool, const char *, const char *, unsigned);

bool _ps_AssertNull(void *, const char *, unsigned);
bool _ps_AssertNotNull(void *, const char *, unsigned);

bool _ps_AssertEqualInteger(int64_t, int64_t, const char *, const char *, unsigned);
bool _ps_AssertNotEqualInteger(int64_t, int64_t, const char *, const char *, unsigned);

bool _ps_AssertEqualUnsignedInteger(uint64_t, uint64_t, const char *, const char *, unsigned);
bool _ps_AssertNotEqualUnsignedInteger(uint64_t, uint64_t, const char *, const char *, unsigned);

bool _ps_AssertEqualCharacter(char, char, const char *, const char *, unsigned);
bool _ps_AssertNotEqualCharacter(char, char, const char *, const char *, unsigned);

bool _ps_AssertEqualWideCharacter(wchar_t, wchar_t, const char *, const char *, unsigned);
bool _ps_AssertNotEqualWideCharacter(wchar_t, wchar_t, const char *, const char *, unsigned);

bool _ps_AssertEqualPointer(void *, void *, const char *, const char *, unsigned);
bool _ps_AssertNotEqualPointer(void *, void *, const char *, const char *, unsigned);

bool _ps_AssertEqualMemory(void *, void *, size_t, const char *, const char *, const char *, unsigned);
bool _ps_AssertNotEqualMemory(void *, void *, size_t, const char *, const char *, const char *, unsigned);

#define RETURN_ON_FAIL(_expression) if (!(_expression)) return

#define ASSERT_TRUE(_expression) RETURN_ON_FAIL(_ps_AssertTrue(_expression, #_expression, __LINE__))
#define ASSERT_FALSE(_expression) RETURN_ON_FAIL(_ps_AssertFalse(_expression, #_expression, __LINE__))

#define ASSERT_EQUAL(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqual((_expected) == (_actual), #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqual((_expected) != (_actual), #_expected, #_actual, __LINE__))

#define ASSERT_NULL(_expression) RETURN_ON_FAIL(_ps_AssertNull(_expression, #_expression, __LINE__))
#define ASSERT_NOT_NULL(_expression) RETURN_ON_FAIL(_ps_AssertNotNull(_expression, #_expression, __LINE__))

#define ASSERT_EQUAL_INT(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqualInteger((int64_t)_expected, (int64_t)_actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_INT(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqualInteger((int64_t)_expected, (int64_t)_actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_UINT(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqualUnsignedInteger((uint64_t)_expected, (uint64_t)_actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_UINT(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqualUnsignedInteger((uint64_t)_expected, (uint64_t)_actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_CHAR(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqualCharacter(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_CHAR(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqualCharacter(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_WCHAR(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqualWideCharacter(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_WCHAR(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqualWideCharacter(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_POINTER(_expected, _actual) RETURN_ON_FAIL(_ps_AssertEqualPointer(_expected, _actual, #_expected, #_actual, __LINE__))
#define ASSERT_NOT_EQUAL_POINTER(_expected, _actual) RETURN_ON_FAIL(_ps_AssertNotEqualPointer(_expected, _actual, #_expected, #_actual, __LINE__))

#define ASSERT_EQUAL_MEMORY(_expected, _actual, _size) RETURN_ON_FAIL(_ps_AssertEqualMemory(_expected, _actual, _size, #_expected, #_actual, #_size, __LINE__))
#define ASSERT_NOT_EQUAL_MEMORY(_expected, _actual, _size) RETURN_ON_FAIL(_ps_AssertNotEqualMemory(_expected, _actual, _size, #_expected, #_actual, #_size, __LINE__))

#define TEST(_name, ...) void _name(__VA_ARGS__)
#define RUN_TEST(_name, ...) \
        _ps_SetUp(); \
        _name(__VA_ARGS__); \
        _ps_TearDown(#_name, __FILE__, __LINE__)

#define TEST_STATUS() _ps_GetStatusCode()

#endif /* PEST_H */


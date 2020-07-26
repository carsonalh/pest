#include "test.h"

#include <stdbool.h>

void setUp(void) {}
void tearDown(void) {}

TEST(passEqual)
{
    ASSERT_EQUAL(1, 1);
}

TEST(passNotEqual)
{
    ASSERT_NOT_EQUAL(3, 4);
}

TEST(passNull)
{
    ASSERT_NULL(NULL);
}

TEST(passNotNull)
{
    void *pointer = (void *)&pointer;
    ASSERT_NOT_NULL(pointer);
}

TEST(passEqualInteger)
{
    short a = 1, b = 1;

    ASSERT_EQUAL_INT(a, b);
}

TEST(passNotEqualInteger)
{
    long long a = 12LL, b = 21LL;

    ASSERT_NOT_EQUAL_INT(a, b + 1LL);
}

TEST(passEqualUnsignedInteger)
{
    unsigned long long a = 12ULL, b = 12ULL;

    ASSERT_EQUAL_UINT(a, b);
}

TEST(passNotEqualUnsignedInteger)
{
    ASSERT_NOT_EQUAL_UINT(0, 1);
}

TEST(passEqualChar)
{
    char a = 'a', b = 'a';

    ASSERT_EQUAL_CHAR(a, b);
}

TEST(passNotEqualChar)
{
    char a = 'a', b = 'b';

    ASSERT_NOT_EQUAL_CHAR(a, b);
}

TEST(passEqualWideChar)
{
    wchar_t a = L'a', b = L'a';

    ASSERT_EQUAL_WCHAR(a, b);
}

TEST(passNotEqualWideChar)
{
    wchar_t a = L'a', b = L'b';

    ASSERT_NOT_EQUAL_WCHAR(a, b);
}

TEST(passEqualPointer)
{
    void *pointer = (void *)&pointer;

    ASSERT_EQUAL_POINTER(***(void ****)pointer, pointer);
}

TEST(passNotEqualPointer)
{
    void *pointer = (void *)&pointer;

    ASSERT_NOT_EQUAL_POINTER(pointer, (int *)pointer + 1);
}

TEST(passEqualMemory)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 1, 2, 3 };

    ASSERT_EQUAL_MEMORY(a, b, sizeof a);
}

TEST(passNotEqualMemory)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 3, 3, 3 };

    ASSERT_NOT_EQUAL_MEMORY(a, b, sizeof a);
}

TEST(failEqual)
{
    ASSERT_EQUAL(1, 2);
}

TEST(failNotEqual)
{
    ASSERT_NOT_EQUAL(3, 4 - 1);
}

TEST(failNull)
{
    int a;
    void *memory = &a;

    ASSERT_NULL(memory);
}

TEST(failNotNull)
{
    void *pointer = NULL;

    ASSERT_NOT_NULL(pointer);
}

TEST(failEqualInteger)
{
    short a = 1, b = 2;

    ASSERT_EQUAL_INT(a, b);
}

TEST(failNotEqualInteger)
{
    long long a = 12LL, b = 11LL;

    ASSERT_NOT_EQUAL_INT(a, b + 1LL);
}

TEST(failEqualUnsignedInteger)
{
    unsigned long long a = 12ULL, b = 11ULL;

    ASSERT_EQUAL_UINT(a, b);
}

TEST(failNotEqualUnsignedInteger)
{
    unsigned short a = 12;

    ASSERT_NOT_EQUAL_UINT(a, a);
}

TEST(failEqualChar)
{
    char a = 'a', b = 'b';

    ASSERT_EQUAL_CHAR(a, b);
}

TEST(failNotEqualChar)
{
    char a = 'a';

    ASSERT_NOT_EQUAL_CHAR(a, a);
}

TEST(failEqualWideChar)
{
    wchar_t a = L'a', b = L'b';

    ASSERT_EQUAL_WCHAR(a, b);
}

TEST(failNotEqualWideChar)
{
    wchar_t a = L'a';

    ASSERT_NOT_EQUAL_WCHAR(a, a);
}

TEST(failEqualPointer)
{
    int a, b;
    void *a_pointer = &a, *b_pointer = &b;

    ASSERT_EQUAL_POINTER(a_pointer, b_pointer);
}

TEST(failNotEqualPointer)
{
    int a, *a_pointer = &a;

    ASSERT_NOT_EQUAL_POINTER(a_pointer, a_pointer);
}

TEST(failEqualMemory)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 3, 2, 1 };

    ASSERT_EQUAL_MEMORY(a, b, sizeof a);
}

TEST(failNotEqualMemory)
{
    int a[3] = { 1, 2, 3 };
    int b[3] = { 1, 2, 3 };

    ASSERT_NOT_EQUAL_MEMORY(a, b, sizeof a);
}

int main(void)
{
    RUN_TEST(passEqual);
    RUN_TEST(passNotEqual);
    RUN_TEST(passNull);
    RUN_TEST(passNotNull);
    RUN_TEST(passEqualInteger);
    RUN_TEST(passNotEqualInteger);
    RUN_TEST(passEqualUnsignedInteger);
    RUN_TEST(passNotEqualUnsignedInteger);
    RUN_TEST(passEqualChar);
    RUN_TEST(passNotEqualChar);
    RUN_TEST(passEqualWideChar);
    RUN_TEST(passNotEqualWideChar);
    RUN_TEST(passEqualPointer);
    RUN_TEST(passNotEqualPointer);
    RUN_TEST(passEqualMemory);
    RUN_TEST(passNotEqualMemory);

    RUN_TEST(failEqual);
    RUN_TEST(failNotEqual);
    RUN_TEST(failNull);
    RUN_TEST(failNotNull);
    RUN_TEST(failEqualInteger);
    RUN_TEST(failNotEqualInteger);
    RUN_TEST(failEqualUnsignedInteger);
    RUN_TEST(failNotEqualUnsignedInteger);
    RUN_TEST(failEqualChar);
    RUN_TEST(failNotEqualChar);
    RUN_TEST(failEqualWideChar);
    RUN_TEST(failNotEqualWideChar);
    RUN_TEST(failEqualPointer);
    RUN_TEST(failNotEqualPointer);
    RUN_TEST(failEqualMemory);
    RUN_TEST(failNotEqualMemory);

    return TEST_STATUS();
}


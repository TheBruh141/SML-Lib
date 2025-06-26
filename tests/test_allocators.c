//
// Created by bruh on 6/26/25.
//
#include "unity.h"
#include "allocators.h" // The header for the code we're testing
#include <limits.h>     // For ULLONG_MAX
#include <stdlib.h>     // For free()
#include <string.h>     // For memset()

// --- Unity Setup/Teardown ---
void setUp(void) {}
void tearDown(void) {}

// --- Tests for sml_malloc ---

void test_sml_malloc_basic_allocation(void) {
    // Test: A standard, valid allocation should succeed.
    void *ptr = sml_malloc(100);
    TEST_ASSERT_NOT_NULL(ptr);
    free(ptr);
}

void test_sml_malloc_zero_size_allocation(void) {
    // Test: Allocating zero bytes should return NULL as per our implementation.
    void *ptr = sml_malloc(0);
    TEST_ASSERT_NULL(ptr);
}

// --- Tests for sml_calloc ---

void test_sml_calloc_basic_allocation_and_zeroing(void) {
    // Test: A standard calloc should succeed and the memory should be zeroed.
    size_t num_elements = 10;
    size_t element_size = sizeof(int);
    int *ptr = sml_calloc(num_elements, element_size);
    TEST_ASSERT_NOT_NULL(ptr);

    // Create an array of zeroes to compare against.
    int expected_zeroes[10] = {0};
    TEST_ASSERT_EQUAL_MEMORY(expected_zeroes, ptr, num_elements * element_size);

    free(ptr);
}

void test_sml_calloc_zero_size_allocation(void) {
    // Test: Allocating zero elements or elements of zero size should return NULL.
    TEST_ASSERT_NULL(sml_calloc(0, sizeof(int)));
    TEST_ASSERT_NULL(sml_calloc(10, 0));
}

void test_sml_calloc_overflow_check(void) {
    // Test: An allocation request that would overflow should return NULL.
    void *ptr = sml_calloc(ULLONG_MAX, 2);
    TEST_ASSERT_NULL(ptr);
}

// --- Tests for sml_alloc ---

void test_sml_alloc_delegates_correctly(void) {
    // Test: A standard allocation should succeed.
    // In a non-DEBUG build, this calls sml_malloc. In DEBUG, it calls sml_calloc.
    int *ptr = sml_alloc(10, sizeof(int));
    TEST_ASSERT_NOT_NULL(ptr);

#ifdef DEBUG
    // If in DEBUG mode, verify that memory is zeroed.
    int expected_zeroes[10] = {0};
    TEST_ASSERT_EQUAL_MEMORY(expected_zeroes, ptr, 10 * sizeof(int));
#endif

    free(ptr);
}

void test_sml_alloc_zero_size(void) {
    // Test: Zero-size requests should return NULL.
    TEST_ASSERT_NULL(sml_alloc(0, 10));
    TEST_ASSERT_NULL(sml_alloc(10, 0));
}

void test_sml_alloc_overflow_check(void) {
    // Test: Overflow check should prevent allocation and return NULL.
    TEST_ASSERT_NULL(sml_alloc(ULLONG_MAX, 2));
}

// --- Tests for sml_realloc ---

void test_sml_realloc_from_null_behaves_like_malloc(void) {
    // Test: Reallocating a NULL pointer should be equivalent to malloc.
    void *ptr = sml_realloc(NULL, 100, 0);
    TEST_ASSERT_NOT_NULL(ptr);
    free(ptr);
}

void test_sml_realloc_to_zero_behaves_like_free(void) {
    // Test: Reallocating to zero size should free the memory and return NULL.
    void *ptr = sml_malloc(100);
    TEST_ASSERT_NOT_NULL(ptr);
    ptr = sml_realloc(ptr, 0, 0);
    TEST_ASSERT_NULL(ptr);
    // Note: The memory is freed, no need to call free(ptr) again.
}

void test_sml_realloc_grow_and_preserve_data(void) {
    // Test: Growing a memory block should preserve its original content.
    char *ptr = sml_malloc(10);
    TEST_ASSERT_NOT_NULL(ptr);
    strcpy(ptr, "testing"); // 7 chars + null terminator

    char *new_ptr = sml_realloc(ptr, 20, 0);
    TEST_ASSERT_NOT_NULL(new_ptr);
    TEST_ASSERT_EQUAL_STRING("testing", new_ptr);

    free(new_ptr);
}

void test_sml_realloc_shrink_and_preserve_data(void) {
    // Test: Shrinking a memory block should preserve content up to the new size.
    char *ptr = sml_malloc(20);
    TEST_ASSERT_NOT_NULL(ptr);
    strcpy(ptr, "testing realloc");

    char *new_ptr = sml_realloc(ptr, 8, 0);
    TEST_ASSERT_NOT_NULL(new_ptr);
    TEST_ASSERT_EQUAL_STRING_LEN("testing", new_ptr, 7);

    free(new_ptr);
}

// --- Tests for sml_realloc_change_place ---

void test_sml_realloc_change_place_bytes_grow(void) {
    // Test: Growing memory should allocate a new block and copy data.
    int *ptr = sml_malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) ptr[i] = i + 1;

    int *new_ptr = sml_realloc_change_place_bytes(ptr, 5 * sizeof(int), 10 * sizeof(int));
    TEST_ASSERT_NOT_NULL(new_ptr);
    TEST_ASSERT_NOT_EQUAL(ptr, new_ptr); // Should be a new location

    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL_INT(i + 1, new_ptr[i]);
    }
    free(new_ptr);
}

void test_sml_realloc_change_place_elements_shrink(void) {
    // Test: Shrinking memory with the element-based function.
    char *ptr = sml_alloc(10, sizeof(char));
    strcpy(ptr, "123456789");

    char *new_ptr = sml_realloc_change_place_elements(ptr, 10, sizeof(char), 5);
    TEST_ASSERT_NOT_NULL(new_ptr);
    TEST_ASSERT_EQUAL_STRING_LEN("12345", new_ptr, 5);
    free(new_ptr);
}

void test_sml_realloc_change_place_elements_zero_element_size(void) {
    // Test: Calling with element_size = 0 should fail and return NULL.
    void* ptr = sml_malloc(10);
    TEST_ASSERT_NULL(sml_realloc_change_place_elements(ptr, 10, 0, 5));
    free(ptr); // Original pointer should be untouched.
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_sml_malloc_basic_allocation);
    RUN_TEST(test_sml_malloc_zero_size_allocation);

    RUN_TEST(test_sml_calloc_basic_allocation_and_zeroing);
    RUN_TEST(test_sml_calloc_zero_size_allocation);
    RUN_TEST(test_sml_calloc_overflow_check);

    RUN_TEST(test_sml_alloc_delegates_correctly);
    RUN_TEST(test_sml_alloc_zero_size);
    RUN_TEST(test_sml_alloc_overflow_check);

    RUN_TEST(test_sml_realloc_from_null_behaves_like_malloc);
    RUN_TEST(test_sml_realloc_to_zero_behaves_like_free);
    RUN_TEST(test_sml_realloc_grow_and_preserve_data);
    RUN_TEST(test_sml_realloc_shrink_and_preserve_data);

    RUN_TEST(test_sml_realloc_change_place_bytes_grow);
    RUN_TEST(test_sml_realloc_change_place_elements_shrink);
    RUN_TEST(test_sml_realloc_change_place_elements_zero_element_size);

    return UNITY_END();
}
//
// Created by bruh on 6/26/25.
//


#include "allocators.h"// The header for the code we're testing
#include "unity.h"
#include <limits.h>// For ULLONG_MAX
#include <stdlib.h>// For free()
#include <string.h>// For memset()


// --- Unity Setup/Teardown ---
void setUp(void) {}
void tearDown(void) {}

// --- Tests ---
void test_sml_malloc_simulated_failure(void) {
#ifndef SML_MALLOC_FAILURE
    TEST_IGNORE_MESSAGE("Compile with -D SML_MALLOC_FAILURE to run this test");
#endif
    // Test: Ensure sml_malloc returns NULL when the failure macro is defined.
    TEST_ASSERT_NULL(sml_malloc(100));
}

void test_sml_calloc_simulated_failure(void) {
#ifndef SML_CALLOC_FAILURE
    TEST_IGNORE_MESSAGE("Compile with -D SML_CALLOC_FAILURE to run this test");
#endif
    // Test: Ensure sml_calloc returns NULL when the failure macro is defined.
    TEST_ASSERT_NULL(sml_calloc(10, sizeof(int)));
}
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_sml_malloc_simulated_failure);
    RUN_TEST(test_sml_calloc_simulated_failure);

    return UNITY_END();
}
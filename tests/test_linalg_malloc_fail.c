//
// Created by bruh on 6/25/25.
//

#include "allocators.h"
#include "unity.h"
#include <linalg.h>

//TODO: implement malloc testing

void setUp(void) {}
void tearDown(void) {}

void test_new_vec_f_malloc_failure(void) {
    Vector_f v = new_vec_f(5, 3, 1.0f, 2.0f, 3.0f);
    TEST_ASSERT_EQUAL_size_t(0, v.size);
    TEST_ASSERT_NULL(v.data);
}

void test_new_vec_f_zeroes_malloc_failure(void) {
    Vector_f v = new_vec_f_zeroes(5);
    TEST_ASSERT_EQUAL_size_t(5, v.size);
    TEST_ASSERT_NULL(v.data);
}

void test_as_string_vec_f_empty_malloc_failure(void) {
    // for an empty vector, as_string_vec_f does a malloc(3)
    Vector_f v = { .size = 0, .data = NULL };
    char *s = as_string_vec_f(v);
    TEST_ASSERT_NULL(s);
}

void test_new_mat_f_malloc_failure(void) {
    Matrix_f m = new_mat_f(4, 3, 2, 2, 1.0f);
    TEST_ASSERT_EQUAL_size_t(4, m.width);   // width/height are preserved
    TEST_ASSERT_EQUAL_size_t(3, m.height);
    TEST_ASSERT_NULL(m.data);
}

int main(void) {
#ifdef SML_TEST_ALLOC_FAILURE
    printf("SML_TEST_MALLOC_FAILURE\n");
#endif
    UNITY_BEGIN();
    RUN_TEST(test_new_vec_f_malloc_failure);
    RUN_TEST(test_new_vec_f_zeroes_malloc_failure);
    RUN_TEST(test_as_string_vec_f_empty_malloc_failure);
    RUN_TEST(test_new_mat_f_malloc_failure);
    return UNITY_END();
}


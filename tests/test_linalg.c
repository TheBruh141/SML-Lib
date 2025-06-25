#include "unity.h"
#include <linalg.h>
#include <stdlib.h>
#include <string.h>


// Optional setup function required by Unity
void setUp(void) {
}


// Optional teardown function required by Unity
void tearDown(void) {
    // Nothing to do here
}

void test_zero_size_vector(void) {
    Vector_f v = new_vec_f(0, 1, 3.14f);
    TEST_ASSERT_EQUAL_size_t(0, v.size);
    TEST_ASSERT_NULL(v.data);
}


void test_zero_given_values(void) {
    Vector_f v = new_vec_f(3, 0, 0.0f); // value won't be used
    TEST_ASSERT_EQUAL_size_t(3, v.size);
    TEST_ASSERT_NOT_NULL(v.data);
    // You can't assert value contents here, undefined
    free_vec_f(v);
}

void test_fewer_values_than_size(void) {
    Vector_f v = new_vec_f(5, 3, 1.0f, 2.0f, 3.0f);
    TEST_ASSERT_EQUAL_size_t(5, v.size);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, v.data[0]);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, v.data[1]);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, v.data[2]);
    // v.data[3] and [4] are garbage; don’t assert
    free_vec_f(v);
}

void test_more_values_than_size(void) {
    Vector_f v = new_vec_f(3, 5, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
    TEST_ASSERT_EQUAL_size_t(3, v.size);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, v.data[0]);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, v.data[1]);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, v.data[2]);
    free_vec_f(v);
}

void test_new_vec_zeroes(void) {
    const Vector_f v = new_vec_f_zeroes(4);
    const float expected[] = {0,0,0,0};
    TEST_ASSERT_EQUAL_size_t(4, v.size);
    TEST_ASSERT_EQUAL_FLOAT_ARRAY( expected, v.data, 4);
    // printf("\n%s\n", as_string_vec_f(v));
    free_vec_f(v);

}

void test_as_string_vec_f_creates_correct_string(void) {
    const Vector_f v = new_vec_f(2, 2, -1.f, 23.f);
    const Vector_f empty = new_vec_f(0, 0, 0);
    char* s = as_string_vec_f(v);
    char* s_empty = as_string_vec_f(empty);

    TEST_ASSERT_EQUAL_STRING(s_empty, "[]");
    TEST_ASSERT_EQUAL_STRING(s, "[-1.00, 23.00]");

    free_vec_f(v);
    free(s);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_zero_size_vector);
    RUN_TEST(test_more_values_than_size);
    RUN_TEST(test_zero_given_values);
    RUN_TEST(test_new_vec_zeroes);
    RUN_TEST(test_fewer_values_than_size);
    RUN_TEST(test_as_string_vec_f_creates_correct_string);

    return UNITY_END();
}

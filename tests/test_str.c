#include "unity.h"
#include "sml_str.h"

void setUp(void) {}
void tearDown(void) {}

void test_new_empty_string(void) {
    sml_str *s = sml_str_new(NULL);
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL(0, s->capacity);
    TEST_ASSERT_EQUAL(0, s->last_index);
    TEST_ASSERT_NULL(s->contents);
    sml_str_free(s);
}

void test_new_string_with_contents(void) {
    sml_str *s = sml_str_new("Hi");
    TEST_ASSERT_NOT_NULL(s);
    TEST_ASSERT_EQUAL_STRING("Hi", s->contents);
    sml_str_free(s);
}

void test_append_works(void) {
    sml_str *s = sml_str_new("A");
    TEST_ASSERT_TRUE(sml_str_append(s, "BC"));
    TEST_ASSERT_EQUAL_STRING("ABC", s->contents);
    sml_str_free(s);
}

void test_substr(void) {
    char *sub = sml_str_get_sub_str("Hello World", 0, 5);
    TEST_ASSERT_EQUAL_STRING("Hello", sub);
    free(sub);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_empty_string);
    RUN_TEST(test_new_string_with_contents);
    RUN_TEST(test_append_works);
    RUN_TEST(test_substr);
    return UNITY_END();
}

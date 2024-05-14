#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_bindings.h"
#include "sml_cstr.h"

// Define the sml_cstr_array struct and functions (already provided)

// Function to stress test the sml_cstr_array library
void stress_test_sml_cstr_array() {
    // Create an empty sml_cstr_array
    sml_cstr_array *array = sml_cstr_array_new_empty();

    // Test sml_cstr_array_new_with_capacity
    sml_cstr_array *array_capacity = sml_cstr_array_new_with_capacity(10);

    // Test sml_cstr_array_from_string
    char str[] = "This is a test string for sml_cstr_array";
    char delim[] = " ";
    sml_cstr_array *array_from_string = sml_cstr_array_from_string(str, delim);

    // Test sml_cstr_array_from_array
    char *test_strings[] = {"One", "Two", "Three", "Four", "Five"};
    sml_size size = sizeof(test_strings) / sizeof(test_strings[0]);
    sml_cstr_array *array_from_array = sml_cstr_array_from_array(test_strings, size);

    // Test sml_cstr_array_append
    sml_cstr_array_append(array, "String 1");
    sml_cstr_array_append(array, "String 2");
    sml_cstr_array_append(array, "String 3");

    // Test sml_cstr_array_get
    char *retrieved_string = sml_cstr_array_get(array, 1);
    if (retrieved_string != NULL) {
        printf("String at index 1: %s\n", retrieved_string);
    }

    // Test sml_cstr_array_merge
    sml_cstr_array *array_to_merge = sml_cstr_array_new_empty();
    sml_cstr_array_append(array_to_merge, "Merge1");
    sml_cstr_array_append(array_to_merge, "Merge2");
    char *merged_string = sml_cstr_array_merge(array, array_to_merge);
    if (merged_string != NULL) {
        printf("Merged string: %s\n", merged_string);
        free(merged_string);
    }

    // Test sml_cstr_array_join
    char *joined_string = sml_cstr_array_join(array, ",");
    if (joined_string != NULL) {
        printf("Joined string: %s\n", joined_string);
        free(joined_string);
    }

    // Test sml_cstr_array_to_string
    char *array_to_string = sml_cstr_array_to_string(array);
    if (array_to_string != NULL) {
        printf("Array to string: %s\n", array_to_string);
        free(array_to_string);
    }

    // Free memory allocated for arrays
    sml_cstr_array_free(array);
    sml_cstr_array_free(array_capacity);
    sml_cstr_array_free(array_from_string);
    sml_cstr_array_free(array_from_array);
    sml_cstr_array_free(array_to_merge);
}

// Main function to run stress tests
int main() {
    stress_test_sml_cstr_array();
    return 0;
}

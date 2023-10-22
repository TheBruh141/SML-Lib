//
// Created by bruh on 10/7/23.
//

#include <stdio.h>
#include "common_bindings.h"
#include "argument_parsing.h"
#include "for_each.h"
#include "file_utils.h"
#include "sml_str.h"

int main(void) {
#if (0 == 1)
    printf("hello you!\n");
    printf("this is a file where you can try sml_lib without copying it :D\n");

    sml_error_config err_conf = init_sml_error(
            "SML_SANDBOX",
            false,
            NULL
    );

    // math.h does not rely on any preexisting math library. Let's check accuracy!
    printf("%f", LOGARITHM_ACC);

    // since we know that sin^2 + cos^2 = 1
    for (sml_size_t degree = 0; degree < 90; degree++) {
        printf("sin = %f, cos = %f, Accuracy = %f\n", sml_sin(degree), sml_cos(degree),
               sml_float_abs((sml_pow(sml_sin(degree), 2) + sml_pow(sml_cos(degree), 2))));
    }
    // note that using --fast-math will change the output since we are not using any platform/compiler-specific instructions
    // or any fancy tricks. This is pure math/skill issues.
    sml_throw_error(&err_conf, ERROR_OK, LOG_SEVERITY_INFO, "DONE!, %s", "With Style");
#elif(2 == 1)

    sml_arg_parse_cfg cfg[] = {
            {"-Wall",    "Invalid usage of -Wall",    "Enable all warnings"},
            {"-Wextra",  "Invalid usage of -Wextra",  "Enable extra warnings"},
            {"-grep",    "Invalid usage of -grep",    "Search for a string"},
            {"-O",       "Invalid usage of -O",       "Set optimization level"},
            {"-feature", "Invalid usage of -feature", "Enable or disable a feature"},
    };

    // Sample argument definitions
    sml_arg args[] = {
            {sml_arg_type_basic,  "-Wall",    "--enable-warnings",       "Enable all warnings"},
            {sml_arg_type_basic,  "-Wextra",  "--enable-extra-warnings", "Enable extra warnings"},
            {sml_arg_type_string, "-grep",    "--search",                "Search for a string"},
            {sml_arg_type_digit,  "-O",       "--optimization-level",    "Set optimization level"},
            {sml_arg_type_yes_no, "-feature", "--enable-feature",        "Enable or disable a feature"},
    };

    sml_arg_array arg_array;
    arg_array.arguments = args;
    arg_array.capacity = sizeof(args) / sizeof(sml_arg);
    arg_array.last_element_index = arg_array.capacity;

    // Test Case 1: Basic Argument - Testing basic arguments -Wall and -Wextra
    char *test_case1[] = {"program", "-Wall", "-Wextra"};
    if (sml_arg_parse(3, test_case1, &arg_array, cfg)) {
        printf("Test Case 1 Passed\n");
    } else {
        printf("Test Case 1 Failed\n");
    }

    // Test Case 2: String Argument - Testing string argument -grep "asd"
    char *test_case2[] = {"program", "-grep", "asd"};
    if (sml_arg_parse(3, test_case2, &arg_array, cfg)) {
        printf("Test Case 2 Passed\n");
    } else {
        printf("Test Case 2 Failed\n");
    }

    // Test Case 3: Digit Argument - Testing digit argument -O3
    char *test_case3[] = {"program", "-O3"};
    if (sml_arg_parse(2, test_case3, &arg_array, cfg)) {
        printf("Test Case 3 Passed\n");
    } else {
        printf("Test Case 3 Failed\n");
    }

    // Test Case 4: Yes/No Argument - Testing yes/no argument -feature=true
    char *test_case4[] = {"program", "-feature=true"};
    if (sml_arg_parse(2, test_case4, &arg_array, cfg)) {
        printf("Test Case 4 Passed\n");
    } else {
        printf("Test Case 4 Failed\n");
    }

    // Test Case 5: Invalid Argument - Testing an invalid argument -xyz
    char *test_case5[] = {"program", "-xyz"};
    if (!sml_arg_parse(2, test_case5, &arg_array, cfg)) {
        printf("Test Case 5 Passed\n");
    } else {
        printf("Test Case 5 Failed\n");
    }
#else

#endif
    return 0;
}

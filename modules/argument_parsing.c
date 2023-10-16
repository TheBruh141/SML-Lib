//
// Created by bruhpc on 10/14/23.
//
#include <stdio.h>

// THIS CODE IS NOT TESTED DO NOT PUSH
#include "argument_parsing.h"
#include "common_bindings.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


sml_arg *new_sml_arg(enum sml_arg_type type, char *short_name, char *long_name, char *usage) {
    sml_arg *new = (sml_arg *) malloc(sizeof(sml_arg));

    CHECK_MEM(new);

    if (strlen(short_name) > 4) {
        fprintf(stderr,
                "\n[SML_LIB_ARGUMENT_PARSING] : short_name parameter cannot be longer than 4 characters. ie char[4]\n Currently it is \n\tshort_name = %s",
                short_name);
        EXIT_WITH_INFO;
    }

    new->type = type;
    new->long_name = long_name;
    new->short_name = short_name;
    new->usage = usage;

    return new;
}

sml_arg_array *new_sml_arg_array(unsigned long long int expected_size) {
    sml_arg_array *new = (sml_arg_array *) malloc(sizeof(sml_arg_array));
    sml_arg *new_content = (sml_arg *) malloc(sizeof(sml_arg) * expected_size);

    CHECK_MEM(new);
    CHECK_MEM(new_content);

    new->capacity = expected_size;
    new->last_element_index = 0;
    new->arguments = new_content;

    return new;
}

void sml_arg_array_append(sml_arg_array *arr, sml_arg *arg) {
    // double array
    if (arr->capacity == arr->last_element_index) {
        arr->capacity *= 2;
        sml_arg *temp = NULL;
        unsigned retry_count = 0;

        while (retry_count < 2 << 5) {
            temp = (sml_arg *) realloc(arr->arguments, arr->capacity * sizeof(sml_arg));
            if (temp != NULL) {
                arr->arguments = temp;
                break; // Allocation successful, exit the loop
            }

            // Allocation failed, increase retry_count, and possibly handle the failure here
            retry_count++;
            fprintf(stderr, "[SML_ARGUMENT_PARSING] : realloc failed, retrying (%02d)\n", retry_count);

        }

        if (temp == NULL) {
            // Handle the failure, e.g., by exiting the program or returning an error code.
            fprintf(stderr, "[SML_ARGUMENT_PARSING] : realloc failed in sml_arg_array_append. :c\nexiting... ");
            EXIT_WITH_INFO;
        }
    }
    arr->arguments[arr->last_element_index++] = *arg;
}

void sml_arg_print_usages(sml_arg_array *args) {
    printf("usages:\n");
    for (unsigned long long i = 0; i < args->last_element_index; i++) {
        printf("\t-%3s, --%15s : %s\n", args->arguments[i].short_name, args->arguments[i].long_name,
               args->arguments[i].usage);
    }
}

void free_sml_arg(sml_arg *arg_to_be_freed) {
    if (arg_to_be_freed != NULL) {
        free(arg_to_be_freed);
    }
}

void free_sml_arg_array(sml_arg_array *args_to_be_freed) {
    free(args_to_be_freed);
}

// this might look scary at first.
// this is my tenth time it does not get better

bool sml_arg_parse(int argc, char **argv, sml_arg_array *args, sml_arg_parse_cfg *cfg) {
    // Initialize an array of boolean values to track argument parsing results
    bool *arg_parsed = (bool *) calloc(args->capacity, sizeof(bool));
    if (arg_parsed == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for arg_parsed.\n");
        return false;
    }

    // Iterate through command-line arguments
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        bool arg_matched = false;

        // Iterate through the sml_arg_array to find a matching argument
        for (unsigned long long j = 0; j < args->last_element_index; j++) {
            if (arg_parsed[j]) {
                continue;  // Skip already parsed arguments
            }
            sml_arg *smlarg = &args->arguments[j];

            // Check if the argument matches the short or long name
            if (strcmp(arg, smlarg->short_name) == 0 || strcmp(arg, smlarg->long_name) == 0) {
                // Handle argument parsing based on the argument type
                switch (smlarg->type) {
                    case sml_arg_type_basic:
                        // Implement basic argument parsing logic here
                        // Example: -Wall, -Wextra
                        // Set the parsed flag
                        arg_parsed[j] = true;
                        arg_matched = true;
                        break;

                    case sml_arg_type_string:
                        // Implement string argument parsing logic here
                        // Example: -grep "asd"
                        // Ensure that there is a next argument and not already parsed
                        if (i + 1 < argc && !arg_parsed[j + 1]) {
                            // Set the parsed flag for both the argument and its value
                            arg_parsed[j] = true;
                            arg_parsed[j + 1] = true;
                            arg_matched = true;
                            i++;  // Skip the value
                        } else {
                            fprintf(stderr, "Error: Argument %s requires a value.\n", arg);
                            return false;
                        }
                        break;

                    case sml_arg_type_digit:
                        // Implement digit argument parsing logic here
                        // Example: -O3, -O2, -O=3
                        // Ensure that there is a next argument and not already parsed
                        if (i + 1 < argc && !arg_parsed[j + 1]) {
                            const char *next_arg = argv[i + 1];
                            if (next_arg[0] == '-' && next_arg[1] != '\0') {
                                // The next argument is another flag, so we treat it as the value
                                arg_parsed[j] = true;
                            } else {
                                // The next argument is the value
                                if (next_arg[0] == '=')
                                    next_arg++;  // Remove any leading '='
                                if ((next_arg) < 0) {
                                    fprintf(stderr, "Error: Argument %s requires a positive integer value.\n", arg);
                                    free(arg_parsed);
                                    return false;
                                }
                                // Set the parsed flag for both the argument and its value
                                arg_parsed[j] = true;
                                arg_parsed[j + 1] = true;
                                i++;  // Skip the value
                            }
                            arg_matched = true;
                        } else {
                            fprintf(stderr, "Error: Argument %s requires a value.\n", arg);
                            free(arg_parsed);
                            return false;
                        }
                        break;

                    case sml_arg_type_yes_no:
                        // Implement yes/no argument parsing logic here
                        // Example: -feature=true, -feature=1
                        // Ensure that there is a next argument and not already parsed
                        if (i + 1 < argc && !arg_parsed[j + 1]) {
                            const char *next_arg = argv[i + 1];
                            if (next_arg[0] == '-' && next_arg[1] != '\0') {
                                // The next argument is another flag, so we treat it as the value
                                arg_parsed[j] = true;
                            } else {
                                // The next argument is the value
                                if (next_arg[0] == '=')
                                    next_arg++;  // Remove any leading '='
                                if (strcmp(next_arg, "true") == 0 || strcmp(next_arg, "1") == 0) {
                                    // Set the parsed flag for both the argument and its value
                                    arg_parsed[j] = true;
                                    arg_parsed[j + 1] = true;
                                    i++;  // Skip the value
                                } else {
                                    fprintf(stderr, "Error: Argument %s requires a 'true' or '1' value.\n", arg);
                                    free(arg_parsed);
                                    return false;
                                }
                            }
                            arg_matched = true;
                        } else {
                            fprintf(stderr, "Error: Argument %s requires a value.\n", arg);
                            free(arg_parsed);
                            return false;
                        }
                        break;

                    default:
                        fprintf(stderr, "Error: Unrecognized argument type for %s.\n", arg);
                        free(arg_parsed);
                        return false;
                }
            }
        }

        // If the argument is not recognized, show an error message
        if (!arg_matched) {
            fprintf(stderr, "Error: Unrecognized argument %s.\n", arg);
            free(arg_parsed);
            return false;
        }
    }

    // Free the dynamically allocated memory
    free(arg_parsed);

    return true;
}

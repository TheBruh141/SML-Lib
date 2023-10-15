//
// Created by bruhpc on 10/14/23.
//
#include <stdio.h>

// THIS CODE IS NOT TESTED DO NOT PUSH
#include "argument_parsing.h"
#include "common_bindings.h"

#include <stdlib.h>
#include <stdbool.h>


sml_arg *new_sml_arg(enum sml_arg_type type, char *short_name, char *long_name, char *usage) {
    sml_arg *new = (sml_arg *) malloc(sizeof(sml_arg));

    CHECK_MEM(new);

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

//bool *sml_arg_parse(int argc, char *argv, sml_arg_array *args) {
//    // we are using calloc because we are wanting everything to be zero
//    bool* truth_table = calloc(sizeof(bool), args->last_element_index);
//
//    for each(arg, argv) {
//
//    }
//
//    return truth_table;
//}

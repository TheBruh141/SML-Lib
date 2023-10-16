//
// Created by bruhpc on 10/14/23.
//

#ifndef SML_DIALECT_ARGUMENT_PARSING_H
#define SML_DIALECT_ARGUMENT_PARSING_H

#include <stdbool.h>
#include "common_bindings.h"

enum sml_arg_type {
    sml_arg_type_basic, // basic on off | -Wall -Wextra like
    sml_arg_type_string, // like grep "asd"
    sml_arg_type_digit, // like -O3, -O2, -O=3 etc...
    sml_arg_type_yes_no, // like -feature=true, -feature=1. NOTE -feature=2 is not accepted
};

typedef struct {

    char *name;
    char *error_message;
    char *usage;

} sml_arg_parse_cfg;

// a type for arguments for the argument_parsing library
typedef struct {

    enum sml_arg_type type;
    char *short_name;
    char *long_name;
    char *usage;

} sml_arg;

// generic array for sml_arg so that we can use it inside a function properly.
typedef struct {

    sml_arg *arguments;
    unsigned long long capacity;
    unsigned long long last_element_index;

} sml_arg_array;

typedef struct {
    bool is_found;
    void *data;
} sml_arg_return;


// the designated way to create a new sml_arg.
// NOTE: if you want to leave a place, empty just make it NULL
sml_arg *new_sml_arg(enum sml_arg_type type, char *short_name, char *long_name, char *usage);

// the designated way to create a new sml_arg_array.
// NOTE: if expected size is NULL or zero sizes will be set to 1;
// NOTE: There is no way to make the arrays smaller procedurally so be wise;
sml_arg_array *new_sml_arg_array(unsigned long long expected_size);

// Appends to the sml_array
// NOTE: There is no way to make the arrays smaller procedurally so be wise;
void sml_arg_array_append(sml_arg_array *arr, sml_arg *arg);

// prints the usages of sml_arg's
void sml_arg_print_usages(sml_arg_array *args);

bool sml_arg_parse(int argc, char **argv, sml_arg_array *args, sml_arg_parse_cfg *cfg);

// frees sml_arg
void free_sml_arg(sml_arg *arg_to_be_freed);

// frees sml_arg_array
void free_sml_arg_array(sml_arg_array *args_to_be_freed);


#endif //SML_DIALECT_ARGUMENT_PARSING_H

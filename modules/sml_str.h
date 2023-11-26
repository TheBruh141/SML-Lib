//
// Created by bruhpc on 10/16/23.
//

#ifndef SML_LIB_SML_STR_H
#define SML_LIB_SML_STR_H

#include "common_bindings.h"

#define SML_STR_SUCCESS 1
#define SML_STR_FAIL 0

typedef struct {
    char *contents;
    sml_size capacity;
    sml_size last_index; // note that this includes the null terminator too ('\0')
} sml_str;

typedef struct {
    sml_str **contents;
    sml_size capacity;
    sml_size last_index;
} sml_str_array;

#ifdef SML_STR_MAKE_GENERIC
typedef sml_str str;
typedef sml_str_array str_array;
#endif

sml_str *sml_str_new(char *contents);

sml_str_array *sml_str_array_new();

// reallocs to double size.
_Bool sml_str_double_capacity(sml_str *contents);

_Bool sml_str_double_capacity_force(sml_str *contents);

_Bool sml_str_append(sml_str *dest, char *to_append);

void sml_str_array_append(sml_str_array *dest, sml_str *to_append);

char *sml_str_get_sub_str(char *str, sml_size start, sml_size end);

void sml_str_pop(sml_str *str);

void sml_str_array_print(sml_str_array *contents);

// destroys the string
void sml_str_destroy(sml_str *contents);

void sml_str_array_destroy(sml_str_array *contents);

// replaces all of the patterns in the string based on the pattern
void sml_str_replace(sml_str *contents, const char *pattern, const char *replacement);

// replaces the pattern in the string by the given replacement but only the nth like
// this will go like this
// a a b b;
// sml_str_replace_nth(sml_str *contents, "a", "b", 1);
// a b b b;
// sml_str_replace_nth(sml_str *contents, "a", "b", 2); // since there is no 3rd 'a' it will loop back to 0
// b a b b;
// ----
//
// a a a a;
// sml_str_replace_nth(sml_str *contents, "a", "b", -1);
// a a a b;
// sml_str_replace_nth(sml_str *contents, "a", "b", -2);
// a a b a;
// just like in python it will loop back.

sml_str *sml_str_replace_nth(sml_str *contents, const char *pattern, const char *replacement,
                             long long nth) __attribute_noinline__;


sml_str* sml_str_array_merge(sml_str_array* arr);
sml_str* sml_str_array_join(sml_str_array* arr, char* delimiter);

// prints the help message for this library.
void sml_str_help();

#endif //SML_LIB_SML_STR_H

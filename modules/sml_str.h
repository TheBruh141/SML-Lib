//
// Created by bruhpc on 10/16/23.
//

#ifndef SML_STR_H
#define SML_STR_H

#include "common_bindings.h"

#define SML_STR_SUCCESS 1
#define SML_STR_FAIL 0

typedef struct {
    char *contents;
    sml_size capacity;
    sml_size last_index; // note that this includes the null terminator too ('\0')
} sml_str;

#ifdef SML_STR_MAKE_GENERIC
typedef sml_str str
#endif

sml_str *sml_str_new(char *contents);

// reallocs to double size.
_Bool sml_str_double_capacity(sml_str *contents);

_Bool sml_str_double_capacity_force(sml_str *contents);


_Bool sml_str_append(sml_str *dest, char *to_append);

char *sml_str_get_sub_str(char *str, sml_size start, sml_size end);

// prints the help message for this library.
void sml_str_help();

#endif //SML_STR_H

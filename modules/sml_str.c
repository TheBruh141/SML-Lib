//
// Created by bruhpc on 10/16/23.
//

#include "sml_str.h"
#include "common_bindings.h"
#include "allocators.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

// creates a new sml_str instance. Note. char* must be null terminated
sml_str *sml_str_new(char *contents) {
    if (contents == NULL) {
        // since calloc zeroes everything we get a zero initialized str :D
        sml_str *new = (sml_str *) calloc(1, sizeof(sml_str));
        return new;
    }
    sml_str *new = (sml_str *) sml_mem_alloc(1, sizeof(sml_str));
    sml_size len = strlen(contents);

    new->capacity = len;
    new->last_index = len;
    new->contents = (char *) sml_mem_alloc(len, sizeof(char));
    memcpy(new->contents, contents, len);
    return new;
}

// doubles the string's capacity
// returns 0 if failed
_Bool sml_str_double_capacity(sml_str *contents) {
    contents->capacity *= 2;
    char *fallback = (char *) realloc(contents->contents, contents->capacity);
    if (fallback == NULL) {
        fprintf(stderr, "[SML_STR_LIB] : string reallocation failed in \nfile : %s\nline %d", __FILE__, __LINE__);
        contents->capacity /= 2;
        return SML_STR_FAIL;
    }
    contents->contents = fallback;
    return SML_STR_SUCCESS;
}

// rather than reallocation with realloc we are using malloc to copy from a -> b.
// NOTE: this function is way slower in paper. have not done tests tho.
_Bool sml_str_double_capacity_force(sml_str *contents) {
    contents->capacity *= 2;
    char *new_content = (char *) malloc(sizeof(char) * contents->capacity);

    if (new_content == NULL) {
        fprintf(stderr, "[SML_STR_LIB] : string reallocation_force failed in \nfile : %s\nline %d", __FILE__, __LINE__);
        return SML_STR_FAIL;
    }

    memcpy(new_content, contents->contents, contents->capacity / 2);
    free(contents->contents);
    contents->contents = new_content;
    return SML_STR_SUCCESS;
}


_Bool sml_str_append(sml_str *dest, char *to_append) {
    sml_size len = strlen(to_append);
    while (dest->capacity <= len + dest->last_index) {
        if (SML_STR_FAIL == sml_str_double_capacity(dest)) {
            if (SML_STR_FAIL == sml_str_double_capacity_force(dest)) {
                return SML_STR_FAIL;
            }
        }
    }
    for (sml_size i = 0; i < len; i++) {
        dest->contents[dest->last_index + i] = to_append[i];
    }
    return Sml_Success;
}

char *sml_str_get_sub_str(char *str, sml_size start, sml_size end) {
    sml_size len = end - start;
    char *sub_str = (char *) sml_mem_alloc(len, sizeof(char));
    memcpy(sub_str, str + start, len);
    return sub_str;
}
void sml_str_help() {

    printf("[SML_STR_LIB] : ");
    printf("\t # Defines ");
    printf("1. SML_STR_MAKE_GENERIC : removes the prefix from types defined in this module. ie. sml_str -> str");

}


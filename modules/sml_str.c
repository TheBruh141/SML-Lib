//
// Created by bruhpc on 10/16/23.
//

#include "sml_str.h"
#include "common_bindings.h"

#include <stdio.h>
#include <string.h>

sml_str *sml_str_new(char *contents) {
    if (contents == NULL) {
        // since calloc zeroes everything we get a zero initialized str :D
        sml_str *new = (sml_str *) calloc(1, sizeof(sml_str));
        return new;
    }
    sml_str *new = (sml_str *) malloc(sizeof(sml_str));
    sml_size len = strlen(contents);

    new->capacity = len;
    new->last_index = len;
    new->contents = (char *) malloc(sizeof(char) * len);
    memcpy(new->contents, contents, len);
    return new;
}

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
}

char *sml_str_get_sub_str(char *str, sml_size start, sml_size end) {
    if (NULL == str) {
        fprintf(stderr,
                "[SML_STR_LIB] : str cannot point to null.\n\t=> File Name :: %s, Line :: %d, Function Parameters ::  %s",
                __FILE__, __LINE__, __PRETTY_FUNCTION__ );
        return (char *) SML_STR_FAIL;
    }
    if (strlen(str) < end || start > strlen(str)) {
        fprintf(stderr,
                "[SML_STR_LIB] : string append failed in \nfile : %s\nline %d\n\t=> start or end cannot exceed the strings boundaries for memory safety and general program health (damn this is too formal)\n\tSTART = %llu, END = %llu, STRING BOUNDS (0,%lu)",
                __FILE__, __LINE__, start, end, strlen(str));
        return (char *) SML_STR_FAIL;
    }


}
//
//// ----- Algorithms ----
//
//// the most basic and the most unoptimized solution.
//// PROS: has no preprocessing and minimal memory requirements.
//// CONS: SLOW!
//// TIME COMPLEXITY: O(mn), where m and n are the length of the strings.
//sml_sub_str_arr sml_str_find_substring_naive(char *string, char *pattern) {
//    sml_size count = 0;
//    sml_size str_len = strlen(string);
//    sml_size pattern_len = strlen(pattern);
//
//    sml_size capacity = str_len / pattern_len;
//    sml_sub_str_arr arr = (sml_sub_str_arr) {
//            .capacity = capacity,
//            .contents = malloc(capacity * sizeof(char)),
//            .last_index = 0,
//    };
//
//    for (sml_size i = 0; i <= str_len - pattern_len; i++) {
//        int j;
//        for (j = 0; j < pattern_len; j++) {
//            if (pattern[j] != string[i + j]) {
//                break;
//            }
//        }
//        if (j == pattern_len) {
//            count++;
//        }
//    }
//
//    return count;
//}

void sml_str_help() {

    printf("[SML_STR_LIB] : ");
    printf("\t # Defines ");
    printf("1. SML_STR_MAKE_GENERIC : removes the prefix from types defined in this module. ie. sml_str -> str");

}


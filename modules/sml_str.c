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
        sml_str *new = (sml_str *) sml_mem_alloc(1, sizeof(sml_str));
        new->capacity = 1;
        new->last_index = 0;
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


sml_str_array *sml_str_array_new() {
    sml_str_array *new = (sml_str_array *) sml_mem_alloc(1, sizeof(sml_str_array));
    new->contents = (sml_str **) sml_mem_alloc(1, sizeof(sml_str *));
    new->last_index = 0;
    new->capacity = 2;
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

void sml_str_array_append(sml_str_array *dest, sml_str *to_append) {
    if (dest->last_index >= dest->capacity) {
        dest->capacity *= 2;
        sml_str **buff = (sml_str **) realloc(dest->contents, dest->capacity * sizeof(sml_str *));

        if (buff == NULL) {
            fprintf(stderr, "[SML_STR_LIB] : string reallocation failed in \nfile : %s\nline %d", __FILE__, __LINE__);
            dest->capacity /= 2;
            return;
        } else {
            dest->contents = buff;
        }
    }
    dest->contents[dest->last_index++] = to_append;
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

// frees sml_str
void sml_str_destroy(sml_str *contents) {
    if (contents) {
        if (contents->contents != NULL) {
            free(contents->contents);
        }
    }
}

// frees the array of sml_str's
void sml_str_array_destroy(sml_str_array *str_array) {
    if (str_array) {
        for (sml_size i = 0; i < str_array->last_index - 1 && str_array->contents[i] != NULL; ++i) {
            sml_str_destroy(str_array->contents[i]);
        }
    }
}


void sml_str_pop(sml_str *str) {
    if (str->last_index == 0) {
        return;
    }
    str->last_index--;
    str->contents[str->last_index] = '\0';
}

void sml_str_array_print(sml_str_array *contents) {
    printf("[\n");
    for (sml_size i = 0; i < contents->last_index; ++i) {
        printf("\t[%s] :: %llu \n", contents->contents[i]->contents, i);
    }
    printf("]");
}

void sml_str_replace(sml_str *contents, const char *pattern, const char *replacement) {
    // Check if any of the input pointers are NULL
    if (contents == NULL || pattern == NULL || replacement == NULL) {
        fprintf(stderr, "Error: NULL pointer detected\n");
        return;
    }

    // Check if pattern is an empty string
    if (strlen(pattern) == 0) {
        fprintf(stderr, "Error: Empty pattern\n");
        return;
    }

    // Find the first occurrence of the pattern in the contents
    char *match = strstr(contents->contents, pattern);

    // If the pattern is not found, return without making any changes
    if (match == NULL) {
        return;
    }

    // Calculate the length of the replacement and the original pattern
    sml_size pattern_len = strlen(pattern);
    sml_size replacement_len = strlen(replacement);

    // Calculate the new length of the contents after replacement
    sml_size new_length = contents->last_index + replacement_len - pattern_len;

    // Check if there is enough capacity to accommodate the new contents
    if (new_length >= contents->capacity) {
        // If not, resize the contents buffer
        contents->capacity = new_length + 1; // +1 for the null terminator
        contents->contents = sml_mem_realloc(contents->contents, contents->capacity, 3);
    }

    // Calculate the position to start copying characters after replacement
    char *copy_start = match + pattern_len;

    // Calculate the number of characters to copy after replacement
    sml_size copy_length = contents->last_index - (copy_start - contents->contents) + 1; // +1 for the null terminator

    // Move the remaining characters to make space for the replacement
    memmove(match + replacement_len, copy_start, copy_length);

    // Copy the replacement into the contents
    memcpy(match, replacement, replacement_len);

    // Update the last_index to reflect the new length of the contents
    contents->last_index = new_length;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

// sml_str_replace_nth - replaces the pattern in the string by the given replacement but only the nth occurrence.
//
// Parameters:
//   contents - the sml_str instance to be modified.
//   pattern - the pattern to be replaced.
//   replacement - the string to replace the pattern.
//   nth - the occurrence to be replaced. Positive values count from the beginning, negative values count from the end.
//
// Returns:
//   A pointer to the modified sml_str instance. If nth exceeds the actual occurrences of the pattern, it wraps around.
//
// Note:
//   This function modifies the input sml_str instance in place.
sml_str *sml_str_replace_nth(sml_str *contents, const char *pattern, const char *replacement, long long nth) {
    if (!contents || !pattern || !replacement) {
        // Handle invalid input parameters
        return NULL;
    }

    sml_size pattern_len = strlen(pattern);
    sml_size replacement_len = strlen(replacement);

    if (pattern_len == 0) {
        // Handle empty pattern
        return contents;
    }

    sml_size content_len = strlen(contents->contents);

    sml_size occurrences;

    start:

    occurrences = 0;


    // Loop through the string and count occurrences
    for (sml_size i = 0; i <= content_len - pattern_len; ++i) {
        if (strncmp(contents->contents + i, pattern, pattern_len) == 0) {
            ++occurrences;
            if (occurrences == nth || (nth < 0 && occurrences == -nth)) {
                // Replace the nth occurrence
                sml_size remaining_len = content_len - i - pattern_len;
                if (replacement_len > pattern_len) {
                    // Expand capacity if needed
                    if (!sml_str_double_capacity(contents)) {
                        // Handle memory allocation failure
                        return NULL;
                    }
                }
                if (replacement_len != pattern_len) {
                    // Shift the remaining content to accommodate the replacement
                    memmove(contents->contents + i + replacement_len, contents->contents + i + pattern_len,
                            remaining_len);
                }
                // Copy the replacement into the string
                memcpy(contents->contents + i, replacement, replacement_len);
                contents->contents[content_len + replacement_len - pattern_len] = '\0';
                return contents;
            }
        }
    }

    // check if there are no occurrences
    if (occurrences == 0) {
        return contents;
    }

    if (nth == 0) {
        nth = 1;
        goto start;
    }
    // If nth is negative, wrap around
    if (nth < 0) {
        long tmp = (nth + occurrences) % (occurrences);
        nth = (tmp < 0) ? -tmp : tmp;
        goto start;
    }

    // If nth exceeds actual occurrences, wrap around
    nth %= (occurrences) + 1;
    goto start;
}

sml_str *sml_str_array_merge(sml_str_array *arr) {

    sml_str *new = sml_str_new(NULL);
    for (sml_size i = 0; i < arr->last_index; ++i) {
        sml_str_append(new, arr->contents[i]->contents);
    }
    return new;
}

sml_str *sml_str_array_join(sml_str_array *arr, char *delimiter) {
    sml_str *new = sml_str_new(NULL);
    for (sml_size i = 0; i < arr->last_index; ++i) {
        sml_str_append(new, arr->contents[i]->contents);
        sml_str_append(new, delimiter);
    }
    return new;
}


#pragma clang diagnostic pop



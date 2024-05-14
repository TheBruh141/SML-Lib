#ifndef SML_LIB_SML_CSTR_H
#define SML_LIB_SML_CSTR_H

#include "common_bindings.h"

// This struct represents a 2D array of strings.
// This struct lives on da heap
typedef struct sml_cstr_array{
    char **contents; // Pointer to the array of strings.
    sml_size size;   // Current number of strings in the array.
    sml_size capacity; // Maximum capacity of the array.
} sml_cstr_array;

// Creates a new empty sml_cstr_array.
sml_cstr_array *sml_cstr_array_new_empty();

// Creates a new sml_cstr_array with a specified initial capacity.
sml_cstr_array *sml_cstr_array_new_with_capacity(sml_size capacity);

// Creates a sml_cstr_array from a string by splitting it using a delimiter.
sml_cstr_array *sml_cstr_array_from_string(char *str, char *delim);

sml_cstr_array *sml_cstr_array_from_array(char** array, sml_size size);

// Frees the memory occupied by an sml_cstr_array.
void sml_cstr_array_free(sml_cstr_array *array);

// Resizes the sml_cstr_array to a new capacity.
void sml_cstr_array_resize(sml_cstr_array *array, sml_size new_capacity);

// Appends a string to the sml_cstr_array.
void sml_cstr_array_append(sml_cstr_array *array, char *str);

// Gets a string at a specific index from the sml_cstr_array.
char *sml_cstr_array_get(sml_cstr_array *array, sml_size index);

// Merges two sml_cstr_array into a single string.
char *sml_cstr_array_merge(sml_cstr_array *array1, sml_cstr_array *array2);

// Joins strings in the sml_cstr_array using a separator.
char *sml_cstr_array_join(sml_cstr_array *array, char *separator);

// Converts the sml_cstr_array to a single string.
char *sml_cstr_array_to_string(sml_cstr_array *array);

#endif //SML_LIB_SML_CSTR_H

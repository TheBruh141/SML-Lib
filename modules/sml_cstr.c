#include "sml_cstr.h"
#include <stdio.h> // Include necessary headers.
#include <string.h>

// Creates a new empty sml_cstr_array.
sml_cstr_array *sml_cstr_array_new_empty() {
    return sml_cstr_array_new_with_capacity(1);
}

sml_cstr_array *sml_cstr_array_new_with_capacity(sml_size initial_capacity) {
    sml_cstr_array *new_array = (sml_cstr_array *) malloc(sizeof(sml_cstr_array));

    if (new_array) {
        new_array->contents = (char **) malloc(initial_capacity * sizeof(char *));
        if (new_array->contents) {
            new_array->size = 0;
            new_array->capacity = initial_capacity;
            return new_array;
        } else {
            // Free the allocated sml_cstr_array struct if contents allocation fails
            free(new_array);
        }
    }

    return NULL; // Return NULL on allocation failure
}

sml_cstr_array *sml_cstr_array_from_string(char *str, char *delim) {
    CHECK(str != NULL
          && delim != NULL
          && str[0] != '\0'
          && delim[0] != '\0'
    ); // Check that the arguments are valid

    sml_cstr_array *array = sml_cstr_array_new_empty();


    char *token;
    char *end;
    token = strtok_r(str, delim, &end);

    while (token != NULL) {
        sml_cstr_array_append(array, token);
        token = strtok_r(NULL, delim, &end);
    }

    return array;
}

sml_cstr_array *sml_cstr_array_from_array(char **array, unsigned long long int size) {
    CHECK(array != NULL && size > 0); // Check that the arguments are valid
    sml_cstr_array *array2 = sml_cstr_array_new_with_capacity(size);
    for (unsigned long long int i = 0; i < size; ++i) {
        sml_cstr_array_append(array2, array[i]);
    }
    return array2;
}

// Frees the memory occupied by an sml_cstr_array.
void sml_cstr_array_free(sml_cstr_array *array) {
    if (array) {
        if (array->contents) {
            free(array->contents);
        }
        free(array);
    }
}


// Resizes the sml_cstr_array to a new capacity.
void sml_cstr_array_resize(sml_cstr_array *array, sml_size new_capacity) {
    if (array) {
        if (array->contents == NULL) {
            fprintf(stderr,
                    "\n[SML_LIB @ CSTR] invalid resizing at %s line %d function %s \n :: arrays contents is NULL which means an empty array.\n\t-> falling back to creating a new array with the desired lenght\n",
                    __FILE__, __LINE__, __func__);
            array = sml_cstr_array_new_with_capacity(new_capacity);
            return;
        }
        char **new_contents = (char **) realloc(array->contents, new_capacity * sizeof(char *));
        if (new_contents) {
            array->contents = new_contents;
            array->capacity = new_capacity;
            if (array->size > new_capacity) {
                array->size = new_capacity;
            }
        } else {
            fprintf(stderr, "[SML_LIB @ CSTR] realloc failed in sml_cstr_array_resize at %s line %d\n", __FILE__,
                    __LINE__);
        }
    }
}


void sml_cstr_array_append(sml_cstr_array *array, char *str) {
    CHECK(str != NULL && array != NULL); // Check that the argument is valid
    CHECK(array->size <= array->capacity); // Check that the our array is also valid


    if (array != NULL) { // check if the array is there
        if (array->size >= array->capacity) {
            if (array->capacity == 0) {
                array = sml_cstr_array_new_with_capacity(1);
                array->contents[array->size++] = str; // append the string to the array
                return;
            }
            sml_cstr_array_resize(array, array->capacity * 2);
        }
        array->contents[array->size++] = str; // append the string to the array
    }
}

char *sml_cstr_array_join(sml_cstr_array *array, char *separator) {
    unsigned long long length = 0;
    unsigned separator_length = strlen(separator);

    for (sml_size i = 0; i < array->size; ++i) {
        CHECK(array->contents[i] != NULL);
        length += strlen(array->contents[i]) + separator_length;
    }

    length -= separator_length; // Remove the last separator because we won't separate at the end

    char *result = (char *) malloc(length + 1);
    if (result) {
        result[0] = '\0'; // Initialize result as an empty string

        for (sml_size i = 0; i < array->size; ++i) {
            strcat(result, array->contents[i]);
            if (i < array->size - 1) {
                strcat(result, separator);
            }
        }
    }
    // result[length] = '\0'; // No need to set the null terminator here

    return result;
}

char *sml_cstr_array_get(sml_cstr_array *array, unsigned long long int index) {
    if (index >= array->size) {
        fprintf(stderr,"[SML_LIB @ CSTR] index out of bounds, array size is %llu, requested index is %llu\n", array->size, index);
        EXIT_WITH_INFO;
    }
    return array->contents[index];
}

char *sml_cstr_array_merge(sml_cstr_array *array1, sml_cstr_array *array2) {
    CHECK(array1 != NULL && array2 != NULL); // Check that the arguments are valid
    sml_cstr_array *array3 = sml_cstr_array_new_with_capacity(array1->size + array2->size);
    for (unsigned long long int i = 0; i < array1->size; ++i) {
        sml_cstr_array_append(array3, array1->contents[i]);
    }
    for (unsigned long long int i = 0; i < array2->size; ++i) {
        sml_cstr_array_append(array3, array2->contents[i]);
    }
    return sml_cstr_array_to_string(array3);
}

char *sml_cstr_array_to_string(sml_cstr_array *array) {
    CHECK(array != NULL); // Check that the arguments are valid
    sml_size length = 0;
    for (unsigned long long int i = 0; i < array->size; ++i) {
        if (array->contents[i] != NULL) {
            length += strlen(array->contents[i]);
        }
    }
    char *result = (char *) malloc(length + 1);
    if (result) {
        result[0] = '\0'; // Initialize result as an empty string
        for (unsigned long long int i = 0; i < array->size; ++i) {
            if (array->contents[i] != NULL) {
                strcat(result, array->contents[i]);
            }
        }
    }
    return result;
}


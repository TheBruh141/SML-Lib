//
// Created by bruh on 6/23/25.
//

#include "linalg.h"

#include <allocators.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Vector
 */
Vector_f new_vec_f(const size_t size,
                   size_t num_given,
                   const float value, ...) {
    /**
     * @brief Creates a new float vector (`Vector_f`) with the given size and initializes
     *        the first `num_given` elements with variadic float arguments.
     *
     * @param size       Total number of elements to allocate in the vector.
     * @param num_given  Number of values provided after `value` (including `value` itself).
     * @param value      The first float value to be inserted (required to access varargs).
     * @param ...        Additional `num_given - 1` float values (promoted to double).
     *
     * @return A `Vector_f` struct with `.size` set and `.data` pointing to the allocated memory.
     *         If memory allocation fails or size is 0, `.data` is NULL and `.size` is set to 0.
     *
     * @note If `num_given > size`, extra values are ignored.
     * @note If `num_given == 0`, the `value` is still required, but not used.
     * @note The caller must call `free_vec_f()` to free the result.
     */

    Vector_f vec = {0};

    if (size == 0) {
        return vec;
    }

    vec.size = size;
    vec.data = (float*) sml_alloc(size, sizeof(float));

    if (!vec.data) {
        fprintf(stderr, "[SML | linalg | new_vec_f] Failed to allocate %zu bytes of memory\n, returning size 0", size);
        vec.size = 0;
        return vec;
    }

    if (num_given == 0) {
        return vec;
    }

    va_list ap;
    va_start(ap, value);
    vec.data[0] = value;

    size_t limit = num_given < size ? num_given : size;

    for (size_t i = 1; i < limit; i++) {
        vec.data[i] = (float) va_arg(ap, double);// float promoted to double
    }
    va_end(ap);

    return vec;
}

Vector_f new_vec_f_zeroes(size_t size) {
    /**
     * @brief Creates a new float vector (`Vector_f`) with the given size and initializes
     *        it with zeroes.
     *
     * @param size       Total number of elements to allocate in the vector.
     * @return A `Vector_f` struct with `.size` set and `.data` pointing to the allocated memory.
     *         If memory allocation fails or size is 0, `.data` is NULL and `.size` is set to 0.
     *
     * @note The caller must call `free_vec_f()` to free the result.
     */

    Vector_f vec = {0};
    if (size == 0) {
        return vec;
    }
    vec.size = size;
    vec.data = sml_calloc(size, sizeof(float));
    if (!vec.data) {
        fprintf(stderr, "[SML | linalg | new_vec_f_zeroes] Failed to allocate %zu bytes of memory\n, returning size 0", size);
    }
    return vec;
}


void free_vec_f(Vector_f vec) {
    /**
     * @brief Frees the dynamically allocated memory of a `Vector_f`.
     *
     * @param vec The vector whose memory should be freed. The function safely handles NULL `data`.
     *
     * @note After calling this, the vector becomes invalid. This does not free the struct itself.
     */

    free(vec.data);
}

char *as_string_vec_f(Vector_f vec) {
    /**
     * @brief Converts a `Vector_f` into a human-readable string representation.
     *
     * @param vec The vector to convert (assumed valid and allocated).
     *
     * @return A newly allocated string containing the vector contents in the format:
     *         "[1.00, 2.00, 3.00]". Returns "[]" for empty vectors.
     *         On memory allocation failure, returns NULL and prints an error message.
     *
     * @note The caller must `free()` the returned string after use.
     */

    if (vec.size == 0) {
        char* empty = sml_alloc(3, sizeof(char));
        if (!empty) {
        fprintf(stderr, "[SML | linalg | as_string_vec_f ] Failed to allocate 3 bytes of memory");
            return nullptr;
        }
        strcpy(empty, "[]");
        return empty;
    }

    // Conservative estimate: 32 characters per float (plenty)
    const size_t max_chars = vec.size * 32 + 2;// +2 for '[' and ']'
    char *result = sml_alloc(max_chars, sizeof(char));
    if (!result) return nullptr;

    char *p = result;
    size_t written = 0;

    written += snprintf(p + written, max_chars - written, "[");
    for (size_t i = 0; i < vec.size; ++i) {
        if (i != 0) {
            written += snprintf(p + written, max_chars - written, ", ");
        }
        written += snprintf(p + written, max_chars - written, "%.2f", vec.data[i]);
    }
    snprintf(p + written, max_chars - written, "]");

    return result;// caller must free
}

/*
 * Matrix
 */

Matrix_f new_mat_f(size_t width,
                   size_t height,
                   size_t num_initial_rows,    // Renamed for clarity, implies va_args covers these rows/cols
                   size_t num_initial_cols,    // Renamed for clarity
                   float default_fill_value, ...) { // Explicitly defines how the rest are filled
    Matrix_f mat = {.width = width, .height = height};
    mat.data = sml_alloc(width * height, sizeof(float));

    if (!mat.data) {
        fprintf(stderr, "[SML | linalg | new_mat_f] Failed to allocate %zu(width) * %zu(height) = %zu bytes of memory\n, returning size 0 of width and heigh",
            width * sizeof(float), height * sizeof(float), width * height * sizeof(float));
        return mat;
    }

    va_list ap;
    va_start(ap, default_fill_value); // Last fixed argument for va_start

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (row < num_initial_rows && col < num_initial_cols) {
                // Read from variadic arguments for the initial section
                mat.data[row * width + col] = (float) va_arg(ap, double);
            } else {
                // Fill the rest with the specified default value
                mat.data[row * width + col] = default_fill_value;
            }
        }
    }
    va_end(ap); // Always call va_end!
    return mat;
}
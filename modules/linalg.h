//
// Created by bruh on 6/23/25.
//

#ifndef LINALG_H
#define LINALG_H
#include <stddef.h>

#pragma region types

typedef struct {
    size_t size;
    float *data;
} Vector_f;

typedef struct {
    size_t width;
    size_t height;

    float *data;
} Matrix_f;

#pragma endregion types

#pragma region implementations

/*
 * Vector
 */

Vector_f new_vec_f(size_t size,
                   size_t num_given,
                   float value, ...);

Vector_f new_vec_f_zeroes(size_t size);

void free_vec_f(Vector_f vec);

char* as_string_vec_f(Vector_f vec);

/*
 * Matrix
 */

Matrix_f new_mat_f(size_t width, size_t height, size_t num_given_width, size_t num_given_height, float default_value, ...);

void free_mat_f(Matrix_f mat);

char* as_string_mat_f(Matrix_f mat);

#pragma endregion implementations

#endif //LINALG_H

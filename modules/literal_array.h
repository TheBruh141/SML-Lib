//
// Created by bruh on 10/6/23.
//

#ifndef SML_DIALECT_LITERAL_ARRAY_H
#define SML_DIALECT_LITERAL_ARRAY_H

#include "common_bindings.h"
#include <stdbool.h>
#include <bits/types/FILE.h>

typedef enum {

    _byte = 0,
    _boolean,

    _unsigned_short_int,
    _unsigned_int,
    _short_int,
    _int,

    _long,
    _long_long,

    _float,
    _double,
    _long_double,

    _generic_array,
}__attribute__((__packed__)) sml_array_types;

#pragma region sml_arr_decl
// a sml_array of bytes

typedef struct {
    void *contents;
    sml_size_t size_of_contents_per_element;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_generic_t;


typedef struct {
    sml_byte_t *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_byte_t;

// a sml_array of booleans
typedef struct {
    bool *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_bool_t;

// a sml_array of unsigned short ints
typedef struct {
    unsigned short int *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_usint_t;

// a sml_array of short ints
typedef struct {
    short int *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_sint_t;

// a sml_array of integers :D
typedef struct {
    int *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_int_t;

// a sml_array of unsigned ints
typedef struct {
    unsigned *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_uint_t;

// a sml_array of longs
typedef struct {
    long *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_long_t;

// a sml_array of long longs
typedef struct {
    long long *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_llong_t;

// a sml_array of doubles
typedef struct {
    double *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_double_t;

// a sml_array of long doubles
typedef struct {
    long double *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_ldouble_t;

// a sml_array of floats
typedef struct {
    float *contents;
    sml_size_t capacity;
    sml_size_t last_pos;
} sml_array_float_t;

#pragma endregion sml_arr_decl

/*
 * Generates a new array.
 * a way of declaring arrays in a general way
 * NOTE: Needs to be typecast-ed in declaration
 * */
void *sml_new_array(sml_array_types type, void *contents, unsigned long long int size_of_contents_per_element);

void print_array(sml_array_types, void *contents, FILE *stream);

void free_array(sml_array_types, void *contents);

void insert_array(sml_array_types, void *insert_contents);

void pop_array(sml_array_types, sml_size_t how_many);

void append_array(sml_array_types, void *append_contents);

#endif //SML_DIALECT_LITERAL_ARRAY_H

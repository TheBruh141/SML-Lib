//
// Created by bruh on 10/6/23.
//

#include "literal_array.h"
#include "common_bindings.h"
#include "allocators.h"

#include <stddef.h>
#include <stdio.h>

static sml_size_t sml_internal_round_up_pow2(sml_size_t n) {
    // If n is already a power of two, return it as is
    if ((n & (n - 1)) == 0) {
        return n;
    }

    // Find the most significant bit (MSB) of n
    unsigned int msb = 0;
    while (n > 0) {
        n >>= 1;
        msb++;
    }

    // Calculate the rounded-up value as 2 raised to the power of the MSB
    return 1u << msb;
}

// needs to be typecasted to be utilized properly.
// this generates a new array with your desired type
void *sml_new_array(sml_array_types type, void *contents, unsigned long long int size_of_contents_per_element) {

    sml_size_t last_pos = sizeof(contents) / size_of_contents_per_element;
    sml_size_t sizeof_array = sml_internal_round_up_pow2(last_pos);

    switch (type) {

        case _byte: {
            sml_array_byte_t *new_array = (sml_array_byte_t *) sml_alloc(sizeof(sml_array_byte_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;
        }
        case _boolean: {
            sml_array_bool_t *new_array = (sml_array_bool_t *) sml_alloc(sizeof(sml_array_bool_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;
        }
        case _unsigned_short_int: {
            sml_array_usint_t *new_array = (sml_array_usint_t *) sml_alloc(sizeof(sml_array_usint_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _unsigned_int: {
            sml_array_uint_t *new_array = (sml_array_uint_t *) sml_alloc(sizeof(sml_array_uint_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _short_int: {
            sml_array_sint_t *new_array = (sml_array_sint_t *) sml_alloc(sizeof(sml_array_sint_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _int: {
            sml_array_int_t *new_array = (sml_array_int_t *) sml_alloc(sizeof(sml_array_int_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _long: {
            sml_array_long_t *new_array = (sml_array_long_t *) sml_alloc(sizeof(sml_array_long_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;


        }
        case _long_long: {
            sml_array_llong_t *new_array = (sml_array_llong_t *) sml_alloc(sizeof(sml_array_llong_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _float: {
            sml_array_float_t *new_array = (sml_array_float_t *) sml_alloc(sizeof(sml_array_float_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _double: {
            sml_array_double_t *new_array = (sml_array_double_t *) sml_alloc(sizeof(sml_array_double_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _long_double: {
            sml_array_ldouble_t *new_array = (sml_array_ldouble_t *) sml_alloc(sizeof(sml_array_ldouble_t), 1);
            new_array->contents = (typeof(new_array->contents)) contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            return new_array;

        }
        case _generic_array: {
            sml_array_generic_t *new_array = (sml_array_generic_t *) sml_alloc(sizeof(sml_array_generic_t), 1);
            new_array->contents = contents;
            new_array->last_pos = last_pos;
            new_array->capacity = sizeof_array;
            new_array->size_of_contents_per_element = size_of_contents_per_element;
            return new_array;
        }
        default:
            fprintf(stderr, "Unknown type cannot initialize array");
    }
    return (void *) -1;
}

// prints any sml_array type
void print_array(sml_array_types types, void *contents, FILE* stream) {
    switch (types) {

        case _byte:
            break;
        case _boolean:
            break;
        case _unsigned_short_int:
            break;
        case _unsigned_int:
            break;
        case _short_int:
            break;
        case _int:
            break;
        case _long:
            break;
        case _long_long:
            break;
        case _float:
            break;
        case _double:
            break;
        case _long_double:
            break;
        case _generic_array:
            break;
    }
}

//
// Created by bruh on 10/6/23.
//

#include "allocators.h"
#include "common_bindings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *sml_mem_alloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    // check for overflow and underflow
    CHECK(how_much * sizeof_mem >= how_much);

#if (defined DEBUG)
    return sml_mem_calloc(how_much, sizeof_mem);
#else
    return sml_mem_malloc(how_much * (sizeof_mem));
#endif
}


void *__attribute_malloc__ sml_mem_malloc(unsigned long long size) {
    void *new_mem = malloc(size);
    CHECK(new_mem == NULL);
    return new_mem;
}

void *__attribute_malloc__ sml_mem_calloc(unsigned long long how_much, unsigned long long sizeof_mem) {
    void *new_mem = calloc(how_much, sizeof_mem);
    return new_mem;
}

void *sml_mem_realloc(void *ptr, unsigned long long new_requested_size, short unsigned retry) {
    sml_pointer new_mem;
    if (!retry) { retry = 1; }

    do {
        new_mem = realloc(ptr, new_requested_size);
        if (new_mem == NULL) {
            SML_LOG_INFO(stderr, "SML_MEM_REALLOC", "cannot realloc");
        }
    } while (retry-- > 0);
    return new_mem;
}

// force a realloc by litterally using a different piece of memory.
// it's slower but safer + more flexible.
void *sml_mem_realloc_change_place(void *ptr, unsigned long long new_requested_size) {
    const unsigned long long int size = sizeof(typeof(ptr[0]));
    sml_pointer new_mem = sml_mem_alloc(new_requested_size, size);
    memcpy(new_mem, ptr, new_requested_size);
    return new_mem;
}

// the same as sml_mem_realloc_change_place but with a different name. to make it easier to type
void *sml_mem_realloc_f(void *ptr, unsigned long long new_requested_size) {
    return sml_mem_realloc_change_place(ptr, new_requested_size);
}
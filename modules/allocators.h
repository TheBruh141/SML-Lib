//
// Created by bruh on 10/6/23.
//

#ifndef SML_DIALECT_ALLOCATORS_H

void *sml_alloc(unsigned long long how_much, unsigned long long sizeof_mem);

void *sml_malloc(unsigned long long size);

void *sml_calloc(unsigned long long how_much, unsigned long long sizeof_mem);

void *sml_realloc(void *ptr, unsigned long long new_requested_size);

// a derivative of sml_realloc.
// rather than relying on realloc,
// it tries to allocate a different memory on failure
void *sml_realloc_s(void *ptr, unsigned long long new_requested_size);


#define SML_DIALECT_ALLOCATORS_H

#endif //SML_DIALECT_ALLOCATORS_H
